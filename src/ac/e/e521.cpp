#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        while (n--) {
            int a, b, c;
            cin >> a >> b >> c;
            
            bool isTriangle = (a + b > c) && (a + c > b) && (b + c > a);
            
            if (!isTriangle) {
                cout << "0\n";
            } else {
                bool isIsosceles = (a == b) || (b == c) || (a == c);
                if (isIsosceles) {
                    cout << "1 1\n";
                } else {
                    cout << "1 0\n";
                }
            }
        }
    }
    
    return 0;
}
