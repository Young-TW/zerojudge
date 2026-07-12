#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    int case_num = 1;
    while (cin >> N && N >= 0) {
        int ans = 0;
        int cur = 1;
        while (cur < N) {
            cur <<= 1;
            ans++;
        }
        cout << "Case " << case_num << ": " << ans << "\n";
        case_num++;
    }
    
    return 0;
}
