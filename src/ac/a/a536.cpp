#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    if(!(cin >> N)) return 0;
    while(N--){
        long long e, f, c;
        cin >> e >> f >> c;
        long long total = e + f;
        long long drank = 0;
        while(total >= c){
            long long newSodas = total / c;
            drank += newSodas;
            total = total % c + newSodas;
        }
        cout << drank << "\n";
    }
    return 0;
}
