#include <iostream>
#include <string>

int main() {
    int data;
    std::cin >> data;
    std::string n;
    int output;
    for (int i=0; i<data; i++) {
        std::cin >> n;
        output = 1;
        for (int j=0; j<n.length(); j++) {
            output *= n[j]-48; //-48 is for char to int
        }

        std::cout << output << std::endl;
    }

    return 0;
}