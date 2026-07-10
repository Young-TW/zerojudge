#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int A, B;
int grid[32][32];
bool vis[32][32];
const int dr[4] = {1,-1,0,0};
const int dc[4] = {0,0,1,-1};

int bfs(int sr, int sc, int H){
    queue<pair<int,int> > q;
    q.push(make_pair(sr,sc));
    vis[sr][sc] = true;
    int cnt = 0;
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        cnt++;
        for(int k=0;k<4;k++){
            int nr = r+dr[k], nc = c+dc[k];
            if(nr<0||nr>=A||nc<0||nc>=B) continue;
            if(vis[nr][nc]) continue;
            if(grid[nr][nc]!=H) continue;
            vis[nr][nc]=true;
            q.push(make_pair(nr,nc));
        }
    }
    return cnt;
}

int main(){
    while(scanf("%d %d", &A, &B)==2){
        for(int i=0;i<A;i++)
            for(int j=0;j<B;j++)
                scanf("%d", &grid[i][j]);
        int N;
        scanf("%d", &N);
        for(int q=0;q<N;q++){
            int H;
            scanf("%d", &H);
            memset(vis,0,sizeof(vis));
            int best = 0;
            for(int i=0;i<A;i++)
                for(int j=0;j<B;j++)
                    if(!vis[i][j] && grid[i][j]==H){
                        int sz = bfs(i,j,H);
                        if(sz>best) best=sz;
                    }
            if(best < 2) best = 0;
            printf("%d\n", best);
        }
    }
    return 0;
}
