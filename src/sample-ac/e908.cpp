#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    map<string, int> mp;
    for (int i = 0; i < 7; ++i) {
        mp[days[i]] = i;
    }
    
    string s;
    long long n;
    while (cin >> s >> n) {
        int idx = mp[s];
        cout << days[(idx + n % 7) % 7] << "\n";
    }
    
    return 0;
}
