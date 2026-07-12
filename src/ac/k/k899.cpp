#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        if (N <= 0) break;
        
        vector<string> L(N);
        for (int i = 0; i < N; i++) cin >> L[i];
        vector<int> T(N);
        for (int i = 0; i < N; i++) cin >> T[i];
        int M, K, S;
        cin >> M >> K >> S;
        
        vector<string> posName(N + 1);
        for (int i = 0; i < N; i++) {
            posName[T[i]] = L[i];
        }
        
        int gold = M, hp = K, pos = S;
        int initS = S;
        int maxGold = M, minGold = M;
        int maxHP = K, minHP = K;
        
        cout << "初始金幣值為" << M << "\n";
        cout << "初始血量值為" << K << "\n";
        cout << "初始位置為" << S << "\n";
        cout << "初始名稱位置為" << posName[S] << "\n";
        
        string cmd;
        while (cin >> cmd) {
            if (cmd == "0") {
                cin >> cmd;
                break;
            } else if (cmd == "left" || cmd == "right") {
                int x;
                cin >> x;
                int newPos;
                if (cmd == "left") newPos = pos - x;
                else newPos = pos + x;
                
                if (x > N || newPos < 1 || newPos > N) {
                    cout << -1 << "\n";
                } else {
                    pos = newPos;
                    cout << posName[pos] << "\n";
                }
            } else if (cmd == "get" || cmd == "lose") {
                int x;
                cin >> x;
                string type;
                cin >> type;
                if (type == "coins") {
                    if (cmd == "get") gold += x;
                    else gold -= x;
                    maxGold = max(maxGold, gold);
                    minGold = min(minGold, gold);
                    cout << gold << "\n";
                } else {
                    if (cmd == "get") hp += x;
                    else hp -= x;
                    if (hp <= 0) {
                        hp = 0;
                        minHP = min(minHP, hp);
                        break;
                    }
                    maxHP = max(maxHP, hp);
                    minHP = min(minHP, hp);
                    cout << hp << "\n";
                }
            } else if (cmd == "BOOM") {
                hp -= 150;
                pos = initS;
                if (hp <= 0) {
                    hp = 0;
                    minHP = min(minHP, hp);
                    break;
                }
                maxHP = max(maxHP, hp);
                minHP = min(minHP, hp);
                cout << hp << " " << pos << " " << posName[pos] << "\n";
            }
        }
        
        cout << "遊戲結束\n";
        cout << "金幣值為" << gold << "\n";
        cout << "金幣值最多時為" << maxGold << "\n";
        cout << "金幣值最少時為" << minGold << "\n";
        cout << "血量值為" << hp << "\n";
        cout << "血量值最多時為" << maxHP << "\n";
        cout << "血量值最少時為" << minHP << "\n";
        cout << "目前所在的格子編號為" << pos << "\n";
        cout << "目前所在的格子名稱為" << posName[pos] << "\n";
    }
    return 0;
}
