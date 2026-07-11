#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    string a, b;
    
    while (cin >> n >> a >> b) {
        int len_a = a.length();
        int len_b = b.length();
        
        if (n > len_b) {
            cout << "NO\n";
            continue;
        }
        
        vector<int> pi(len_a, 0);
        for (int i = 1; i < len_a; i++) {
            int j = pi[i - 1];
            while (j > 0 && a[i] != a[j]) {
                j = pi[j - 1];
            }
            if (a[i] == a[j]) {
                j++;
            }
            pi[i] = j;
        }
        
        long long count = 0;
        int j = 0;
        for (int i = 0; i < len_b; i++) {
            while (j > 0 && b[i] != a[j]) {
                j = pi[j - 1];
            }
            if (b[i] == a[j]) {
                j++;
            }
            if (j == len_a) {
                count++;
                j = pi[j - 1];
            }
        }
        
        if (count == n) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
