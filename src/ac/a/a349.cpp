#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool isNumber(const string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') start = 1;
    if (start >= (int)s.size()) return false;
    for (int i = start; i < (int)s.size(); ++i) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string token;
    bool firstCase = true;
    
    while (cin >> token) {
        if (!isNumber(token)) {
            if (token == "LOAD" || token == "STORE" || token == "ADD" || token == "MOVE") {
                continue;
            }
            // Label like "輸入範例一" -> output "輸出範例一"
            // "輸入" is 6 bytes in UTF-8
            if (!firstCase) cout << "\n\n";
            firstCase = false;
            cout << "輸出" << token.substr(6) << "\n";
            continue;
        }
        
        vector<int> memory(8);
        vector<int> registers(4, 0);
        
        memory[0] = stoi(token);
        for (int i = 1; i < 8; ++i) {
            cin >> memory[i];
        }
        
        int N;
        cin >> N;
        
        for (int i = 0; i < N; ++i) {
            string op;
            cin >> op;
            if (op == "LOAD") {
                int rd, ms;
                cin >> rd >> ms;
                registers[rd] = memory[ms];
            } else if (op == "STORE") {
                int md, rs;
                cin >> md >> rs;
                memory[md] = registers[rs];
            } else if (op == "ADD") {
                int rd, rs1, rs2;
                cin >> rd >> rs1 >> rs2;
                registers[rd] = registers[rs1] + registers[rs2];
            } else if (op == "MOVE") {
                int rd, rs;
                cin >> rd >> rs;
                registers[rd] = registers[rs];
            }
        }
        
        cout << registers[0] << "\n" << memory[0] << "\n";
    }

    return 0;
}
