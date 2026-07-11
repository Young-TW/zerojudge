#include <iostream>

using namespace std;

int sum[1001];
int fact[3000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int len = 1;
    fact[0] = 1;
    sum[0] = 1;
    
    for (int i = 1; i <= 1000; ++i) {
        int carry = 0;
        for (int j = 0; j < len; ++j) {
            int temp = fact[j] * i + carry;
            fact[j] = temp % 10;
            carry = temp / 10;
        }
        while (carry > 0) {
            fact[len] = carry % 10;
            carry /= 10;
            len++;
        }
        
        int s = 0;
        for (int j = 0; j < len; ++j) {
            s += fact[j];
        }
        sum[i] = s;
    }
    
    int n;
    while (cin >> n) {
        cout << sum[n] << "\n";
    }
    
    return 0;
}
