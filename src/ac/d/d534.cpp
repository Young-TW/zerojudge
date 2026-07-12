#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r0, r1, c0, c1;
    while (cin >> r0 >> r1 >> c0 >> c1) {
        vector<int> arr = {0, 1, 2, 3};
        bool found = false;
        do {
            int sum_r0 = arr[0] + arr[1];
            int sum_r1 = arr[2] + arr[3];
            int sum_c0 = arr[0] + arr[2];
            int sum_c1 = arr[1] + arr[3];
            if (sum_r0 == r0 && sum_r1 == r1 && sum_c0 == c0 && sum_c1 == c1) {
                cout << arr[0] << " " << arr[1] << "\n";
                cout << arr[2] << " " << arr[3] << "\n";
                found = true;
                break;
            }
        } while (next_permutation(arr.begin(), arr.end()));

        if (!found) {
            cout << "No solutions.\n";
        }
    }

    return 0;
}
