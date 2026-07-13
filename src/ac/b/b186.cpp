#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int cookie, chocolate, cake;
    while (cin >> cookie >> chocolate >> cake) {
        int bonus = min(cookie / 10, cake / 2);
        chocolate += bonus;
        cout << cookie << " 個餅乾，" << chocolate << " 盒巧克力，" << cake << " 個蛋糕。\n";
    }
    
    return 0;
}
