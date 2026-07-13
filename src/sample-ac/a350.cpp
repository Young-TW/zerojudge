#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> counts(9);
    for (int i = 0; i < 9; ++i) {
        cin >> counts[i];
    }

    vector<int> lengths = {8, 16, 24, 32, 40, 48, 56, 64, 80};
    vector<int> order = {8, 7, 6, 5, 4, 3, 2, 1, 0};

    int total_ribbons = 0;
    bool possible = true;

    while (true) {
        int remaining = N;
        bool used = false;

        for (int idx : order) {
            while (counts[idx] > 0 && lengths[idx] <= remaining) {
                remaining -= lengths[idx];
                counts[idx]--;
                used = true;
            }
        }

        if (!used) {
            bool all_zero = true;
            for (int c : counts) {
                if (c != 0) {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero) {
                break;
            } else {
                possible = false;
                break;
            }
        }

        total_ribbons++;
    }

    if (possible) {
        cout << total_ribbons << endl;
    } else {
        cout << "NO SOLUTION!!" << endl;
    }

    return 0;
}
