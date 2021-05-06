#include <iostream> 
using namespace std;
int main(){
    int x;
    while (cin >> x){
        if ((x%4 == 0 && x%100 != 0) || x%400 == 0){
            cout <<"閏年\n"; 
        }
        else{
            cout <<"平年\n";
        }
    }
    return 0;
}