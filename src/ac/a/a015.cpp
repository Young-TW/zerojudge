#include <iostream>
using namespace std;

int main(){
    int x,y;
    int m[100][100];
    while(cin >> x >> y){
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                cin >> m[i][j];
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<x;j++){
                cout << m[j][i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}