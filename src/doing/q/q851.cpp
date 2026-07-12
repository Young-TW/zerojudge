#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    while (getline(cin, line)) {
        string result = "";
        int space_count = 0;
        
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == ' ') {
                space_count++;
            } else {
                if (space_count > 0) {
                    for (int j = 0; j < space_count - 1; ++j) {
                        result += '*';
                    }
                    result += ' ';
                    space_count = 0;
                }
                result += line[i];
            }
        }
        
        if (space_count > 0) {
            for (int j = 0; j < space_count; ++j) {
                result += '*';
            }
            result += ' ';
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
