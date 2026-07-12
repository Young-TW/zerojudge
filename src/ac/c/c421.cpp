#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    multiset<int> s;
    while (getline(cin, line)) {
        if (line.empty()) {
            cout << "\n";
            continue;
        }
        
        bool isDataLine = true;
        for (char c : line) {
            if (!isdigit(c) && !isspace(c) && c != '-') {
                isDataLine = false;
                break;
            }
        }
        
        if (isDataLine) {
            const char* p = line.c_str();
            char* end;
            bool hasOutput = false;
            while (*p) {
                while (*p && isspace(*p)) p++;
                if (!*p) break;
                
                long val = strtol(p, &end, 10);
                if (p == end) {
                    p++;
                } else {
                    int x = (int)val;
                    if (x == 0) {
                        s.clear();
                    } else if (x == -2) {
                        if (!s.empty()) {
                            auto it = s.end();
                            --it;
                            cout << *it << " ";
                            s.erase(it);
                            hasOutput = true;
                        }
                    } else if (x == -1) {
                        if (!s.empty()) {
                            auto it = s.begin();
                            cout << *it << " ";
                            s.erase(it);
                            hasOutput = true;
                        }
                    } else {
                        s.insert(x);
                    }
                    p = end;
                }
            }
            if (hasOutput) {
                cout << "\n";
            }
        } else {
            cout << line << "\n";
        }
    }
    return 0;
}
