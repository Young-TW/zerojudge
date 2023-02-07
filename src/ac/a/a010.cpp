#include <iostream>
using namespace std;

int main(){
    long long n;
    cin >> n;
    long long num = 2;
    long long count;
    bool first_time = 1;
    while(n>=num){
        count=0;
        while(n%num==0){
            n/=num;
            count++;
        }
        if(count>1 && first_time){
            cout << num << "^" << count;
            first_time=0;
        }else if(count==1 && first_time){
            cout << num;
            first_time=0;
        }else if(count>1 && !first_time){
            cout << " * " << num << "^" << count;
        }else if(count==1 && !first_time){
            cout << " * " << num;
        }else{
            num++;
        }
    }
    return 0;
}