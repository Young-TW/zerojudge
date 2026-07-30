#include <bits/stdc++.h>
using namespace std;

int N=9;
vector<string> g;
bool vis[9][9];
int dr[4]={1,-1,0,0};
int dc[4]={0,0,1,-1};

int main(){
    g.assign(9,"");
    for(int i=0;i<9;i++) cin>>g[i];

    long long scoreB=0, scoreW=0;
    for(int i=0;i<9;i++)for(int j=0;j<9;j++){
        if(g[i][j]=='B') scoreB++;
        else if(g[i][j]=='W') scoreW++;
    }

    memset(vis,0,sizeof(vis));
    for(int i=0;i<9;i++)for(int j=0;j<9;j++){
        if(g[i][j]!='.'||vis[i][j]) continue;
        // flood fill this empty region
        vector<pair<int,int>> cells;
        bool touchB=false, touchW=false;
        stack<pair<int,int>> st;
        st.push({i,j}); vis[i][j]=true;
        while(!st.empty()){
            auto [r,c]=st.top(); st.pop();
            cells.push_back({r,c});
            for(int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if(nr<0||nr>=9||nc<0||nc>=9) continue;
                char v=g[nr][nc];
                if(v=='.'){
                    if(!vis[nr][nc]){ vis[nr][nc]=true; st.push({nr,nc}); }
                } else if(v=='B') touchB=true;
                else if(v=='W') touchW=true;
            }
        }
        if(touchB&&touchW){
            // region enclosed by both colors -> game not finished
            cout<<"Wrong\n";
            return 0;
        }
        if(touchB){
            scoreB+=(long long)cells.size();
            for(auto&p:cells) g[p.first][p.second]='B';
        } else if(touchW){
            scoreW+=(long long)cells.size();
            for(auto&p:cells) g[p.first][p.second]='W';
        }
        // neither: neutral, leave as '.'
    }

    if(scoreB>scoreW) cout<<"Black wins!!\n";
    else cout<<"White wins!!\n";
    cout<<scoreB<<":"<<scoreW<<"\n";
    for(int i=0;i<9;i++) cout<<g[i]<<"\n";
    return 0;
}
