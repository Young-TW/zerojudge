#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string keyboard = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";
    char mapping[256];
    for (int i = 0; i < 256; ++i) {
        mapping[i] = (char)i;
    }
    for (size_t i = 2; i < keyboard.size(); ++i) {
        mapping[(unsigned char)keyboard[i]] = keyboard[i - 2];
    }
    
    char c;
    while (cin.get(c)) {
        cout.put(mapping[(unsigned char)c]);
    }
    
    return 0;
}
