#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        cin.ignore();
        map<string, string> slogans;
        for (int i = 0; i < N; ++i) {
            string a, b;
            getline(cin, a);
            getline(cin, b);
            slogans[a] = b;
        }
        
        int Q;
        if (!(cin >> Q)) break;
        cin.ignore();
        for (int i = 0; i < Q; ++i) {
            string query;
            getline(cin, query);
            cout << slogans[query] << "\n";
        }
    }
    
    return 0;
}
