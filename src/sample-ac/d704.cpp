#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    unsigned long long W[] = {0, 1, 2, 6, 30, 240, 3120, 65520, 2227680, 122522400, 10904493600ULL};
    int max_idx = 9;
    
    unsigned long long n;
    while (cin >> n) {
        int start = max_idx;
        while (start > 1 && W[start] > n) {
            start--;
        }
        bool first = true;
        for (int i = start; i >= 1; --i) {
            if (!first) cout << ",";
            cout << n / W[i];
            n %= W[i];
            first = false;
        }
        cout << "\n";
    }
    return 0;
}
