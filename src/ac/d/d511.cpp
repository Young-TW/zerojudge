#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int ans = 0;
    for (int i = 0; i < 5; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        int arr[3] = {a, b, c};
        sort(arr, arr + 3);
        if (arr[0] + arr[1] > arr[2]) {
            ++ans;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
