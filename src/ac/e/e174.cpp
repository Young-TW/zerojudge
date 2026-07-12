#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    string dummy;
    getline(cin, dummy);
    while(n--){
        vector<string> board(19);
        for(int i=0;i<19;i++){
            string s;
            if(!getline(cin, s)) s.clear();
            while(!s.empty() && (s.back()=='\r' || s.back()=='\n' || s.back()==' ' || s.back()=='\t')) s.pop_back();
            while((int)s.size()<19) s.push_back('.');
            if((int)s.size()>19) s = s.substr(0,19);
            board[i] = s;
        }
        int black = 0, white = 0;
        for(int r=0;r<19;r++){
            for(int c=0;c<19;c++){
                if(board[r][c]=='O') black++;
                else if(board[r][c]=='X') white++;
            }
        }
        vector<vector<bool>> vis(19, vector<bool>(19, false));
        int dr[4] = {1,-1,0,0};
        int dc[4] = {0,0,1,-1};
        for(int r=0;r<19;r++){
            for(int c=0;c<19;c++){
                if(board[r][c]=='.' && !vis[r][c]){
                    queue<pair<int,int>> q;
                    q.push(make_pair(r,c));
                    vis[r][c] = true;
                    int cnt = 0;
                    bool touchB = false, touchW = false;
                    while(!q.empty()){
                        pair<int,int> cur = q.front(); q.pop();
                        cnt++;
                        int cr = cur.first, cc = cur.second;
                        for(int d=0;d<4;d++){
                            int nr = cr + dr[d];
                            int nc = cc + dc[d];
                            if(nr<0||nr>=19||nc<0||nc>=19) continue;
                            char ch = board[nr][nc];
                            if(ch=='O') touchB = true;
                            else if(ch=='X') touchW = true;
                            else if(ch=='.' && !vis[nr][nc]){
                                vis[nr][nc] = true;
                                q.push(make_pair(nr,nc));
                            }
                        }
                    }
                    if(touchB && !touchW) black += cnt;
                    else if(touchW && !touchB) white += cnt;
                }
            }
        }
        cout << "O:" << black << "\n";
        cout << "X:" << white << "\n";
        if(black > white) cout << "Black win!!\n";
        else if(white > black) cout << "White win!!\n";
        else cout << "Draw\n";
    }
    return 0;
}
