#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAXN = 100005;
const double INF = 1e30;

int N, L, P;
int len[MAXN];
double dp[MAXN];
int pre[MAXN];

double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) {
        result *= base;
        if (result > 1e18) return 1e30; 
    }
    return result;
}

double calc(int i, int j) {
    if (j >= i) return INF;
    int line_len = 0;
    for (int k = j; k < i; ++k) {
        if (k > j) line_len += 1; 
        line_len += len[k];
    }
    double diff = abs(line_len - L);
    return power(diff, P);
}

void solve() {
    cin >> N >> L >> P;
    string s;
    getline(cin, s); 

    for (int i = 0; i < N; ++i) {
        getline(cin, s);
        len[i] = s.length();
    }

    deque<int> dq;
    dq.push_back(0);
    dp[0] = 0;
    pre[0] = -1;

    for (int i = 1; i <= N; ++i) {
        while (dq.size() >= 2) {
            int j1 = dq[0];
            int j2 = dq[1];
            if (dp[j1] + calc(i, j1) >= dp[j2] + calc(i, j2)) {
                dq.pop_front();
            } else {
                break;
            }
        }

        int best_j = dq.front();
        dp[i] = dp[best_j] + calc(i, best_j);
        pre[i] = best_j;

        while (dq.size() >= 2) {
            int j1 = dq[dq.size() - 2];
            int j2 = dq.back();
            int j3 = i;
            
            double val1 = dp[j1] + calc(j2, j1);
            double val2 = dp[j2] + calc(j2, j1); 
            double val3 = dp[j2] + calc(j3, j2);
            double val4 = dp[j3] + calc(j3, j2);

            if ((val2 - val1) * (j3 - j2) >= (val4 - val3) * (j2 - j1)) {
                dq.pop_back();
            } else {
                break;
            }
        }
        dq.push_back(i);
    }

    if (dp[N] > 1e18) {
        cout << "Too hard to arrange" << endl;
    } else {
        cout << (ll)(dp[N] + 0.5) << endl;
    }
    cout << "--------------------" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
