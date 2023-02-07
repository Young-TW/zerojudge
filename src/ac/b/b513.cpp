#include <iostream>
using namespace std;

int main(){
    int n,m;
    cin >> n;
    bool prime=0;
    for(int i=0;i<n;i++){
        cin >> m;
        for(int j=2;j<m/2;j++){
            if(m%j==0){
                prime=1;
            }
        }

        if(!prime)
            cout << "Y" << endl;
        else
            cout << "N" << endl;
        prime=0;
    }
    return 0;
}