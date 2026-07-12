#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        string num = s;
        size_t dot_pos = num.find('.');
        if (dot_pos == string::npos) {
            num += ".0000";
        } else {
            int decimal_places = num.length() - dot_pos - 1;
            for (int i = 0; i < 4 - decimal_places; ++i) {
                num += '0';
            }
        }
        
        string abs_num = num;
        if (!abs_num.empty() && (abs_num[0] == '-' || abs_num[0] == '+')) {
            abs_num.erase(0, 1);
        }
        
        cout << '|' << num << "|=" << abs_num << '\n';
    }
    
    return 0;
}
