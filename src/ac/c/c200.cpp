#include <iostream>
#include <string>
using namespace std;

bool isPlate(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'))) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    int remaining = 0;
    while (getline(cin, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) 
            line.pop_back();
        if (line.empty()) continue;
        
        if (!isPlate(line)) {
            // Label line: replace 入(E5 85 A5) with 出(E5 87 BA)
            string out;
            for (size_t i = 0; i < line.size(); ) {
                if (i + 3 <= line.size() && 
                    (unsigned char)line[i] == 0xE5 && 
                    (unsigned char)line[i+1] == 0x85 && 
                    (unsigned char)line[i+2] == 0xA5) {
                    out += (char)0xE5;
                    out += (char)0x87;
                    out += (char)0xBA;
                    i += 3;
                } else {
                    out += line[i];
                    i++;
                }
            }
            cout << out << "\n";
        } else if (remaining > 0) {
            // Plate line
            long long val = 0;
            for (size_t i = 0; i < line.size(); i++) {
                char c = line[i];
                int d;
                if (c >= '0' && c <= '9') d = c - '0';
                else d = c - 'A' + 10;
                val = (val * 36 + d) % 1688;
            }
            cout << (val + 1) << "\n";
            remaining--;
        } else {
            // T line
            remaining = 0;
            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] >= '0' && line[i] <= '9') 
                    remaining = remaining * 10 + (line[i] - '0');
            }
        }
    }
    return 0;
}
