#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<double> v(N);
            for (int i = 0; i < N; i++) {
                cin >> v[i];
            }
            sort(v.begin(), v.end());
            
            int guards = 0;
            double cover = -1.0;
            for (int i = 0; i < N; i++) {
                if (v[i] > cover) {
                    guards++;
                    cover = v[i] + 2.0;
                }
            }
            cout << guards << "\n";
        }
    }
    return 0;
}
