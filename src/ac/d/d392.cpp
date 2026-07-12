#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        long long sum = 0;
        long long num = 0;
        bool in_num = false;
        
        for (char c : line) {
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                in_num = true;
            } else {
                if (in_num) {
                    sum += num;
                    num = 0;
                    in_num = false;
                }
            }
        }
        
        if (in_num) {
            sum += num;
        }
        
        cout << sum << '\n';
    }
    
    return 0;
}
