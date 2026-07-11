#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    const long long g = 34943;
    
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line == "#") {
            break;
        }
        
        long long val = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            val = (val * 256 + (unsigned char)line[i]) % g;
        }
        
        val = (val * 65536) % g;
        long long crc = (g - val) % g;
        
        printf("%02X %02X\n", crc / 256, crc % 256);
    }
    
    return 0;
}
