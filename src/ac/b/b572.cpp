#include <iostream>
using namespace std;

int main(){
    int n;
    short m1,m2,h1,h2,t;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> h1 >> m1 >> h2 >> m2 >> t;
        m1 = 60*h1 + m1;
        m2 = 60*h2 + m2;
        if(t>m2-m1){
            cout << "No" << endl;
        }else{
            cout << "Yes" << endl;
        }
    }
    return 0;
}