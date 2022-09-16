#include <iostream>
using namespace std;

int main(){
    int a,b,n,input,ans=0;
    cin >> a >> b >> n;
    int cin_a=0,cin_b=0;
    for(int i=0;i<n;i++){
        cin_a=0,cin_b=0;
        cin >> input;
        while(input){
            if(input == a)
                cin_a++;
            if(input == -a)
                cin_a--;
            if(input == b)
                cin_b++;
            if(input == -b)
                cin_b--;
            
            cin >> input;
        }
        if(cin_a>0 && cin_b>0)
            ans++;
    }
    cout << ans;
    return 0;
}