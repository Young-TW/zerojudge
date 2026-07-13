#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string add(const string& a, const string& b) {
    string res;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string div(const string& a, long long b) {
    string res;
    long long rem = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        rem = rem * 10 + (a[i] - '0');
        res.push_back((rem / b) + '0');
        rem %= b;
    }
    size_t pos = 0;
    while (pos < res.size() - 1 && res[pos] == '0') {
        pos++;
    }
    return res.substr(pos);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, F;
    int case_num = 1;
    while (cin >> N >> F) {
        if (N == 0 && F == 0) break;
        string sum = "0";
        for (int i = 0; i < N; ++i) {
            string v;
            cin >> v;
            sum = add(sum, v);
        }
        string pay = div(sum, F);
        cout << "Bill #" << case_num << " costs " << sum << ": each friend should pay " << pay << "\n\n";
        case_num++;
    }
    return 0;
}
