#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> dp;
vector<vector<int>> nextA;
vector<vector<int>> nextB;
string cur;

long long dfs_count(int i, int j) {
    if (dp[i][j] == 0) {
        return 1;
    }
    long long count = 0;
    for (char c = '0'; c <= '9'; ++c) {
        int ni = nextA[i][c];
        int nj = nextB[j][c];
        if (ni < n && nj < m && dp[ni + 1][nj + 1] + 1 == dp[i][j]) {
            count += dfs_count(ni + 1, nj + 1);
        }
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        int ni = nextA[i][c];
        int nj = nextB[j][c];
        if (ni < n && nj < m && dp[ni + 1][nj + 1] + 1 == dp[i][j]) {
            count += dfs_count(ni + 1, nj + 1);
        }
    }
    return count;
}

void dfs_print(int i, int j) {
    if (dp[i][j] == 0) {
        cout << cur << '\n';
        return;
    }
    for (char c = '0'; c <= '9'; ++c) {
        int ni = nextA[i][c];
        int nj = nextB[j][c];
        if (ni < n && nj < m && dp[ni + 1][nj + 1] + 1 == dp[i][j]) {
            cur.push_back(c);
            dfs_print(ni + 1, nj + 1);
            cur.pop_back();
        }
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        int ni = nextA[i][c];
        int nj = nextB[j][c];
        if (ni < n && nj < m && dp[ni + 1][nj + 1] + 1 == dp[i][j]) {
            cur.push_back(c);
            dfs_print(ni + 1, nj + 1);
            cur.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        for (int case_num = 1; case_num <= T; ++case_num) {
            string A, B;
            if (!(cin >> A >> B)) break;
            n = A.size();
            m = B.size();
            
            dp.assign(n + 1, vector<int>(m + 1, 0));
            for (int i = n - 1; i >= 0; --i) {
                for (int j = m - 1; j >= 0; --j) {
                    if (A[i] == B[j]) {
                        dp[i][j] = dp[i + 1][j + 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
                    }
                }
            }
            
            nextA.assign(n + 1, vector<int>(128, n));
            for (int i = n - 1; i >= 0; --i) {
                for (int c = 0; c < 128; ++c) {
                    nextA[i][c] = nextA[i + 1][c];
                }
                nextA[i][(unsigned char)A[i]] = i;
            }
            
            nextB.assign(m + 1, vector<int>(128, m));
            for (int i = m - 1; i >= 0; --i) {
                for (int c = 0; c < 128; ++c) {
                    nextB[i][c] = nextB[i + 1][c];
                }
                nextB[i][(unsigned char)B[i]] = i;
            }
            
            cur.clear();
            
            long long count = dfs_count(0, 0);
            cout << "Case #" << case_num << ": " << count << "\n";
            dfs_print(0, 0);
        }
    }
    
    return 0;
}
