#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    vector<int> memory(8, 0);
    vector<int> registers(4, 0);

    for (int i = 0; i < 8; ++i) {
        cin >> memory[i];
    }

    int N;
    cin >> N;
    cin.ignore();

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string op;
        iss >> op;

        if (op == "LOAD") {
            int rd, ms;
            iss >> rd >> ms;
            registers[rd] = memory[ms];
        } else if (op == "STORE") {
            int md, rs;
            iss >> md >> rs;
            memory[md] = registers[rs];
        } else if (op == "ADD") {
            int rd, rs1, rs2;
            iss >> rd >> rs1 >> rs2;
            registers[rd] = registers[rs1] + registers[rs2];
        } else if (op == "MOVE") {
            int rd, rs;
            iss >> rd >> rs;
            registers[rd] = registers[rs];
        }
    }

    cout << registers[0] << endl;
    cout << memory[0] << endl;

    return 0;
}
