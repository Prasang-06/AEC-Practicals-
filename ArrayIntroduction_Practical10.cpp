```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int arr[1000];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << arr[i];

        if (i > 0) {
            cout << " ";
        }
    }

    cout << endl;

    return 0;
}
```