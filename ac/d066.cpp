#include <iostream>
using namespace std;

int main(){
    int a,b;
    cin >> a >> b;
    a = (a*60)+b;
    if(450<=a && a<1020){
    	cout << "At School";
	}else{
		cout << "Off School";
	}
    return 0;
}