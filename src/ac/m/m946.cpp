#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int case_num = 1;
    int N;
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            long long n;
            cin >> n;
            string res = "";
            if (n == 0) {
                res = "0";
            } else {
                while (n != 0) {
                    long long r = n % -2;
                    n /= -2;
                    if (r < 0) {
                        r += 2;
                        n += 1;
                    }
                    res += (char)('0' + r);
                }
                reverse(res.begin(), res.end());
            }
            cout << "Case #" << case_num << ": " << res << "\n";
            case_num++;
        }
    }
    return 0;
}
