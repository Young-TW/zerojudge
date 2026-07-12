#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        int total_slices = 8 * M;
        int min_slices = 2 * N;
        int max_slices = 3 * N;
        
        if (total_slices < min_slices) {
            cout << "Not enough\n";
        } else if (total_slices > max_slices) {
            cout << "Too much\n";
        } else {
            cout << "Yes\n";
        }
    }
    
    return 0;
}
