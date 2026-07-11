#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n1;
    while (cin >> n1) {
        vector<long long> poly(1005, 0);
        
        for (int i = 0; i < n1; ++i) {
            int p;
            long long c;
            cin >> p >> c;
            poly[p] += c;
        }

        int n2;
        cin >> n2;
        for (int i = 0; i < n2; ++i) {
            int p;
            long long c;
            cin >> p >> c;
            poly[p] += c;
        }

        bool hasOutput = false;
        for (int p = 1000; p >= 0; --p) {
            if (poly[p] != 0) {
                cout << p << ':' << poly[p] << '\n';
                hasOutput = true;
            }
        }

        if (!hasOutput) {
            cout << "NULL!\n";
        }
    }

    return 0;
}
