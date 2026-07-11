#include <iostream>
#include <string>

using namespace std;

const int MAXN = 100005;
int bit_neg[MAXN];
int bit_zero[MAXN];
int arr[MAXN];

void add(int* bit, int idx, int val, int n) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += val;
}

int sum(int* bit, int idx) {
    int ret = 0;
    for (; idx > 0; idx -= idx & -idx)
        ret += bit[idx];
    return ret;
}

int range_sum(int* bit, int l, int r) {
    return sum(bit, r) - sum(bit, l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) {
            bit_neg[i] = 0;
            bit_zero[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            if (arr[i] < 0) add(bit_neg, i, 1, n);
            else if (arr[i] == 0) add(bit_zero, i, 1, n);
        }
        string ans;
        while (k--) {
            char op;
            int a, b;
            cin >> op >> a >> b;
            if (op == 'C') {
                if (arr[a] < 0) add(bit_neg, a, -1, n);
                else if (arr[a] == 0) add(bit_zero, a, -1, n);
                
                arr[a] = b;
                
                if (arr[a] < 0) add(bit_neg, a, 1, n);
                else if (arr[a] == 0) add(bit_zero, a, 1, n);
            } else {
                if (range_sum(bit_zero, a, b) > 0) {
                    ans += '0';
                } else {
                    int neg_cnt = range_sum(bit_neg, a, b);
                    if (neg_cnt % 2 == 1) ans += '-';
                    else ans += '+';
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
