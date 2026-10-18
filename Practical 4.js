require("dotenv").config();
const express = require("express");
const session = require("express-session");
const path = require("path");
const bcrypt = require("bcryptjs");
const mysql = require("mysql2/promise");

const app = express();
const PORT = Number(process.env.PORT || 3000);

const pool = mysql.createPool({
  host: process.env.DB_HOST || "localhost",
  port: Number(process.env.DB_PORT || 3306),
  user: process.env.DB_USER || "root",
  password: process.env.DB_PASSWORD || "",
  database: process.env.DB_NAME || "login_system_p4",
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(session({
  secret: process.env.SESSION_SECRET || "change-this-development-secret",
  resave: false,
  saveUninitialized: false,
  cookie: { httpOnly: true, sameSite: "lax", secure: false, maxAge: 2 * 60 * 60 * 1000 }
}));
app.use(express.static(path.join(__dirname, "public")));

function requireLogin(req, res, next) {
  if (!req.session.user) return res.status(401).json({ message: "Please log in first." });
  next();
}
function cleanUser(row) {
  return { id: row.id, name: row.name, email: row.email, mobile: row.mobile, created_at: row.created_at };
}

// Register
app.post("/api/register", async (req, res) => {
  const name = String(req.body.name || "").trim();
  const email = String(req.body.email || "").trim().toLowerCase();
  const mobile = String(req.body.mobile || "").trim();
  const password = String(req.body.password || "");
  if (!name || !email || !mobile || !password) {
    return res.status(400).json({ message: "All fields are required." });
  }
  if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
    return res.status(400).json({ message: "Enter a valid email address." });
  }
  if (password.length < 8) {
    return res.status(400).json({ message: "Password must be at least 8 characters." });
  }
  try {
    const hash = await bcrypt.hash(password, 12);
    await pool.execute(
      "INSERT INTO users (name, email, mobile, password_hash) VALUES (?, ?, ?, ?)",
      [name, email, mobile, hash]
    );
    res.status(201).json({ message: "Registration successful. You can now log in." });
  } catch (err) {
    if (err.code === "ER_DUP_ENTRY") return res.status(409).json({ message: "That email is already registered." });
    console.error(err);
    res.status(500).json({ message: "Server/database error. Check the server terminal and database settings." });
  }
});

// Login
app.post("/api/login", async (req, res) => {
  const email = String(req.body.email || "").trim().toLowerCase();
  const password = String(req.body.password || "");
  if (!email || !password) return res.status(400).json({ message: "Email and password are required." });
  try {
    const [rows] = await pool.execute(
      "SELECT id, name, email, mobile, password_hash FROM users WHERE email = ?",
      [email]
    );
    if (!rows.length || !(await bcrypt.compare(password, rows[0].password_hash))) {
      return res.status(401).json({ message: "Invalid email or password." });
    }
    req.session.user = { id: rows[0].id, name: rows[0].name, email: rows[0].email };
    res.json({ message: `Welcome, ${rows[0].name}!`, user: req.session.user });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: "Server/database error. Check the server terminal and database settings." });
  }
});

// Current session
app.get("/api/me", (req, res) => {
  res.json({ user: req.session.user || null });
});

// Logout
app.post("/api/logout", (req, res) => {
  req.session.destroy(err => {
    if (err) return res.status(500).json({ message: "Could not log out." });
    res.clearCookie("connect.sid");
    res.json({ message: "Logged out successfully." });
  });
});

// View users (authenticated)
app.get("/api/users", requireLogin, async (req, res) => {
  try {
    const [rows] = await pool.execute(
      "SELECT id, name, email, mobile, created_at FROM users ORDER BY id DESC"
    );
    res.json({ users: rows.map(cleanUser) });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: "Could not load users." });
  }
});

// Edit a user (authenticated). Do not accept password changes through this endpoint.
app.put("/api/users/:id", requireLogin, async (req, res) => {
  const id = Number(req.params.id);
  const name = String(req.body.name || "").trim();
  const email = String(req.body.email || "").trim().toLowerCase();
  const mobile = String(req.body.mobile || "").trim();
  if (!Number.isInteger(id) || id < 1 || !name || !email || !mobile) {
    return res.status(400).json({ message: "Valid user ID, name, email and mobile are required." });
  }
  if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
    return res.status(400).json({ message: "Enter a valid email address." });
  }
  try {
    const [result] = await pool.execute(
      "UPDATE users SET name = ?, email = ?, mobile = ? WHERE id = ?",
      [name, email, mobile, id]
    );
    if (!result.affectedRows) return res.status(404).json({ message: "User not found." });
    res.json({ message: "User updated successfully." });
  } catch (err) {
    if (err.code === "ER_DUP_ENTRY") return res.status(409).json({ message: "That email is already used by another account." });
    console.error(err);
    res.status(500).json({ message: "Could not update user." });
  }
});

// Delete a user (authenticated). Confirmation is handled in the frontend.
app.delete("/api/users/:id", requireLogin, async (req, res) => {
  const id = Number(req.params.id);
  if (!Number.isInteger(id) || id < 1) return res.status(400).json({ message: "Invalid user ID." });
  try {
    const [result] = await pool.execute("DELETE FROM users WHERE id = ?", [id]);
    if (!result.affectedRows) return res.status(404).json({ message: "User not found." });
    res.json({ message: "User deleted successfully." });
  } catch (err) {
    console.error(err);
    res.status(500).json({ message: "Could not delete user." });
  }
});

app.get("/api/health", async (_req, res) => {
  try {
    await pool.query("SELECT 1");
    res.json({ status: "ok", database: "connected" });
  } catch (_err) {
    res.status(500).json({ status: "error", database: "not connected", hint: "Check .env and schema.sql." });
  }
});

app.listen(PORT, () => {
  console.log(`Practical 4 running at http://localhost:${PORT}`);
});
