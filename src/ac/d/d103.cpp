#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        // Strip trailing \r or \n
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
            line.pop_back();
        }

        // Determine if this line is an ISBN (starts with a digit, ignoring whitespace)
        bool isISBN = false;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == ' ' || line[i] == '\t') continue;
            isISBN = (line[i] >= '0' && line[i] <= '9');
            break;
        }

        if (isISBN) {
            int sum = 0, idx = 1;
            char checkChar = 0;
            for (size_t i = 0; i < line.size(); i++) {
                char c = line[i];
                if (c == '-' || c == ' ' || c == '\t') continue;
                if (idx <= 9) {
                    sum += (c - '0') * idx;
                    idx++;
                } else {
                    checkChar = c;
                }
            }
            int mod = sum % 11;
            char correct = (mod == 10) ? 'X' : (char)('0' + mod);
            if (checkChar == correct) {
                cout << "Right" << endl;
            } else {
                string out = line;
                for (int i = (int)out.size() - 1; i >= 0; i--) {
                    if (out[i] != '-' && out[i] != ' ' && out[i] != '\t') {
                        out[i] = correct;
                        break;
                    }
                }
                cout << out << endl;
            }
        } else {
            // Replace "输入" (UTF-8: E8 BE 93 E5 85 A5) with "输出" (UTF-8: E8 BE 93 E5 87 BA)
            string out;
            for (size_t i = 0; i < line.size(); ) {
                if (i + 6 <= line.size() &&
                    (unsigned char)line[i]   == 0xE8 &&
                    (unsigned char)line[i+1] == 0xBE &&
                    (unsigned char)line[i+2] == 0x93 &&
                    (unsigned char)line[i+3] == 0xE5 &&
                    (unsigned char)line[i+4] == 0x85 &&
                    (unsigned char)line[i+5] == 0xA5) {
                    out += (char)0xE8; out += (char)0xBE; out += (char)0x93;
                    out += (char)0xE5; out += (char)0x87; out += (char)0xBA;
                    i += 6;
                } else {
                    out += line[i];
                    i++;
                }
            }
            cout << out << endl;
        }
    }
    return 0;
}
