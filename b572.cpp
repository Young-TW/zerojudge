#include <iostream>
using namespace std;

int main(){
    int n,h1,m1,h2,m2,t;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> h1 >> m1 >> h2 >> m2 >> t;
        m1 = m1 + (h1*60);
        m2 = m2 + (h2*60);
        if(m2-m1>t){
            cout  << "Yes";
        }else{
            cout << "No";
        }
        cout << endl;
    }
    return 0;
}