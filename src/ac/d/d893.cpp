#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

bool isNumber(const string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') start = 1;
    if (start >= (int)s.size()) return false;
    for (int i = start; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

int solve(int N, int M, const vector<int>& a, const vector<int>& cards) {
    int c1=0,c2=0,c3=0,c4=0;
    for (int x : cards) {
        if (x==1) c1++;
        else if (x==2) c2++;
        else if (x==3) c3++;
        else c4++;
    }
    
    vector<vector<vector<vector<int>>>> dp(
        c1+1, vector<vector<vector<int>>>(
            c2+1, vector<vector<int>>(
                c3+1, vector<int>(c4+1, 0))));
    
    dp[0][0][0][0] = a[0];
    for (int i = 0; i <= c1; i++) {
        for (int j = 0; j <= c2; j++) {
            for (int k = 0; k <= c3; k++) {
                for (int l = 0; l <= c4; l++) {
                    if (i==0 && j==0 && k==0 && l==0) continue;
                    int pos = i + 2*j + 3*k + 4*l;
                    int best = 0;
                    if (i > 0) best = max(best, dp[i-1][j][k][l]);
                    if (j > 0) best = max(best, dp[i][j-1][k][l]);
                    if (k > 0) best = max(best, dp[i][j][k-1][l]);
                    if (l > 0) best = max(best, dp[i][j][k][l-1]);
                    dp[i][j][k][l] = best + a[pos];
                }
            }
        }
    }
    
    return dp[c1][c2][c3][c4];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string tok;
    vector<int> nums;
    bool hasMarkers = false;
    vector<int> sampleStarts;
    while (cin >> tok) {
        if (isNumber(tok)) {
            nums.push_back(atoi(tok.c_str()));
        } else {
            hasMarkers = true;
            sampleStarts.push_back(nums.size());
        }
    }
    
    if (hasMarkers) {
        for (int s = 0; s < (int)sampleStarts.size(); s++) {
            int startIdx = sampleStarts[s];
            if (startIdx + 1 >= (int)nums.size()) break;
            int N = nums[startIdx];
            int M = nums[startIdx + 1];
            if (startIdx + 2 + N + M > (int)nums.size()) break;
            vector<int> a(nums.begin() + startIdx + 2, nums.begin() + startIdx + 2 + N);
            vector<int> cards(nums.begin() + startIdx + 2 + N, nums.begin() + startIdx + 2 + N + M);
            int ans = solve(N, M, a, cards);
            cout << "输出样例" << (s+1) << "：\n";
            cout << ans << "\n";
        }
    } else {
        int idx = 0;
        while (idx + 1 < (int)nums.size()) {
            int N = nums[idx];
            int M = nums[idx+1];
            if (idx + 2 + N + M > (int)nums.size()) break;
            vector<int> a(nums.begin() + idx + 2, nums.begin() + idx + 2 + N);
            vector<int> cards(nums.begin() + idx + 2 + N, nums.begin() + idx + 2 + N + M);
            int ans = solve(N, M, a, cards);
            cout << ans << "\n";
            idx += 2 + N + M;
        }
    }
    
    return 0;
}
