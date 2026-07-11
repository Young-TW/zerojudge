#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while(cin >> n){
        long long max_so_far = LLONG_MIN, max_ending = 0;
        for(int i = 0; i < n; ++i){
            long long x;
            cin >> x;
            max_ending = max(x, max_ending + x);
            if(max_ending > max_so_far) max_so_far = max_ending;
        }
        cout << max_so_far << "\n";
    }
    return 0;
}
