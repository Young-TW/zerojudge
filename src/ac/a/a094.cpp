#include <bits/stdc++.h>
using namespace std;

// seven-segment masks: bits a=1,b=2,c=4,d=8,e=16,f=32,g=64
// 0:6  1:2  2:5  3:5  4:4  5:5  6:6  7:3  8:7  9:6  sticks
int mask[10] = {63,6,91,79,102,109,125,7,127,111};
int pc(int x){ return __builtin_popcount(x); }

vector<int> addN[10], remN[10], winN[10];
void build(){
    for(int x=0;x<10;x++)for(int y=0;y<10;y++){
        if(x==y) continue;
        int a=mask[x], b=mask[y];
        if((a&b)==a && pc(b)-pc(a)==1) addN[x].push_back(y); // gain one stick
        if((a&b)==b && pc(a)-pc(b)==1) remN[x].push_back(y); // lose one stick
        if(pc(a)==pc(b) && pc(a&b)==pc(a)-1) winN[x].push_back(y); // move one stick within
    }
}

struct D { long long coef; int strpos; int val; };

int main(){
    build();
    string line;
    while(getline(cin,line)){
        // tolerate Windows line endings
        while(!line.empty() && (line.back()=='\r' || line.back()=='\n')) line.pop_back();
        size_t h = line.find('#');
        if(h == string::npos){ cout << "\n"; continue; } // blank / separator line
        string eq = line.substr(0, h); // equation, operators fixed, only digits movable

        // Parse digits with signed positional coefficient so that the equation
        // is valid  <=>  F = sum(coef[i]*digit[i]) == 0 . left side +, right side -.
        vector<D> ds;
        long long sideFactor = 1, termSign = 1;
        int n = (int)eq.size();
        for(int i=0;i<n;){
            char c = eq[i];
            if(c=='+'){ termSign = 1; i++; }
            else if(c=='-'){ termSign = -1; i++; }
            else if(c=='='){ sideFactor = -1; termSign = 1; i++; }
            else if(isdigit((unsigned char)c)){
                int j=i; while(j<n && isdigit((unsigned char)eq[j])) j++;
                long long place = 1;
                for(int k=j-1;k>=i;k--){
                    ds.push_back({ sideFactor*termSign*place, k, eq[k]-'0' });
                    place *= 10;
                }
                i = j; termSign = 1;
            } else i++;
        }
        // keep left-to-right order for a deterministic first solution
        sort(ds.begin(), ds.end(), [](const D&a, const D&b){ return a.strpos < b.strpos; });

        long long baseF = 0;
        for(auto&d : ds) baseF += d.coef * d.val;

        int m = (int)ds.size();
        string ans; bool found = false;

        // Case 1: move a stick within a single digit (stick count unchanged).
        for(int i=0;i<m && !found;i++){
            for(int v : winN[ds[i].val]){
                if(baseF + ds[i].coef*(v - ds[i].val) == 0){
                    ans = eq; ans[ds[i].strpos] = '0'+v; found = true; break;
                }
            }
        }
        // Case 2: take a stick from digit i (i loses one) and add to digit j (j gains one).
        for(int i=0;i<m && !found;i++){
            if(remN[ds[i].val].empty()) continue;
            for(int j=0;j<m && !found;j++){
                if(j==i) continue;
                if(addN[ds[j].val].empty()) continue;
                for(int r : remN[ds[i].val]){
                    for(int a : addN[ds[j].val]){
                        if(baseF + ds[i].coef*(r - ds[i].val)
                                 + ds[j].coef*(a - ds[j].val) == 0){
                            ans = eq;
                            ans[ds[i].strpos] = '0'+r;
                            ans[ds[j].strpos] = '0'+a;
                            found = true; break;
                        }
                    }
                    if(found) break;
                }
            }
        }

        if(found) cout << ans << "#\n"; else cout << "No\n";
    }
    return 0;
}
