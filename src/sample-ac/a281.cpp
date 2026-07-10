#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long y;
    int p;
    while(cin >> y >> p){
        long long bestNum = 0, bestDen = 0, bestS = 0;
        bool found = false;
        for(int book = 0; book < p; book++){
            long long s, h, i, k;
            cin >> s >> h >> i >> k;
            long long L = 0, W = 0, C = 0;
            for(long long ing = 0; ing < i; ing++){
                long long a, b, c, d, e;
                cin >> a >> b >> c >> d >> e;
                L += c * b;      // dish level sum
                W += d * e;      // total weight
                C += a * e;      // total material cost
            }
            if(s > y) continue;  // cannot afford
            // C/P = (L * W) / (C * k)
            long long num = L * W;
            long long den = C * k;
            if(!found){
                found = true;
                bestNum = num; bestDen = den; bestS = s;
            } else if(num * bestDen > bestNum * den){
                bestNum = num; bestDen = den; bestS = s;
            }
        }
        if(found) cout << (y - bestS) << "\n";
        else cout << y << "\n";
    }
    return 0;
}
