#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        bool hasContent = false;
        for (size_t k = 0; k < line.size(); k++) {
            if (!isspace((unsigned char)line[k])) { hasContent = true; break; }
        }
        if (!hasContent) {
            cout << "\n";
            continue;
        }
        size_t i = 0;
        while (i < line.size() && isspace((unsigned char)line[i])) i++;
        bool neg = false;
        if (i < line.size() && (line[i] == '-' || line[i] == '+')) {
            if (line[i] == '-') neg = true;
            i++;
        }
        string num;
        while (i < line.size() && isdigit((unsigned char)line[i])) {
            num += line[i];
            i++;
        }
        reverse(num.begin(), num.end());
        size_t j = 0;
        while (j + 1 < num.size() && num[j] == '0') j++;
        string result = num.substr(j);
        if (result.empty()) result = "0";
        if (neg && result != "0") cout << "-";
        cout << result << "\n";
    }
    return 0;
}
