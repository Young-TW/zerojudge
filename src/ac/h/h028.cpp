#include <iostream>
using namespace std;
int n,l,highest,num;
int X[100005],H[100005],le[100005];

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> l;
    X[0]=H[0]=0;
    for (int i=1; i<=n; i++){
        cin >> X[i];
        le[i]=i-1;
    }
    for (int i=1; i<=n; i++)
        cin >> H[i];
    for(int i=1;i<=n;i++){
        if((X[i]-H[i]>=X[le[i]]) || (X[i]+H[i]<=X[i+1])){
            num++;
            le[i+1]=le[i];
            highest=max(highest,H[i]);
            while(1){
                if(le[i+1]>0 && X[le[i+1]]+H[le[i+1]]<=X[i+1]){
                    num++;
                    highest=max(highest,H[le[i+1]]);
                    le[i+1]=le[le[i+1]];
                }else{
                    break;
                }
            }
        }
    }

    if(num==0){
        cout << 0 << endl;
        cout << 0 << endl;
    }
    else{
        cout << num << endl;
        cout << highest << endl;
    }
    return 0;
}