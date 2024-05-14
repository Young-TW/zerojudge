#include <iostream>
#include <string>

int k = 0, d = 0, a = 0;

void die(int combo) {
    d++;
    if (combo <= 2) {
        std::cout << "You have been slained." << std::endl;
        return;
    }
    std::cout << "SHUTDOWN." << std::endl;
    return;
}

void kill(int combo) {
    k++;
    combo++;
    if (combo <= 2) {
        std::cout << "You have slain an enemie." << std::endl;
        return;
    }
    if (combo == 3) {
        std::cout << "KILLING SPREE!" << std::endl;
        return;
    }
    if (combo == 4) {
        std::cout << "RAMPAGE~" << std::endl;
        return;
    }
    if (combo == 5) {
        std::cout << "UNSTOPPABLE!" << std::endl;
        return;
    }
    if (combo == 6) {
        std::cout << "DOMINATING!" << std::endl;
        return;
    }
    if (combo == 7) {
        std::cout << "GUALIKE!" << std::endl;
        return;
    }
    if (combo >= 8) {
        std::cout << "LEGENDARY!" << std::endl;
        return;
    }
    return;
}

int main() {
    int n, combo = 0;
    std::string status;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> status;
        if (status == "Get_Kill") {
            kill(combo);
            combo++;
        }
        if (status == "Get_Assist") a++;
        if (status == "Die") {
            die(combo);
            combo = 0;
        }
    }
    std::cout << k << "/" << d << "/" << a;
    return 0;
}