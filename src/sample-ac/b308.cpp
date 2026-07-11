#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int a[5], b[5], p;
        for (int i = 0; i < 5; ++i) cin >> a[i];
        for (int i = 0; i < 5; ++i) cin >> b[i];
        cin >> p;
        
        int v[5] = {1, 5, 10, 50, 100};
        int V_inko = 0, V_doc = 0;
        for (int i = 0; i < 5; ++i) {
            V_inko += a[i] * v[i];
            V_doc += b[i] * v[i];
        }

        if (V_inko < p) {
            cout << "I HAVE MAGIC!\n";
            continue;
        }

        const int INF = 1e9;

        // reachable[x] = true if Inko can pay exactly x using a subset of her coins
        vector<char> reach(V_inko + 1, 0);
        reach[0] = 1;
        for (int i = 0; i < 5; ++i) {
            int cnt = a[i], val = v[i];
            for (int k = 1; cnt > 0; k <<= 1) {
                int take = min(k, cnt);
                cnt -= take;
                int weight = take * val;
                for (int j = V_inko; j >= weight; --j) {
                    if (reach[j - weight]) reach[j] = 1;
                }
            }
        }

        // docDP[c] = min number of doctor's coins to make change value c
        vector<int> docDP(V_doc + 1, INF);
        docDP[0] = 0;
        for (int i = 0; i < 5; ++i) {
            int cnt = b[i], val = v[i];
            for (int k = 1; cnt > 0; k <<= 1) {
                int take = min(k, cnt);
                cnt -= take;
                int weight = take * val;
                for (int j = V_doc; j >= weight; --j) {
                    if (docDP[j - weight] != INF) {
                        docDP[j] = min(docDP[j], docDP[j - weight] + take);
                    }
                }
            }
        }

        int ans = INF;
        for (int paid = p; paid <= V_inko; ++paid) {
            if (!reach[paid]) continue;
            int change = paid - p;
            if (change <= V_doc && docDP[change] != INF) {
                ans = min(ans, docDP[change]);
            }
        }

        if (ans == INF) {
            cout << "YOU ARE MAGICIAN!\n";
        } else {
            cout << ans << "\n";
        }
    }
    
    return 0;
}
