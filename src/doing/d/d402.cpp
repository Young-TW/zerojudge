#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char c;
    string numStr = "";
    int nums[2];
    int idx = 0;
    
    while (cin.get(c)) {
        if (c >= '0' && c <= '9') {
            numStr += c;
        } else {
            if (!numStr.empty()) {
                if (idx < 2) {
                    nums[idx++] = atoi(numStr.c_str());
                }
                numStr.clear();
            }
        }
    }
    
    if (!numStr.empty()) {
        if (idx < 2) {
            nums[idx++] = atoi(numStr.c_str());
        }
    }
    
    if (idx == 2) {
        cout << nums[0] << " " << nums[1] << " " << nums[0] + nums[1] << "\n";
    }
    
    return 0;
}
