#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

char target[10005];
char monkey[3][10005];
int dp[2][10005];

int edit_distance(const char* X, const char* Y) {
    int lenX = strlen(X);
    int lenY = strlen(Y);
    int* prev_dp = dp[0];
    int* curr_dp = dp[1];
    for (int j = 0; j <= lenY; ++j) {
        prev_dp[j] = 2 * j;
    }
    for (int i = 1; i <= lenX; ++i) {
        curr_dp[0] = 2 * i;
        char xi = X[i-1];
        for (int j = 1; j <= lenY; ++j) {
            int cost = (xi == Y[j-1]) ? 0 : 3;
            int val = prev_dp[j-1] + cost;
            int val2 = prev_dp[j] + 2;
            if (val2 < val) val = val2;
            val2 = curr_dp[j-1] + 2;
            if (val2 < val) val = val2;
            curr_dp[j] = val;
        }
        int* tmp = prev_dp;
        prev_dp = curr_dp;
        curr_dp = tmp;
    }
    return prev_dp[lenY];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> target >> monkey[0] >> monkey[1] >> monkey[2]) {
        int best_monkey = 1;
        int min_dist = edit_distance(target, monkey[0]);
        
        int dist2 = edit_distance(target, monkey[1]);
        if (dist2 <= min_dist) {
            min_dist = dist2;
            best_monkey = 2;
        }
        
        int dist3 = edit_distance(target, monkey[2]);
        if (dist3 <= min_dist) {
            min_dist = dist3;
            best_monkey = 3;
        }
        
        cout << best_monkey << " " << min_dist << "\n";
    }
    return 0;
}
