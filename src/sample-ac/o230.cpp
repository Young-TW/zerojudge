#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K;
    if (!(cin >> K)) return 0;
    
    for (int t = 1; t <= K; ++t) {
        int N;
        cin >> N;
        
        vector<set<int>> stamps(N);
        map<int, int> owner_count;
        
        for (int i = 0; i < N; ++i) {
            int M;
            cin >> M;
            for (int j = 0; j < M; ++j) {
                int A;
                cin >> A;
                if (stamps[i].find(A) == stamps[i].end()) {
                    stamps[i].insert(A);
                    owner_count[A]++;
                }
            }
        }
        
        int total_unique = 0;
        vector<int> unique_count(N, 0);
        
        for (int i = 0; i < N; ++i) {
            for (int stamp : stamps[i]) {
                if (owner_count[stamp] == 1) {
                    unique_count[i]++;
                }
            }
            total_unique += unique_count[i];
        }
        
        cout << "Case " << t << ":";
        for (int i = 0; i < N; ++i) {
            double percentage = 0.0;
            if (total_unique > 0) {
                percentage = (double)unique_count[i] * 100.0 / total_unique;
            }
            cout << " " << fixed << setprecision(6) << percentage << "%";
        }
        cout << "\n";
    }
    
    return 0;
}
