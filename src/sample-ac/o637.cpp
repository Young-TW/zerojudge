#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> first_pos(n + 1, -1);
        long long total_sum = 0;
        
        for (int i = 0; i < 2 * n; ++i) {
            int x;
            cin >> x;
            if (first_pos[x] == -1) {
                first_pos[x] = i;
            } else {
                total_sum += (i - first_pos[x]);
            }
        }
        
        cout << total_sum << "\n";
    }
    
    return 0;
}
