#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x1, y1, x2, y2, x3, y3, x4, y4;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        int left = max(x1, x3);
        int right = min(x2, x4);
        int bottom = max(y1, y3);
        int top = min(y2, y4);
        
        int w = right - left;
        int h = top - bottom;
        
        if (w > 0 && h > 0) {
            cout << w * h << "\n";
        } else {
            cout << "banana\n";
        }
    }
    
    return 0;
}
