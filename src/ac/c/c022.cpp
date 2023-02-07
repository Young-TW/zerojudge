#include <iostream>
using namespace std;

int main(){
    int t,n,m,tt;
    cin >> t;
    for(int i=0;i<t;i++){
        cin >> n >> m;
        tt=0;
        if(n%2==0)
            n++;
        for(int j=n;j<=m;j+=2){
            tt+=j;
        }
        cout << "Case " << i+1 << ": " << tt << endl;
    }
    return 0;
}