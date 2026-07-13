#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while(cin >> N){
        vector<long long> a(N);
        for(int i=0;i<N;i++) cin >> a[i];
        sort(a.begin(), a.end());
        vector<long long> sq(N);
        for(int i=0;i<N;i++) sq[i] = a[i]*a[i];
        long long ans = 0;
        for(int k=N-1;k>=2;k--){
            long long target = sq[k];
            int i=0, j=k-1;
            while(i<j){
                long long s = sq[i]+sq[j];
                if(s==target){
                    ans++;
                    i++;
                    j--;
                } else if(s<target){
                    i++;
                } else {
                    j--;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
