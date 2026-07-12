#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int total_coke = 0;
        int phos_coke = 0;
        
        for (size_t i = 0; i < s.length(); ) {
            if (s[i] == 'C') {
                if (i + 1 < s.length() && s[i + 1] == 'A') {
                    total_coke++;
                    phos_coke++;
                    i += 2;
                } else {
                    total_coke++;
                    i++;
                }
            } else {
                i++;
            }
        }
        
        for (size_t i = 0; i < s.length(); ) {
            if (s[i] == 'F') {
                cout << total_coke << " " << phos_coke << "\n";
                i++;
            } else if (s[i] == 'C') {
                if (i + 1 < s.length() && s[i + 1] == 'A') {
                    total_coke--;
                    phos_coke--;
                    i += 2;
                } else {
                    total_coke--;
                    i++;
                }
            } else {
                i++;
            }
        }
    }
    
    return 0;
}
