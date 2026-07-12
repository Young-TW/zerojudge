#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void process(const string& line) {
    stringstream ss(line);
    string word;
    string decoded = "";
    int idx = 1;
    while (ss >> word) {
        if (word.length() >= (size_t)idx) {
            decoded += word[idx - 1];
            idx++;
        }
    }
    cout << decoded << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (!line.empty()) break;
    }
    if (line.empty() && cin.eof()) return 0;
    
    int T = stoi(line);
    
    for (int t = 1; t <= T; ++t) {
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) break;
        }
        
        if (line.empty() && cin.eof()) break;
        
        cout << "Case #" << t << ":\n";
        process(line);
        
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) break;
            process(line);
        }
        
        if (t < T) cout << "\n";
    }
    
    return 0;
}
