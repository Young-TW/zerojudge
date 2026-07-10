#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>
using namespace std;

int N, M, x, y, K;
char grid[205][205];
int dp[205][205];
int ndp[205][205];

int main(){
    while(scanf("%d %d %d %d %d", &N, &M, &x, &y, &K) == 5){
        for(int i = 1; i <= N; i++){
            scanf("%s", grid[i]+1);
        }
        const int NEG = -1000000;
        for(int i = 0; i <= N+1; i++)
            for(int j = 0; j <= M+1; j++)
                dp[i][j] = NEG;
        dp[x][y] = 0;

        for(int it = 0; it < K; it++){
            int s, t, d;
            scanf("%d %d %d", &s, &t, &d);
            int len = t - s + 1;
            for(int i = 0; i <= N+1; i++)
                for(int j = 0; j <= M+1; j++)
                    ndp[i][j] = NEG;

            if(d == 4){ // east: move right, process left-to-right
                for(int r = 1; r <= N; r++){
                    deque<int> dq;
                    for(int c = 1; c <= M; c++){
                        if(grid[r][c] == 'x'){ dq.clear(); continue; }
                        if(dp[r][c] > NEG){
                            int val = dp[r][c] - c;
                            while(!dq.empty() && dp[r][dq.back()] - dq.back() <= val) dq.pop_back();
                            dq.push_back(c);
                        }
                        while(!dq.empty() && dq.front() < c - len) dq.pop_front();
                        if(!dq.empty()) ndp[r][c] = dp[r][dq.front()] - dq.front() + c;
                    }
                }
            } else if(d == 3){ // west: move left, process right-to-left
                for(int r = 1; r <= N; r++){
                    deque<int> dq;
                    for(int c = M; c >= 1; c--){
                        if(grid[r][c] == 'x'){ dq.clear(); continue; }
                        if(dp[r][c] > NEG){
                            int val = dp[r][c] + c;
                            while(!dq.empty() && dp[r][dq.back()] + dq.back() <= val) dq.pop_back();
                            dq.push_back(c);
                        }
                        while(!dq.empty() && dq.front() > c + len) dq.pop_front();
                        if(!dq.empty()) ndp[r][c] = dp[r][dq.front()] + dq.front() - c;
                    }
                }
            } else if(d == 2){ // south: move down, process top-to-bottom
                for(int c = 1; c <= M; c++){
                    deque<int> dq;
                    for(int r = 1; r <= N; r++){
                        if(grid[r][c] == 'x'){ dq.clear(); continue; }
                        if(dp[r][c] > NEG){
                            int val = dp[r][c] - r;
                            while(!dq.empty() && dp[dq.back()][c] - dq.back() <= val) dq.pop_back();
                            dq.push_back(r);
                        }
                        while(!dq.empty() && dq.front() < r - len) dq.pop_front();
                        if(!dq.empty()) ndp[r][c] = dp[dq.front()][c] - dq.front() + r;
                    }
                }
            } else { // d == 1, north: move up, process bottom-to-top
                for(int c = 1; c <= M; c++){
                    deque<int> dq;
                    for(int r = N; r >= 1; r--){
                        if(grid[r][c] == 'x'){ dq.clear(); continue; }
                        if(dp[r][c] > NEG){
                            int val = dp[r][c] + r;
                            while(!dq.empty() && dp[dq.back()][c] + dq.back() <= val) dq.pop_back();
                            dq.push_back(r);
                        }
                        while(!dq.empty() && dq.front() > r + len) dq.pop_front();
                        if(!dq.empty()) ndp[r][c] = dp[dq.front()][c] + dq.front() - r;
                    }
                }
            }

            memcpy(dp, ndp, sizeof(dp));
        }

        int ans = 0;
        for(int r = 1; r <= N; r++)
            for(int c = 1; c <= M; c++)
                ans = max(ans, dp[r][c]);
        printf("%d\n", ans);
    }
    return 0;
}
