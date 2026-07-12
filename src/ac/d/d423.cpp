#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 10000001;
vector<int> prime_factors_count(MAX_N + 1, 0);

void precompute() {
    for (int i = 2; i <= MAX_N; ++i) {
        if (prime_factors_count[i] == 0) {
            for (int j = i; j <= MAX_N; j += i) {
                int num = j;
                while (num % i == 0) {
                    prime_factors_count[j]++;
                    num /= i;
                }
            }
        }
    }
    for (int i = 1; i <= MAX_N; ++i) {
        prime_factors_count[i] += prime_factors_count[i - 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int N, case_num = 1;
    while (cin >> N) {
        if (N < 0) break;
        cout << "Case " << case_num++ << ": ";
        if (N == 0) {
            cout << "0!\n";
            continue;
        }
        int low = 0, high = MAX_N;
        int ans = -1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (prime_factors_count[mid] >= N) {
                if (prime_factors_count[mid] == N) {
                    ans = mid;
                }
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        if (ans != -1) {
            cout << ans << "!\n";
        } else {
            cout << "Not possible.\n";
        }
    }

    return 0;
}
