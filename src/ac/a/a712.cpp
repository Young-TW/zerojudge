#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    map<string,int> cnt;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        string num;
        for(char c : s){
            if(c=='-') continue;
            char d;
            if(c>='0'&&c<='9') d=c;
            else {
                if(c>='A'&&c<='C') d='2';
                else if(c>='D'&&c<='F') d='3';
                else if(c>='G'&&c<='I') d='4';
                else if(c>='J'&&c<='L') d='5';
                else if(c>='M'&&c<='O') d='6';
                else if(c=='P'||c=='R'||c=='S') d='7';
                else if(c>='T'&&c<='V') d='8';
                else d='9';
            }
            num.push_back(d);
        }
        cnt[num]++;
    }
    bool any=false;
    for(auto& p : cnt){
        if(p.second>1){
            cout<<p.first.substr(0,3)<<"-"<<p.first.substr(3)<<" "<<p.second<<"\n";
            any=true;
        }
    }
    if(!any) cout<<"No duplicates.\n";
    return 0;
}
