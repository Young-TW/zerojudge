#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        size_t pos_if = string::npos;
        for (size_t i = 0; i + 1 < line.size(); ++i) {
            if (line[i] == 'i' && line[i+1] == 'f') {
                bool valid = true;
                if (i > 0 && (isalnum((unsigned char)line[i-1]) || line[i-1] == '_')) valid = false;
                if (i + 2 < line.size() && (isalnum((unsigned char)line[i+2]) || line[i+2] == '_')) valid = false;
                if (valid) {
                    pos_if = i;
                    break;
                }
            }
        }
        
        if (pos_if == string::npos) {
            cout << line << "\n";
            continue;
        }
        
        size_t pos_open = line.find('(', pos_if);
        if (pos_open == string::npos) {
            cout << line << "\n";
            continue;
        }
        
        int depth = 1;
        size_t pos_close = string::npos;
        for (size_t i = pos_open + 1; i < line.size(); ++i) {
            if (line[i] == '(') depth++;
            else if (line[i] == ')') {
                depth--;
                if (depth == 0) {
                    pos_close = i;
                    break;
                }
            }
        }
        
        if (pos_close == string::npos) {
            cout << line << "\n";
            continue;
        }
        
        string prefix = line.substr(0, pos_if);
        string if_part = line.substr(pos_if, pos_close - pos_if + 1);
        string statement_part = line.substr(pos_close + 1);
        
        statement_part = trim(statement_part);
        if (!statement_part.empty() && statement_part.back() == ';') {
            statement_part.pop_back();
            statement_part = trim(statement_part);
        }
        
        cout << prefix << statement_part << " " << if_part << ";\n";
    }
    return 0;
}
