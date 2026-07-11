#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    const double PI = std::acos(-1.0);
    
    int N;
    while (std::cin >> N) {
        std::cin.ignore();
        for (int i = 0; i < N; i++) {
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            int a = 0, b = 0;
            if (iss >> a >> b) {
                // r1 = a, r2 = b
                // Big circle radius R = r1 + r2
                // Gray area = pi*R^2 - pi*r1^2 - pi*r2^2 = 2*pi*r1*r2
                double area = 2.0 * PI * a * b;
                std::cout << std::fixed << std::setprecision(4) << area << "\n";
            } else {
                // t = a
                // t = 2*sqrt(r1*r2) => r1*r2 = t^2/4
                // Gray area = 2*pi*r1*r2 = 2*pi*(t^2/4) = pi*t^2/2
                double t = a;
                double area = PI * t * t / 2.0;
                std::cout << std::fixed << std::setprecision(4) << area << "\n";
            }
        }
    }
    
    return 0;
}
