#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string a, b;
    int yukari_wins = 0, reimu_wins = 0;
    
    auto get_val = [](const string& s) -> int {
        if (s == "Scissors") return 0;
        if (s == "Stone") return 1;
        return 2; // Paper
    };
    
    while (cin >> a >> b) {
        if (a == "Game") {
            break;
        }
        int va = get_val(a);
        int vb = get_val(b);
        if ((va + 1) % 3 == vb) {
            cout << "靈夢獲勝\n";
            reimu_wins++;
        } else {
            cout << "紫獲勝\n";
            yukari_wins++;
        }
    }
    
    if (reimu_wins > yukari_wins) {
        cout << "悲慘的籌措起香油錢\n";
    } else {
        cout << "螢火的蹤跡\n";
    }
    
    return 0;
}
