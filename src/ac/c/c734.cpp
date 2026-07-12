#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_digit(int j, long long pos_in_num) {
    int d = 0;
    int temp = j;
    while (temp > 0) {
        d++;
        temp /= 10;
    }
    int target_digit_from_right = d - pos_in_num + 1;
    for (int k = 1; k < target_digit_from_right; ++k) {
        j /= 10;
    }
    return j % 10;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<long long> prefix_len;
    vector<long long> len_s;
    prefix_len.push_back(0);
    len_s.push_back(0);
    long long current_len = 0;
    for (int i = 1; ; ++i) {
        int d = 0;
        int temp = i;
        while (temp > 0) {
            d++;
            temp /= 10;
        }
        current_len += d;
        len_s.push_back(current_len);
        prefix_len.push_back(prefix_len.back() + current_len);
        if (prefix_len.back() > 2147483647LL) {
            break;
        }
    }

    int T;
    if (cin >> T) {
        bool first = true;
        while (T--) {
            long long x;
            cin >> x;
            
            int i = lower_bound(prefix_len.begin(), prefix_len.end(), x) - prefix_len.begin();
            long long pos_in_s = x - prefix_len[i - 1];
            int j = lower_bound(len_s.begin(), len_s.begin() + i + 1, pos_in_s) - len_s.begin();
            long long pos_in_num = pos_in_s - len_s[j - 1];
            
            int ans = get_digit(j, pos_in_num);
            
            if (!first) cout << " ";
            cout << ans;
            first = false;
        }
        cout << "\n";
    }

    return 0;
}
