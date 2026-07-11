#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<unsigned int> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        
        sort(arr.begin(), arr.end());
        
        do {
            for (int i = 0; i < N; ++i) {
                cout << arr[i];
                if (i < N - 1) {
                    cout << ' ';
                }
            }
            cout << '\n';
        } while (next_permutation(arr.begin(), arr.end()));
    }

    return 0;
}
