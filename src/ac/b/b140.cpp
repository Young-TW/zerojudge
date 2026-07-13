#include <iostream>
#include <algorithm>
using namespace std;

int dp[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, M;
    while(cin >> T >> M){
        for(int i=0;i<=T;i++) dp[i]=0;
        for(int i=0;i<M;i++){
            int t, v;
            cin >> t >> v;
            for(int j=T;j>=t;j--){
                if(dp[j-t]+v > dp[j]) dp[j]=dp[j-t]+v;
            }
        }
        cout << dp[T] << "\n";
    }
    return 0;
}
