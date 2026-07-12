#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        double pi = acos(-1.0);
        double error = pi - n * sin(pi / n);
        printf("%.2e\n", error);
    }
    return 0;
}
