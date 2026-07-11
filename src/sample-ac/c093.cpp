#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (cin >> n) {
        while (n--) {
            string left[3], right[3], res[3];
            for (int i = 0; i < 3; ++i) {
                cin >> left[i] >> right[i] >> res[i];
            }
            
            for (char c = 'A'; c <= 'L'; ++c) {
                for (int isLight = 0; isLight <= 1; ++isLight) {
                    bool valid = true;
                    for (int i = 0; i < 3; ++i) {
                        int lw = 0, rw = 0;
                        for (char x : left[i]) {
                            if (x == c) lw += (isLight ? -1 : 1);
                        }
                        for (char x : right[i]) {
                            if (x == c) rw += (isLight ? -1 : 1);
                        }
                        
                        string expected;
                        if (lw > rw) {
                            expected = "up";
                        } else if (lw < rw) {
                            expected = "down";
                        } else {
                            expected = "even";
                        }
                        
                        if (expected != res[i]) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        cout << c << " is the counterfeit coin and it is " 
                             << (isLight ? "light." : "heavy.") << "\n";
                    }
                }
            }
        }
    }
    
    return 0;
}
