#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    while (std::cin >> s) {
        int count[26] = {0};
        for (size_t i = 0; i < s.length(); ++i) {
            count[s[i] - 'A']++;
        }
        
        std::string ans;
        ans.reserve(s.length());
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                ans.append(count[i], static_cast<char>('A' + i));
            }
        }
        std::cout << ans << '\n';
    }
    
    return 0;
}
