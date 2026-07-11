#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Comparator {
    int len;
    Comparator(int l) : len(l) {}
    bool operator()(const char* a, const char* b) const {
        return strncmp(a, b, len) < 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string S;
    while (cin >> S) {
        int N = S.length();
        bool has_output = false;
        
        for (int d = 1; d < N; ++d) {
            if (N % d != 0) continue;
            
            vector<const char*> parts;
            parts.reserve(N / d);
            for (int i = 0; i < N; i += d) {
                parts.push_back(S.c_str() + i);
            }
            
            sort(parts.begin(), parts.end(), Comparator(d));
            
            string new_S;
            new_S.reserve(N);
            for (const char* p : parts) {
                new_S.append(p, d);
            }
            
            if (new_S != S) {
                cout << new_S << "\n";
                has_output = true;
            }
        }
        
        if (!has_output) {
            cout << "bomb!\n";
        }
    }
    
    return 0;
}
