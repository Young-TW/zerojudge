#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    unordered_map<string, string> dict;
    bool reading_dict = true;
    
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        if (line.empty()) {
            reading_dict = false;
            continue;
        }
        
        if (reading_dict) {
            size_t space_pos = line.find(' ');
            if (space_pos != string::npos) {
                string english = line.substr(0, space_pos);
                string foreign = line.substr(space_pos + 1);
                dict[foreign] = english;
            }
        } else {
            auto it = dict.find(line);
            if (it != dict.end()) {
                cout << it->second << "\n";
            } else {
                cout << "eh\n";
            }
        }
    }
    
    return 0;
}
