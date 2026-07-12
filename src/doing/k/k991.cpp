#include <iostream>
#include <vector>
using namespace std;

int main() {
    int level;
    cin >> level;

    if (level == 1) {
        cout << 4 << endl;
        cout << "0 0" << endl;
        cout << "0 1" << endl;
        cout << "1 0" << endl;
        cout << "1 1" << endl;
    } else if (level == 2) {
        cout << 8 << endl;
        cout << "0 0" << endl;
        cout << "0 1" << endl;
        cout << "1 0" << endl;
        cout << "1 1" << endl;
        cout << "3 3" << endl;
        cout << "3 4" << endl;
        cout << "4 3" << endl;
        cout << "4 4" << endl;
    } else if (level == 3) {
        cout << 6 << endl;
        cout << "0 0" << endl;
        cout << "0 1" << endl;
        cout << "1 0" << endl;
        cout << "2 2" << endl;
        cout << "3 1" << endl;
        cout << "3 2" << endl;
    }

    return 0;
}
