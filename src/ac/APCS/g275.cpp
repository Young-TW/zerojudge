#include <iostream>

int main(){
    int n;
    bool a, b, c;
    int d[14];
    std::cin >> n;
    for (int i=0; i<n; i++) {
        for (int j=0; j<14; j++) {
            std::cin >> d[j];
        }

        a = !(d[1] == d[5] && d[1] != d[3] && d[8] == d[12] && d[8] != d[10]);
        b = !(d[6] == 1 && d[13] == 0);
        c = !(d[1] != d[8] && d[5] != d[12] && d[3] != d[10]);
        if (a) std::cout << "A";
        if (b) std::cout << "B";
        if (c) std::cout << "C";
        if (a==0 && b==0 && c==0) std::cout << "None";
        std::cout << std::endl;
    }

    return 0;
}