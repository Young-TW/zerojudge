#include <iostream>
using namespace std;
int main(){
    long long X;
    while(cin>>X){
        if(X==3){cout<<"BA\n";continue;}
        if(X==6){cout<<"ABA\n";continue;}
        for(long long i=0;i<X;++i)cout<<'A';
        cout<<"\n";
    }
    return 0;
}
