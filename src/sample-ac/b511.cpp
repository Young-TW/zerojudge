#include <iostream>

using namespace std;

int N;
int coins[5];
int target;
int count[5];

void dfs(int idx, int remaining) {
    if (idx == N - 1) {
        if (remaining % coins[idx] == 0) {
            count[idx] = remaining / coins[idx];
            cout << "(";
            for (int i = 0; i < N; ++i) {
                cout << count[i];
                if (i < N - 1) {
                    cout << ",";
                }
            }
            cout << ")\n";
        }
        return;
    }
    for (int i = 0; i * coins[idx] <= remaining; ++i) {
        count[idx] = i;
        dfs(idx + 1, remaining - i * coins[idx]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N) {
        if (N <= 0) continue;
        for (int i = 0; i < N; ++i) {
            cin >> coins[i];
        }
        cin >> target;
        dfs(0, target);
    }
    return 0;
}
