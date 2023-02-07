#include <iostream>
using namespace std;

int main(){
    int a,b,c;
    cin >> a >> b >> c;
    if(a>b)
        swap(a,b);
    if(b>c)
        swap(b,c);
    if(a>b)
        swap(a,b);
    
    cout << a << " " << b << " " << c << endl;
    
    if(a+b<=c){
        cout << "No";
    }else if((a*a)+(b*b)<c*c){
        cout << "Obtuse";
    }else if((a*a)+(b*b)==c*c){
        cout << "Right";
    }else if((a*a)+(b*b)>c*c){
        cout << "Acute";
    }
    return 0;
}