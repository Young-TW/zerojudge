#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n,tempi,count=0;
    cin >> n;
    vector<int> f(n);
    vector<int> tracked(n);
    for(int i=0;i<n;i++){
        cin >> f[i];
        tracked[i] = 0;
    }
    for(int i=0;i<n;i++){ //從0開始
        if(tracked[i]){ // 追蹤過跳過
            continue;
        }
        tracked[i] = 1; // 自己已經追蹤過了
        tempi = i; // 自己的暫存器
        while(i != f[tempi]){ // 遇到自己結束
            tempi = f[tempi];
            tracked[tempi] = 1;
        }
        count++;
    }
    cout << count;
    return 0;
}