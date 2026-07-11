#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> instructions = {
        "SET C A",
        "LS B A",
        "LS C 1",
        "SET D 1",
        "XOR D C",
        "ANS D"
    };

    for (const string& inst : instructions) {
        cout << inst << '\n';
    }

    return 0;
}
