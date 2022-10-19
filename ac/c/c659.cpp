#include <iostream>
#include <string>
using namespace std;

int main(){
    string n,m;
    int i=0;
    cin >> n;
    while(cin >> m){
        if(i){
            cout << " " << n << " ";
        }
        cout << m;
        i++;
    }
    return 0;
}