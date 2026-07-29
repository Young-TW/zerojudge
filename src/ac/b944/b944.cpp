#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    if(!(cin>>n)) return 0;
    vector<long long> num(n,0), tm(n,0);
    long long a,b;
    string out;
    int rec=0;
    while(cin>>a>>b){
        // decrement / free
        for(int i=0;i<n;i++){
            if(tm[i]!=0) tm[i]--;
            if(tm[i]==0) num[i]=0;
        }
        // find isolated spot (smallest index), else first empty
        int place=-1;
        for(int p=0;p<n;p++){
            if(num[p]==0 && (p==0||num[p-1]==0) && (p==n-1||num[p+1]==0)){place=p;break;}
        }
        if(place==-1){
            for(int p=0;p<n;p++) if(num[p]==0){place=p;break;}
        }
        if(rec>0) out+="\n";
        rec++;
        if(place==-1){
            out+="  Not enough\n";
        } else {
            num[place]=a; tm[place]=b;
        }
        out+="Number:";
        for(int i=0;i<n;i++){ out+=' '; out+=to_string(num[i]); }
        out+="\n  Time:";
        for(int i=0;i<n;i++){ out+=' '; out+=to_string(tm[i]); }
        out+="\n";
    }
    // remove single trailing newline to match sample exactly? keep standard.
    cout<<out;
    return 0;
}
