#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> delay;
    long long money = 0;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        if(b > 100){
            money += (long long)(b - 100) * 5;
            delay.push_back(a);
        }
    }
    if(delay.empty()){
        cout << 0 << "\n";
    } else {
        sort(delay.begin(), delay.end());
        for(size_t i = 0; i < delay.size(); i++){
            if(i) cout << " ";
            cout << delay[i];
        }
        cout << "\n" << money << "\n";
    }
    return 0;
}
