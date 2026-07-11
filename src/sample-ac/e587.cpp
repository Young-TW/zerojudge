#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x;
    while (cin >> x && x != 0) {
        int low = 1, high = 10;
        string s1, s2;
        bool dishonest = false;
        
        while (cin >> s1 >> s2) {
            if (s1 == "right") {
                if (x < low || x > high) {
                    dishonest = true;
                }
                break;
            } else if (s1 == "too") {
                if (s2 == "high") {
                    high = min(high, x - 1);
                } else if (s2 == "low") {
                    low = max(low, x + 1);
                }
                cin >> x;
            }
        }
        
        if (dishonest) {
            cout << "Stan is dishonest\n";
        } else {
            cout << "Stan may be honest\n";
        }
    }
    
    return 0;
}
