#include <iostream>
#include <vector>
#define int long long
using namespace std;

int main(){
    int r,c,m;
    int b[10][10];
    int mm[10];

    cin >> r >> c >> m;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin >> b[i][j];
        }
    }

    for(int i=0;i<m;i++){
        cin >> mm[i];
    }

    

    return 0;
}