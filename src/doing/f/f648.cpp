#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

unsigned long long encode(const string& s) {
    unsigned long long h = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int val;
        if (s[i] >= 'a' && s[i] <= 'z') {
            val = s[i] - 'a' + 27;
        } else {
            val = s[i] - 'A' + 1;
        }
        h = h * 53 + val;
    }
    return h;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line1, line2;
    if (!getline(cin, line1)) return 0;
    getline(cin, line2);

    unordered_map<unsigned long long, int> count;
    count.reserve(1 << 20);
    
    string word;
    for (size_t i = 0; i < line1.size(); ++i) {
        char c = line1[i];
        if (isspace(static_cast<unsigned char>(c))) {
            if (!word.empty()) {
                count[encode(word)]++;
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        count[encode(word)]++;
    }

    word.clear();
    for (size_t i = 0; i < line2.size(); ++i) {
        char c = line2[i];
        if (isspace(static_cast<unsigned char>(c))) {
            if (!word.empty()) {
                auto it = count.find(encode(word));
                if (it == count.end()) {
                    cout << "No\n";
                } else if (it->second == 1) {
                    cout << "Yes\n";
                } else {
                    cout << "Pathetic\n";
                }
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        auto it = count.find(encode(word));
        if (it == count.end()) {
            cout << "No\n";
        } else if (it->second == 1) {
            cout << "Yes\n";
        } else {
            cout << "Pathetic\n";
        }
    }

    return 0;
}
