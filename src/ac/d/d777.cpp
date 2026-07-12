#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

bool isAllUpperAZ(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] < 'A' || s[i] > 'Z') return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    vector<string> dataLines;
    const string inLabel = "输入";
    const string outLabel = "输出";
    
    while (getline(cin, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
            line.pop_back();
        }
        
        if (line.empty()) continue;
        
        if (isAllUpperAZ(line)) {
            dataLines.push_back(line);
            if (dataLines.size() == 3) {
                const string& encrypted = dataLines[0];
                const string& original = dataLines[1];
                const string& toDecrypt = dataLines[2];
                
                char mapTo[256];
                char mapFrom[256];
                memset(mapTo, 0, sizeof(mapTo));
                memset(mapFrom, 0, sizeof(mapFrom));
                bool failed = false;
                
                for (size_t i = 0; i < encrypted.size(); i++) {
                    char x = original[i];
                    char y = encrypted[i];
                    
                    if (mapTo[(unsigned char)x] == 0) {
                        mapTo[(unsigned char)x] = y;
                    } else if (mapTo[(unsigned char)x] != y) {
                        failed = true;
                        break;
                    }
                    
                    if (mapFrom[(unsigned char)y] == 0) {
                        mapFrom[(unsigned char)y] = x;
                    } else if (mapFrom[(unsigned char)y] != x) {
                        failed = true;
                        break;
                    }
                }
                
                if (!failed) {
                    for (int c = 'A'; c <= 'Z'; c++) {
                        if (mapTo[c] == 0) {
                            failed = true;
                            break;
                        }
                    }
                }
                
                if (failed) {
                    cout << "Failed" << "\n";
                } else {
                    string result;
                    for (size_t i = 0; i < toDecrypt.size(); i++) {
                        result += mapFrom[(unsigned char)toDecrypt[i]];
                    }
                    cout << result << "\n";
                }
                
                dataLines.clear();
            }
        } else {
            string out = line;
            size_t pos = out.find(inLabel);
            if (pos != string::npos) {
                out.replace(pos, inLabel.size(), outLabel);
            }
            cout << out << "\n";
        }
    }
    
    return 0;
}
