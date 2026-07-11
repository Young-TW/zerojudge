#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        vector<int> v;
        int x;
        while (ss >> x) {
            v.push_back(x);
        }
        if (!v.empty()) {
            cout << v[v.size() / 2] << "\n";
            break;
        }
    }
    
    return 0;
}
