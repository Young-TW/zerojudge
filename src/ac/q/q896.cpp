#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
    string s;
    while (getline(cin, s)) {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == string::npos) continue;
        size_t end = s.find_last_not_of(" \t\r\n");
        string token = s.substr(start, end - start + 1);
        
        bool is_num = !token.empty();
        for (size_t i = 0; i < token.size(); ++i) {
            if (!isdigit(static_cast<unsigned char>(token[i]))) {
                is_num = false;
                break;
            }
        }
        
        if (is_num) {
            long long a = stoll(token);
            double ans = a / 2.0;
            cout << fixed << setprecision(1) << ans << "\n";
        } else {
            cout << "格式為：ans.d(d為零依然需輸出）\n";
        }
    }
    return 0;
}
