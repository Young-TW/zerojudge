#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N;
            if (!(cin >> N)) break;
            vector<int> ages(N);
            for (int i = 0; i < N; ++i) {
                cin >> ages[i];
            }
            cout << "Case " << t << ": " << ages[N / 2] << "\n";
        }
    }
    
    return 0;
}
