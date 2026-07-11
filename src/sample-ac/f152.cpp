#include <iostream>

using namespace std;

unsigned long long n;
int max_divs = 0;
unsigned long long best_val = 0;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};

void dfs(int idx, unsigned long long current_val, int current_divs, int prev_exp) {
    if (current_divs > max_divs || (current_divs == max_divs && current_val < best_val)) {
        max_divs = current_divs;
        best_val = current_val;
    }
    
    if (idx == 18) return;
    
    for (int exp = 1; exp <= prev_exp; ++exp) {
        if (current_val > n / primes[idx]) break;
        current_val *= primes[idx];
        dfs(idx + 1, current_val, current_divs * (exp + 1), exp);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n) {
        max_divs = 0;
        best_val = 0;
        dfs(0, 1, 1, 63);
        cout << best_val << " " << max_divs << "\n";
    }
    return 0;
}
