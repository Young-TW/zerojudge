#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long t, s, p;
    const long long d[5] = {5, 6, 8, 9, 0};
    while(cin >> t >> s >> p){
        long long ans = 0;
        long long per = t / 5;
        long long rem = t;
        for(int i = 0; i < 5 && s > 0 && rem > 0; i++){
            long long cnt = per + (i == 0 ? 1 : 0);
            cnt = min(cnt, min(s, rem));
            ans += (p * d[i] / 10) * cnt;
            s -= cnt;
            rem -= cnt;
        }
        cout << ans << '\n';
    }
    return 0;
}
