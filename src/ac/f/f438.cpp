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
        int S, A, F;
        cin >> S >> A >> F;
        
        vector<int> streets(F);
        vector<int> avenues(F);
        
        for (int i = 0; i < F; ++i) {
            cin >> streets[i] >> avenues[i];
        }
        
        sort(streets.begin(), streets.end());
        sort(avenues.begin(), avenues.end());
        
        int best_street = streets[(F - 1) / 2];
        int best_avenue = avenues[(F - 1) / 2];
        
        cout << "(Street: " << best_street << ", Avenue: " << best_avenue << ")\n";
    }

    return 0;
}
