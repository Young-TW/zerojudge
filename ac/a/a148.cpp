#include <iostream>
using namespace std;

int main(){
    double n,tt,reg;
    while(cin >> n){
        tt=0;
        for(int i=0;i<n;i++){
            cin >> reg;
            tt += reg;
        }
        if((tt/n)>59)
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }
    return 0;
}