#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int L, M;
    while (cin >> L >> M) {
        vector<bool> trees(L + 1, true);
        for (int i = 0; i < M; ++i) {
            int start, end;
            cin >> start >> end;
            for (int j = start; j <= end; ++j) {
                trees[j] = false;
            }
        }
        
        int remaining = 0;
        for (int i = 0; i <= L; ++i) {
            if (trees[i]) {
                remaining++;
            }
        }
        
        cout << remaining << "\n";
    }
    
    return 0;
}
