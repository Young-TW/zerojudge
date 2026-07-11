#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    int case_num = 1;
    while (cin >> N >> K) {
        vector<vector<int>> restaurants(N, vector<int>(K));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < K; ++j) {
                cin >> restaurants[i][j];
            }
        }
        
        vector<pair<long long, int>> points(N);
        vector<int> query(K);
        int Q;
        cin >> Q;
        for (int q = 0; q < Q; ++q) {
            for (int j = 0; j < K; ++j) {
                cin >> query[j];
            }
            int P;
            cin >> P;
            
            for (int i = 0; i < N; ++i) {
                long long dist = 0;
                for (int j = 0; j < K; ++j) {
                    long long diff = query[j] - restaurants[i][j];
                    dist += diff * diff;
                }
                points[i] = {dist, i + 1};
            }
            
            partial_sort(points.begin(), points.begin() + P, points.end());
            
            cout << "Case " << case_num++ << ": " << P;
            for (int i = 0; i < P; ++i) {
                cout << " " << points[i].second;
            }
            cout << "\n";
        }
    }
    return 0;
}
