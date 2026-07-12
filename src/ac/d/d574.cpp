#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    bool first_case = true;
    std::string s;

    while (std::cin >> n) {
        std::cin >> s;

        std::string compressed;
        compressed.reserve(static_cast<std::string::size_type>(n) * 2);

        int len = static_cast<int>(s.length());
        for (int i = 0; i < len; ) {
            char c = s[i];
            int j = i + 1;
            while (j < len && s[j] == c) {
                ++j;
            }
            int count = j - i;

            char num_buf[12];
            int num_len = 0;
            int x = count;
            do {
                num_buf[num_len++] = '0' + (x % 10);
                x /= 10;
            } while (x > 0);
            for (int k = num_len - 1; k >= 0; --k) {
                compressed.push_back(num_buf[k]);
            }
            compressed.push_back(c);

            i = j;
        }

        if (!first_case) {
            std::cout << '\n';
        }
        first_case = false;

        if (compressed.length() < s.length()) {
            std::cout << compressed << '\n';
        } else {
            std::cout << s << '\n';
        }
    }

    return 0;
}
