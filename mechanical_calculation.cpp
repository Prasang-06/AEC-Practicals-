
#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

// Function to safely accept positive numbers
double getPositiveInput(string message) {
    double value;

    while (true) {
        cout << message;

        if (cin >> value && value > 0) {
            return value;
        }

        cout << "Error: Enter a valid positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Calculate Force: F = m * a
double calculateForce(double mass, double acceleration) {
    return mass * acceleration;
}

// Calculate Work: W = F * d
double calculateWork(double force, double distance) {
    return force * distance;
}

// Calculate Power: P = W / t
double calculatePower(double work, double time) {
    return work / time;
}

// Calculate Density: density = mass / volume
double calculateDensity(double mass, double volume) {
    return mass / volume;
}

// Calculate Pressure: P = F / A
double calculatePressure(double force, double area) {
    return force / area;
}

int main() {
    int choice;
    double a, b, result;

    cout << fixed << setprecision(2);

    do {
        cout << "\n===== MECHANICAL CALCULATOR =====\n";
        cout << "1. Calculate Force\n";
        cout << "2. Calculate Work\n";
        cout << "3. Calculate Power\n";
        cout << "4. Calculate Density\n";
        cout << "5. Calculate Pressure\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                a = getPositiveInput("Enter mass (kg): ");
                b = getPositiveInput("Enter acceleration (m/s^2): ");
                result = calculateForce(a, b);
                cout << "Force = " << result << " N\n";
                break;

            case 2:
                a = getPositiveInput("Enter force (N): ");
                b = getPositiveInput("Enter distance (m): ");
                result = calculateWork(a, b);
                cout << "Work = " << result << " J\n";
                break;

            case 3:
                a = getPositiveInput("Enter work (J): ");
                b = getPositiveInput("Enter time (s): ");
                result = calculatePower(a, b);
                cout << "Power = " << result << " W\n";
                break;

            case 4:
                a = getPositiveInput("Enter mass (kg): ");
                b = getPositiveInput("Enter volume (m^3): ");
                result = calculateDensity(a, b);
                cout << "Density = " << result << " kg/m^3\n";
                break;

            case 5:
                a = getPositiveInput("Enter force (N): ");
                b = getPositiveInput("Enter area (m^2): ");
                result = calculatePressure(a, b);
                cout << "Pressure = " << result << " Pa\n";
                break;

            case 6:
                cout << "Exiting Mechanical Calculator. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Please select 1-6.\n";
        }

    } while (choice != 6);

    return 0;
}
