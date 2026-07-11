#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const char* zodiac[] = {"鼠", "牛", "虎", "兔", "龍", "蛇", "馬", "羊", "猴", "雞", "狗", "豬"};
    int y;
    while (cin >> y) {
        int idx = ((y - 1) % 12 + 12) % 12;
        cout << zodiac[idx] << "\n";
    }
    
    return 0;
}
