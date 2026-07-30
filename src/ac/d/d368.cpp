#include <bits/stdc++.h>
using namespace std;

char B[8][8];

bool inB(int r,int c){ return r>=0&&r<8&&c>=0&&c<8; }

// is the king of given side ('W' -> white king 'K', 'B' -> black king 'k') in check?
// side 'W': our pieces uppercase, enemy lowercase. 'B': ours lowercase, enemy uppercase.
bool isCheck(char side){
    char kingCh = (side=='W') ? 'K' : 'k';
    int kr=-1,kc=-1;
    for(int r=0;r<8;r++)for(int c=0;c<8;c++) if(B[r][c]==kingCh){kr=r;kc=c;}
    if(kr<0) return false; // no such king (shouldn't happen)

    auto isEnemy = [&](char x){
        if(x=='.') return false;
        bool up = isupper((unsigned char)x);
        return (side=='W') ? !up : up; // enemy is opposite color
    };
    auto up = [&](char x){ return (char)toupper((unsigned char)x); };

    // Knight
    int kn[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
    for(auto&d:kn){int r=kr+d[0],c=kc+d[1]; if(inB(r,c)&&isEnemy(B[r][c])&&up(B[r][c])=='N') return true;}

    // Enemy king adjacent
    for(int dr=-1;dr<=1;dr++)for(int dc=-1;dc<=1;dc++){ if(!dr&&!dc)continue; int r=kr+dr,c=kc+dc; if(inB(r,c)&&isEnemy(B[r][c])&&up(B[r][c])=='K') return true; }

    // Pawn
    if(side=='W'){
        // white king attacked by black pawn 'p' located at (kr-1, kc±1) (black pawns attack downward)
        for(int dc=-1;dc<=1;dc+=2){ int r=kr-1,c=kc+dc; if(inB(r,c)&&B[r][c]=='p') return true; }
    } else {
        // black king attacked by white pawn 'P' located at (kr+1, kc±1) (white pawns attack upward)
        for(int dc=-1;dc<=1;dc+=2){ int r=kr+1,c=kc+dc; if(inB(r,c)&&B[r][c]=='P') return true; }
    }

    // Sliding: straight (rook/queen) and diagonal (bishop/queen)
    int straight[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    int diag[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
    for(auto&d:straight){
        int r=kr+d[0],c=kc+d[1];
        while(inB(r,c)){
            if(B[r][c]!='.'){
                if(isEnemy(B[r][c])){ char u=up(B[r][c]); if(u=='R'||u=='Q') return true; }
                break;
            }
            r+=d[0]; c+=d[1];
        }
    }
    for(auto&d:diag){
        int r=kr+d[0],c=kc+d[1];
        while(inB(r,c)){
            if(B[r][c]!='.'){
                if(isEnemy(B[r][c])){ char u=up(B[r][c]); if(u=='B'||u=='Q') return true; }
                break;
            }
            r+=d[0]; c+=d[1];
        }
    }
    return false;
}

int main(){
    vector<string> rows;
    string line;
    int game=0;
    while(getline(cin,line)){
        // strip trailing \r and spaces
        while(!line.empty() && (line.back()=='\r'||line.back()=='\n'||line.back()==' ')) line.pop_back();
        if(line.empty()){
            continue; // separator
        }
        rows.push_back(line);
        if((int)rows.size()==8){
            // build board
            bool allDot=true;
            for(int r=0;r<8;r++){
                for(int c=0;c<8;c++){
                    char ch = (c<(int)rows[r].size()) ? rows[r][c] : '.';
                    B[r][c]=ch;
                    if(ch!='.') allDot=false;
                }
            }
            rows.clear();
            if(allDot) break; // end of input
            game++;
            bool w=isCheck('W'); // white king in check?
            bool b=isCheck('B'); // black king in check?
            if(w) printf("Game #%d: white king is in check.\n", game);
            else if(b) printf("Game #%d: black king is in check.\n", game);
            else printf("Game #%d: no king is in check.\n", game);
        }
    }
    return 0;
}
