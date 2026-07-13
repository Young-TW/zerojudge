#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        bool is_winning[26] = {false};
        for (int i = 0; i < N; ++i) {
            int num;
            cin >> num;
            is_winning[num] = true;
        }
        
        bool board[5][5];
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                int num;
                cin >> num;
                board[i][j] = is_winning[num];
            }
        }
        
        int success = 0;
        int almost = 0;
        
        // 檢查行
        for (int i = 0; i < 5; ++i) {
            int cnt = 0;
            for (int j = 0; j < 5; ++j) {
                if (board[i][j]) cnt++;
            }
            if (cnt == 5) success++;
            else if (cnt == 4) almost++;
        }
        
        // 檢查列
        for (int j = 0; j < 5; ++j) {
            int cnt = 0;
            for (int i = 0; i < 5; ++i) {
                if (board[i][j]) cnt++;
            }
            if (cnt == 5) success++;
            else if (cnt == 4) almost++;
        }
        
        // 檢查對角線
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < 5; ++i) {
            if (board[i][i]) cnt1++;
            if (board[i][4 - i]) cnt2++;
        }
        if (cnt1 == 5) success++;
        else if (cnt1 == 4) almost++;
        
        if (cnt2 == 5) success++;
        else if (cnt2 == 4) almost++;
        
        cout << success << " " << almost << "\n";
    }
    
    return 0;
}
