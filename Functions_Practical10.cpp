
#include <iostream>
using namespace std;

int max_of_four(int a, int b, int c, int d) {
    int largest = a;

    if (b > largest)
        largest = b;
    if (c > largest)
        largest = c;
    if (d > largest)
        largest = d;

    return largest;
}

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << max_of_four(a, b, c, d) << endl;

    return 0;
}