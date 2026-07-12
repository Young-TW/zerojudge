#include <iostream>
#include <string>

using namespace std;

string s;
int idx;

long long solve(long long area) {
    char c = s[idx++];
    if (c == '0') {
        return 0;
    } else if (c == '1') {
        return area;
    } else { // c == '2'
        long long sub_area = area / 4;
        return solve(sub_area) + solve(sub_area) + solve(sub_area) + solve(sub_area);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> s) {
        long long n;
        if (!(cin >> n)) break;
        idx = 0;
        cout << solve(n * n) << "\n";
    }
    
    return 0;
}
