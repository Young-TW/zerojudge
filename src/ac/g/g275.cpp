#include <iostream>
using namespace std;

int main(){
    int n;
    bool a,b,c;
    int d[14];
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<14;j++){
            cin >> d[j];
        }
        a = !(d[1] == d[5] && d[1] != d[3] && d[8] == d[12] && d[8] != d[10]);
        b = !(d[6] == 1 && d[13] == 0);
        c = !(d[1] != d[8] && d[5] != d[12] && d[3] != d[10]);
        if(a){
            cout << "A";
        }
        if(b){
            cout << "B";
        }
        if(c){
            cout << "C";
        }
        if(a==0 && b==0 && c==0){
            cout << "None";
        }
        cout << endl;
    }
    return 0;
}