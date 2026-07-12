#include <iostream>
#include <string>
using namespace std;

int main() {
    string id;
    while (cin >> id) {
        int count = 0;
        for (char c : id) {
            if (c == '8') {
                count++;
            }
        }
        int discount = 100 - count * 10;
        if (discount < 20) {
            discount = 20;
        }
        cout << id << " can get " << 100 - discount << "% off." << endl;
    }
    return 0;
}
