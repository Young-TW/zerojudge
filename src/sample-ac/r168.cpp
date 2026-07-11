#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> arr(n * n, 0);
        int rem = m;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j < i) {
                    arr[i * n + j] = arr[j * n + i];
                } else {
                    int c = (i == j) ? 1 : 2;
                    if (rem >= c) {
                        arr[i * n + j] = 1;
                        arr[j * n + i] = 1;
                        rem -= c;
                    } else {
                        arr[i * n + j] = 0;
                        arr[j * n + i] = 0;
                    }
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << arr[i * n + j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
