#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, m;
    while (cin >> k >> m) {
        vector<set<long long>> table(m);
        for (int i = 0; i < k; i++) {
            int op;
            cin >> op;
            if (op == 1) {
                long long n;
                cin >> n;
                table[n % m].insert(n);
            } else if (op == 2) {
                long long n;
                cin >> n;
                table[n % m].erase(n);
            } else {
                cout << "===== s =====\n";
                for (int j = 0; j < m; j++) {
                    cout << '[' << setw(3) << setfill('0') << j << "]:";
                    if (table[j].empty()) {
                        cout << "NULL\n";
                    } else {
                        for (auto v : table[j]) {
                            cout << v << " -> ";
                        }
                        cout << "NULL\n";
                    }
                }
                cout << "===== e =====\n";
            }
        }
    }
    return 0;
}
