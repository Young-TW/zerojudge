#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first = true;
    while(cin >> n){
        vector<long long> c(n+1);
        for(int i=1;i<=n;i++) cin >> c[i];
        long long m, p1, s1, s2;
        cin >> m >> p1 >> s1 >> s2;
        
        c[p1] += s1;
        
        long long dragon = 0, tiger = 0;
        for(int i=1;i<=n;i++){
            if(i < m) dragon += c[i] * (m - i);
            else if(i > m) tiger += c[i] * (i - m);
        }
        
        long long diff = dragon - tiger;
        
        long long best = LLONG_MAX;
        int bestP = 1;
        for(int p2 = 1; p2 <= n; p2++){
            long long newdiff;
            if(p2 < m) newdiff = diff + s2 * (m - p2);
            else if(p2 > m) newdiff = diff - s2 * (p2 - m);
            else newdiff = diff;
            long long absv = newdiff < 0 ? -newdiff : newdiff;
            if(absv < best){
                best = absv;
                bestP = p2;
            }
        }
        
        if(!first) cout << "\n";
        cout << bestP << "\n";
        first = false;
    }
    return 0;
}
