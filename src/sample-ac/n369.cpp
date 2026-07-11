#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        unordered_set<string> used_emails;
        for (int i = 0; i < N; ++i) {
            string a, b;
            cin >> a >> b;
            if (used_emails.find(a) == used_emails.end()) {
                used_emails.insert(a);
                cout << "welcome, " << b << "\n";
            } else {
                cout << b << " account has been used\n";
            }
        }
    }
    
    return 0;
}
