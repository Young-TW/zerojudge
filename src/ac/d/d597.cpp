#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> comb(k);
    for (int i = 0; i < k; ++i) {
        cin >> comb[i];
    }

    int rank = 1;
    vector<int> temp(k);
    for (int i = 0; i < k; ++i) {
        temp[i] = i + 1;
    }

    while (temp != comb) {
        int i = k - 1;
        while (i >= 0 && temp[i] == n - k + i + 1) {
            --i;
        }
        if (i < 0) break;
        ++temp[i];
        for (int j = i + 1; j < k; ++j) {
            temp[j] = temp[j - 1] + 1;
        }
        ++rank;
    }

    cout << rank << endl;

    int i = k - 1;
    while (i >= 0 && comb[i] == n - k + i + 1) {
        --i;
    }
    if (i < 0) {
        cout << "no next combination" << endl;
    } else {
        ++comb[i];
        for (int j = i + 1; j < k; ++j) {
            comb[j] = comb[j - 1] + 1;
        }
        for (int j = 0; j < k; ++j) {
            if (j > 0) cout << " ";
            cout << comb[j];
        }
        cout << endl;
    }

    return 0;
}
