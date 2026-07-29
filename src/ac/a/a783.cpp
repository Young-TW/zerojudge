// a783 Houston Skyline - self-written renderer (silhouette-outline model).
// Per-column height colH[x] = max actual height (h+2) over buildings covering column x.
// Building i covers cols [Li..Ri] = [s .. s+w+1] (actual width w+2), actual height Hi=h+2.
// Draw the outline of this histogram:
//  - top surface '-' at each column's roof (y==colH[x]);
//  - vertical walls '|' at height steps (a column taller than a neighbour), the wall
//    spanning from the neighbour's height up to its own (bottom corner = neighbour top);
//  - roof of a shorter neighbour extends one cell into the taller column (a corner);
//  - ground '-' along y==1 for empty columns and wall bases;
//  - corners/junctions '+' where horizontal meets vertical.
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const int COLS=50;
    const string ruler="12345678901234567890123456789012345678901234567890";
    int n;
    while(cin>>n){
        vector<int> L,R,H;
        for(int i=0;i<n;i++){
            int s,w,h; cin>>s>>w>>h;
            L.push_back(s); R.push_back(s+w+1); H.push_back(h+2);
        }
        // compute heights beyond col 50 too, so a building continuing past the
        // right edge does not create an artificial wall at column 50.
        const int WIDE=110;
        vector<int> colH(WIDE+2,0); // col 0 is empty sentinel (buildings start >=1)
        int maxH=0;
        for(int x=1;x<=WIDE;x++){
            int best=0;
            for(int i=0;i<(int)L.size();i++) if(L[i]<=x&&x<=R[i]) best=max(best,H[i]);
            colH[x]=best;
            if(x<=COLS) maxH=max(maxH,best);
        }
        if(maxH==0){ cout<<ruler<<"\n"; continue; }
        vector<string> rows;
        for(int y=maxH;y>=1;y--){
            string line(COLS,' ');
            for(int x=1;x<=COLS;x++){
                int hx=colH[x], hl=colH[x-1], hr=colH[x+1];
                bool leftTaller  = hx>hl;
                bool rightTaller = hx>hr;
                bool V=false;
                if(leftTaller  && y>=max(1,hl) && y<=hx) V=true;
                if(rightTaller && y>=max(1,hr) && y<=hx) V=true;
                bool Hh=false;
                if(hx>0 && y==hx) Hh=true;                 // top surface
                if(leftTaller  && hl>0 && y==hl) Hh=true;  // shorter-left roof extends into this col
                if(rightTaller && hr>0 && y==hr) Hh=true;  // shorter-right roof extends into this col
                if(y==1){                                  // ground line
                    if(hx==0) Hh=true;
                    else if(hl==0||hr==0) Hh=true;         // wall base on ground
                }
                char c=' ';
                if(Hh&&V)c='+'; else if(Hh)c='-'; else if(V)c='|';
                line[x-1]=c;
            }
            size_t e=line.find_last_not_of(' ');
            line = (e==string::npos)? string() : line.substr(0,e+1);
            rows.push_back(line);
        }
        for(auto&r:rows) cout<<r<<"\n";
        cout<<ruler<<"\n";
    }
    return 0;
}
