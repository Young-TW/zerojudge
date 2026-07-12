#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            int L;
            cin >> L;
            vector<int> arr(L);
            for (int i = 0; i < L; ++i) {
                cin >> arr[i];
            }
            
            int swaps = 0;
            for (int i = 0; i < L; ++i) {
                for (int j = 0; j < L - 1 - i; ++j) {
                    if (arr[j] > arr[j + 1]) {
                        swap(arr[j], arr[j + 1]);
                        swaps++;
                    }
                }
            }
            
            cout << "Optimal train swapping takes " << swaps << " swaps.\n";
        }
    }
    
    return 0;
}
