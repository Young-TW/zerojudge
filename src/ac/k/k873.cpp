#include <iostream>

using namespace std;

int main() {
    // 駭客題:Alice 正確(空列表回傳 bool False);Bob 的 `n and all(...)`
    // 對空列表回傳 [] 而非 False,故唯一能使兩者回傳值不同的輸入是空列表。
    cout << "Alice\n";  // 第一行:正確的函數
    cout << "\n";        // 第二行:空列表
    return 0;
}
