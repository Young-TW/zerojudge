#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n && n != 0) {
        cout << "Original number was " << n << "\n";
        set<long long> seen;
        seen.insert(n);
        long long curr = n;
        
        while (true) {
            string s = to_string(curr);
            sort(s.begin(), s.end());
            long long a = stoll(s);
            sort(s.rbegin(), s.rend());
            long long b = stoll(s);
            long long next = b - a;
            
            cout << b << " - " << a << " = " << next << "\n";
            
            if (seen.count(next)) {
                break;
            }
            
            seen.insert(next);
            curr = next;
        }
        
        cout << "Chain length " << seen.size() << "\n\n";
    }
    
    return 0;
}
