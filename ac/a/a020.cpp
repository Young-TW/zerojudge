#include <iostream>
#include <string>
using namespace std;

int main(){
    int a[26] ={1,10,19,28,37,46,55,64,39,73,82,2,11,20,48,29,38,47,56,65,74,83,21,3,12,30};
    string s;
    cin >> s;
    int tt = a[s[0]-'A'];
    for(int i=1;i<s.length();i++)
        tt+=(s[i]-'0')*(9-i);
    
    tt+=s[9] - '0';
    if(tt%10==0)
        cout<<"real"<<endl;
    else
        cout<<"fake"<<endl;
    return 0;
}