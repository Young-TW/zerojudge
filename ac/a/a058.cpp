#include <iostream>
using namespace std;

int main(){
    int n;
    int a=0,b=0,c=0,inp;
    cin >> n;
    for(int d=0;d<n;d++){
    	cin >> inp;
    	if(inp%3==0){
    		a++;
		}else if(inp%3==1){
			b++;
		}else{
			c++;
		}
	}
	cout << a << " " << b << " " << c;
    return 0;
}