#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    
    while (cin >> n && n != 0) {
        cout << "Case " << case_num << ": " << n / 2 << "\n";
        case_num++;
    }
    
    return 0;
}
