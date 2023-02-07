#include <iostream>
#include <string>
using namespace std;

int main(){
    int data;
    cin >> data;
    string n;
    int output;
    for (int i=0;i<data;i++){
        cin >> n;
        output=1;
        for(int j=0;j<n.length();j++){
            output *= n[j]-48; //-48 is for char to int
        }
        cout << output << endl;
    }
    return 0;
}