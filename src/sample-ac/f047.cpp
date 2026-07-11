#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> v;
    string s;
    while (cin >> s) {
        v.push_back(s);
    }
    
    vector<string> col[3];
    for (size_t i = 0; i < v.size(); ++i) {
        col[i % 3].push_back(v[i]);
    }
    
    for (int i = 0; i < 3; ++i) {
        for (size_t j = 0; j < col[i].size(); ++j) {
            if (j > 0) cout << " ";
            cout << col[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}
