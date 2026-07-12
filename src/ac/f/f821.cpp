#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string N, Q;
    int m;
    while (cin >> N >> m) {
        for (int i = 0; i < m; ++i) {
            cin >> Q;
            int A = 0, B = 0;
            bool inN[10] = {false};
            for (char c : N) {
                inN[c - '0'] = true;
            }
            for (size_t j = 0; j < N.length(); ++j) {
                if (N[j] == Q[j]) {
                    A++;
                } else if (inN[Q[j] - '0']) {
                    B++;
                }
            }
            cout << A << "A" << B << "B\n";
        }
    }
    return 0;
}
