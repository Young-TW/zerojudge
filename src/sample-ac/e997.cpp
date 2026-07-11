#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        vector<string> names;
        stringstream ss(line);
        string name;
        while (ss >> name) {
            names.push_back(name);
        }
        
        int n;
        if (!(cin >> n)) break;
        cin.ignore();
        
        cout << names[names.size() - n] << "\n";
    }
    
    return 0;
}
