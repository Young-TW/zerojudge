#include <iostream>
#include <cstring>

using namespace std;

const int MAX_A = 5005;
int bit[MAX_A];

void add(int idx, int val) {
    for (; idx < MAX_A; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            memset(bit, 0, sizeof(bit));
            
            long long total_sum = 0;
            for (int i = 0; i < n; ++i) {
                int a;
                cin >> a;
                total_sum += query(a);
                add(a, 1);
            }
            cout << total_sum << "\n";
        }
    }
    return 0;
}
