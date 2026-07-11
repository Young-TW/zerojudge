#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore();
    
    vector<string> arr(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, arr[i]);
    }
    
    sort(arr.begin(), arr.end());
    
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << '\n';
    }
    
    return 0;
}
