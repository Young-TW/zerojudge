#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<long long> x;
int count_prime;

long long pow_mod(long long a, long long exp, long long mod) {
    long long res = 1;
    a %= mod;
    while (exp) {
        if (exp & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        exp >>= 1;
    }
    return res;
}

bool is_prime(long long num) {
    if (num < 2) return false;
    if (num == 2 || num == 3 || num == 5 || num == 7) return true;
    if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0) return false;
    
    long long d = num - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    for (int a : {2, 7, 61}) {
        if (a >= num) continue;
        long long x_val = pow_mod(a, d, num);
        if (x_val == 1 || x_val == num - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x_val = (x_val * x_val) % num;
            if (x_val == num - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

void dfs(int idx, int picked, long long sum) {
    if (picked == k) {
        if (is_prime(sum)) {
            count_prime++;
        }
        return;
    }
    if (idx == n) return;
    if (n - idx < k - picked) return;
    
    dfs(idx + 1, picked + 1, sum + x[idx]);
    dfs(idx + 1, picked, sum);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> n >> k) {
        x.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        count_prime = 0;
        dfs(0, 0, 0);
        cout << count_prime << "\n";
    }
    
    return 0;
}
