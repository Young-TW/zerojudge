#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAXN = 100005;
    int pref[MAXN];
    pref[0] = 0;
    int A_prev = 0;
    for (int i = 1; i < MAXN; ++i) {
        int A_curr = A_prev ^ i;
        pref[i] = pref[i - 1] ^ A_curr;
        A_prev = A_curr;
    }
    
    int a, b;
    while (cin >> a >> b) {
        cout << (pref[b] ^ pref[a - 1]) << "\n";
    }
    
    return 0;
}
