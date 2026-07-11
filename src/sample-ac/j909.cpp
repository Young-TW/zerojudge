#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string firstName, lastName;
    while (cin >> firstName >> lastName) {
        cout << lastName << ", " << firstName << "\n";
    }
    
    return 0;
}
