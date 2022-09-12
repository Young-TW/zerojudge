#include <iostream>
#include <vector>
using namespace std;

int main(){
    int r,c,m;
    int b[10][10];
    int mk[10];

    cin >> r >> c >> m;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin >> b[i][j];
        }
    }

    for(int k=0;k<m;k++){
        cin >> mk[k];
    }

    

    return 0;
}