#include <iostream>
#include <string>

using namespace std;

int get_len(int n) {
    if (n == 0) return 1;
    int len = 0;
    while (n > 0) {
        len++;
        n /= 10;
    }
    return len;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b;
    while (cin >> a >> b) {
        int ans = a * b;
        int len_ans = get_len(ans);
        
        cout << string(len_ans - get_len(a), ' ') << a << "\n";
        cout << string(len_ans - get_len(b), ' ') << b << "\n";
        cout << string(len_ans, '-') << "\n";
        
        int temp_b = b;
        int i = 0;
        while (temp_b > 0) {
            int digit = temp_b % 10;
            int prod = a * digit;
            int len_prod = get_len(prod);
            int width = len_ans - i;
            cout << string(width - len_prod, ' ') << prod << "\n";
            temp_b /= 10;
            i++;
        }
        
        cout << string(len_ans, '-') << "\n";
        cout << ans << "\n";
    }
    return 0;
}
