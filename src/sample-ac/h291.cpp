#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<std::string> months = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    int n;
    while (std::cin >> n) {
        if (n >= 1 && n <= 12) {
            std::cout << months[n] << "\n";
        }
    }
    
    return 0;
}
