#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        int ab = a * 10 + b;
        int bc = b * 10 + c;
        
        int ans = 0;
        ans = max(ans, a + b + c);
        ans = max(ans, a + b * c);
        ans = max(ans, a * b + c);
        ans = max(ans, a * b * c);
        ans = max(ans, ab + c);
        ans = max(ans, ab * c);
        ans = max(ans, a + bc);
        ans = max(ans, a * bc);
        
        cout << ans << "\n";
    }
    
    return 0;
}
