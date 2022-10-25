#include <bits/stdc++.h>
using namespace std;

int pl(int n){
    if(n<0){
        return -n;
    }
    return n;
}

int main(){
    int n,lx,ly,x,y,maxx=0,minn=INT_MAX;
    cin >> n;
    int d;
    for(int i=0;i<n;i++){
        cin >> x >> y;
        if(i==0){
            lx = x;
            ly = y;
            continue;
        }
        d = pl(x-lx)+pl(y-ly);
        lx = x;
        ly = y;
        maxx = max(maxx,d);
        minn = min(minn,d);
    }
    cout << maxx << " " << minn << endl;
    return 0;
}