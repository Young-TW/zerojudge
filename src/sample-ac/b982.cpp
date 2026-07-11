#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        long long ans = 0;
        char last = s.back();
        
        if (last == 'm') {
            // xgym
            size_t pos_g = s.find('g');
            long long x = stoll(s.substr(0, pos_g));
            long long y = stoll(s.substr(pos_g + 1));
            ans = x * 8LL * 1000000000LL + y * 8LL * 1000000LL;
        } else if (last == 'k') {
            // xgymzk or ymzk
            size_t pos_g = s.find('g');
            size_t pos_m = s.find('m');
            if (pos_g != string::npos) {
                long long x = stoll(s.substr(0, pos_g));
                long long y = stoll(s.substr(pos_g + 1, pos_m - pos_g - 1));
                long long z = stoll(s.substr(pos_m + 1));
                ans = x * 8LL * 1000000000LL + y * 8LL * 1000000LL + z * 8LL * 1000LL;
            } else {
                long long y = stoll(s.substr(0, pos_m));
                long long z = stoll(s.substr(pos_m + 1));
                ans = y * 8LL * 1000000LL + z * 8LL * 1000LL;
            }
        } else if (last == 'b') {
            // gb, mb, kb, z.akb
            char second_last = s[s.length() - 2];
            if (second_last == 'g') {
                // xgb
                long long x = stoll(s);
                ans = x * 8LL * 1000000000LL;
            } else if (second_last == 'm') {
                // ymb
                long long y = stoll(s);
                ans = y * 8LL * 1000000LL;
            } else if (second_last == 'k') {
                // zkb or z.akb
                size_t pos_dot = s.find('.');
                if (pos_dot != string::npos) {
                    long long z = stoll(s.substr(0, pos_dot));
                    long long a = stoll(s.substr(pos_dot + 1));
                    ans = z * 8LL * 1000LL + a * 8LL * 100LL;
                } else {
                    long long z = stoll(s);
                    ans = z * 8LL * 1000LL;
                }
            }
        } else if (last == 'e') {
            // ubyte or u.vbyte
            size_t pos_dot = s.find('.');
            if (pos_dot != string::npos) {
                long long u = stoll(s.substr(0, pos_dot));
                long long v = stoll(s.substr(pos_dot + 1));
                ans = u * 8LL + v;
            } else {
                long long u = stoll(s);
                ans = u * 8LL;
            }
        } else if (last == 't') {
            // vbit
            long long v = stoll(s);
            ans = v;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
