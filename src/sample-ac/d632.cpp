#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string A, B;
    while (cin >> A >> B) {
        string S(32, '0');
        int c = 0;
        for (int i = 31; i >= 0; --i) {
            int a = A[i] - '0';
            int b = B[i] - '0';
            int s = a ^ b ^ c;
            c = (a & b) | (b & c) | (c & a);
            S[i] = s + '0';
        }
        cout << A << "\n";
        cout << B << "\n";
        cout << "---------------------------------\n";
        cout << S << "\n";
        cout << "****End of Data******************\n";
    }
    return 0;
}
