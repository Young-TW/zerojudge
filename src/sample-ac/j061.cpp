#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    while (cin >> n) {
        if (n == 0) break;
        cin.ignore();
        cout << "Case " << case_num << ":\n";
        cout << "#include<string.h>\n";
        cout << "#include<stdio.h>\n";
        cout << "int main()\n";
        cout << "{\n";
        
        for (int i = 0; i < n; ++i) {
            string line;
            getline(cin, line);
            cout << "printf(\"";
            for (char c : line) {
                if (c == '\\' || c == '"') {
                    cout << '\\';
                }
                cout << c;
            }
            cout << "\\n\");\n";
        }
        
        cout << "printf(\"\\n\");\n";
        cout << "return 0;\n";
        cout << "}\n";
        
        case_num++;
    }
    return 0;
}
