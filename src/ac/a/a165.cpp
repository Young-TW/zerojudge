#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    if (getline(cin, line)) {
        // 如果有讀到東西（包括空字串，如果輸入只有換行）
        cout << "我說了答案不就出來了 =   =" << endl;
    } else {
        // 如果讀到 EOF（完全沒有輸入）
        cout << 381654729 << endl;
    }
    return 0;
}
