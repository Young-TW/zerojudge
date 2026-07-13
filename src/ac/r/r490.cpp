#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        map<string, int> count;
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            int s_odd = 0;
            int s_even = 0;
            for (int j = 0; j < 12; ++j) {
                int digit = s[j] - '0';
                if (j % 2 == 0) {
                    s_odd += digit;
                } else {
                    s_even += digit;
                }
            }
            int C = s[12] - '0';
            int sum = (s_odd + 3 * s_even) % 10;
            if ((sum + C) % 10 == 0) {
                string origin = s.substr(0, 3);
                count[origin]++;
            }
        }
        
        string best_origin = "";
        int max_count = -1;
        for (map<string, int>::iterator it = count.begin(); it != count.end(); ++it) {
            if (it->second > max_count) {
                max_count = it->second;
                best_origin = it->first;
            }
        }
        cout << best_origin << " " << max_count << "\n";
    }
    return 0;
}
