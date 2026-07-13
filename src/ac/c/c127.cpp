#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore();
    for (int t = 1; t <= n; ++t) {
        string line;
        getline(cin, line);
        
        double vals[3] = {0, 0, 0}; // P, U, I
        bool found[3] = {false, false, false};
        
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '=' && i > 0) {
                char concept = line[i - 1];
                int idx = -1;
                if (concept == 'P') idx = 0;
                else if (concept == 'U') idx = 1;
                else if (concept == 'I') idx = 2;
                
                if (idx != -1) {
                    size_t j = i + 1;
                    string numStr;
                    while (j < line.size() && (isdigit(line[j]) || line[j] == '.')) {
                        numStr += line[j];
                        j++;
                    }
                    double val = stod(numStr);
                    
                    if (j < line.size()) {
                        char prefix = line[j];
                        if (prefix == 'm') {
                            val *= 1e-3;
                            j++;
                        } else if (prefix == 'k') {
                            val *= 1e3;
                            j++;
                        } else if (prefix == 'M') {
                            val *= 1e6;
                            j++;
                        }
                    }
                    
                    vals[idx] = val;
                    found[idx] = true;
                }
            }
        }
        
        cout << "Problem #" << t << endl;
        cout << fixed << setprecision(2);
        if (!found[0]) {
            cout << "P=" << vals[1] * vals[2] << "W" << endl;
        } else if (!found[1]) {
            cout << "U=" << vals[0] / vals[2] << "V" << endl;
        } else if (!found[2]) {
            cout << "I=" << vals[0] / vals[1] << "A" << endl;
        }
        cout << endl;
    }
    return 0;
}
