#include <iostream>
#include <string>
using namespace std;

int main() {
    string num, temp;
    int n, a, b;
    cin >> num >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        a = 0;
        b = 0;
        for (int j = 0; j < 4; j++) {
            if (num.at(j) == temp.at(j)) {
                a++;
            } else {
                for (int k = 0; k < 4; k++) {
                    if (num.at(j) == temp.at(k) && j != k) {
                        b++;
                    }
                }
            }
        }
        cout << a << "A" << b << "B" << endl;
    }
    return 0;
}