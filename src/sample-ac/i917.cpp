#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int x;
        int max_sum = 0;
        int current_sum = 0;
        
        while (ss >> x) {
            current_sum += x;
            if (current_sum < 0) {
                current_sum = 0;
            }
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
        
        cout << max_sum << "\n";
    }
    
    return 0;
}
