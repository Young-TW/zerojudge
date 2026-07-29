#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while(cin >> n >> m){
        vector<int> v(n + 1, 0);
        for(int i = 1; i <= n; i++){
            cin >> v[i];
        }
        int ans = 0;
        int Max = v[m];
        for(int i = m - 1; i >= 1; i--){
            if(Max < v[i]){
                ans++;
                Max = v[i];
            }
        }
        Max = v[m];
        for(int i = m + 1; i <= n; i++){
            if(Max < v[i]){
                ans++;
                Max = v[i];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
