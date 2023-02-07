#include <iostream>
using namespace std;

int main(){
    long long int n,m,sum,count;
    while(cin >> n >> m){
        sum = 0;
        count = 0;
        do {
            sum += n + count++;
        } while (sum <= m);
        cout << count << endl;
    }
    return 0;
}