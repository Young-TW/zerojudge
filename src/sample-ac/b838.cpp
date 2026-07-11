#include <iostream>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if(!(cin>>t)) return 0;
    while(t--){
        string s;
        cin>>s;
        int depth=0, pairs=0;
        bool ok=true;
        for(char c:s){
            if(c=='('){
                depth++;
            }else if(c==')'){
                if(depth==0){ ok=false; break; }
                depth--;
                pairs++;
            }
        }
        if(ok && depth==0) cout<<pairs<<"\n";
        else cout<<0<<"\n";
    }
    return 0;
}
