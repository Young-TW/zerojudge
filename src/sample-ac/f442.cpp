#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> arr(N);
        unordered_map<int, queue<int>> pos;
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
            pos[arr[i]].push(i);
        }
        
        int M;
        cin >> M;
        
        int K;
        cin >> K;
        for (int i = 0; i < K; ++i) {
            int x;
            cin >> x;
            
            int p = pos[x].front();
            pos[x].pop();
            
            arr[p] = M;
            pos[M].push(p);
            
            M = x;
        }
        
        for (int i = 0; i < N; ++i) {
            cout << arr[i];
            if (i < N - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
