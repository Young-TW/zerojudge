#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a0;
    while (cin >> a0 && a0 != 0) {
        bool seen[10000];
        memset(seen, false, sizeof(seen));
        
        int curr = a0;
        int count = 0;
        
        while (!seen[curr]) {
            seen[curr] = true;
            count++;
            curr = (curr * curr / 100) % 10000;
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
