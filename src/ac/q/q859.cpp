#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const char* med[12] = {
        "Aspect of Combat",      // 0
        "Ringmaster Scarr",      // 1
        "Night Rose",            // 2
        "Aspect of Speed",       // 3
        "Shrouded Striker",      // 4
        "Unstoppable",           // 5
        "Aspect of Siphon",      // 6
        "Infernal Defenses",     // 7
        "The Machinist",         // 8
        "Shogun X",              // 9
        "Megalo Don",            //10
        "Aspect of Agility"      //11
    };
    
    long long n;
    while (cin >> n) {
        cout << med[n % 12] << '\n';
    }
    return 0;
}
