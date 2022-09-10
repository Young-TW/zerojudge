#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int a,n,m,tt=0;
    cin >> a;
    for(int i=0;i<a;i++){
        cin >> n >> m;
        for(int j=n;j<m;j++){
            if(sqrt(j) == int(sqrt(j))){
                tt+=j;
            }
        }
        cout << "Case " << i+1 << ": " << tt << endl;
        tt=0;
    }
    return 0;
}