#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while(cin >> n >> m){
        vector<long long> hx(n), hy(n);
        for(int i = 0; i < n; i++){
            cin >> hx[i] >> hy[i];
        }
        for(int i = 0; i < m; i++){
            long long a, b;
            cin >> a >> b;
            int best = 0;
            long long bestd = (hx[0] - a) * (hx[0] - a) + (hy[0] - b) * (hy[0] - b);
            for(int j = 1; j < n; j++){
                long long d = (hx[j] - a) * (hx[j] - a) + (hy[j] - b) * (hy[j] - b);
                if(d < bestd){
                    bestd = d;
                    best = j;
                }
            }
            cout << best + 1 << "\n";
        }
    }
    return 0;
}
