#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using namespace std;

// 將座位表展平為字串以便於比較和存儲
string flatten(const vector<vector<int> >& grid) {
    string res = "";
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (j > 0) res += " ";
            res += to_string(grid[i][j]);
        }
        if (i < grid.size() - 1) res += "\n";
    }
    return res;
}

// 解析字串回座位表
vector<vector<int> > parse(const string& s, int R, int C) {
    vector<vector<int> > grid(R, vector<int>(C));
    int idx = 0;
    // 簡單解析：假設數字由空格或換行分隔
    // 由於我們 flatten 時用空格分隔同行，換行分隔不同行，這裡重新解析
    // 但為了 BFS 方便，我們其實只需要保持字串格式一致即可比較
    // 若要進行移動操作，還是需要二維結構
    // 這裡改用 token 分割
    vector<int> nums;
    string numStr = "";
    for (size_t i = 0; i <= s.length(); ++i) {
        if (i == s.length() || s[i] == ' ' || s[i] == '\n') {
            if (!numStr.empty()) {
                nums.push_back(stoi(numStr));
                numStr = "";
            }
        } else {
            numStr += s[i];
        }
    }
    
    int k = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (k < (int)nums.size())
                grid[i][j] = nums[k++];
        }
    }
    return grid;
}

// 移動操作
// 往上移動：第一列變最後一列，其他列上移
vector<vector<int> > moveUp(const vector<vector<int> >& grid) {
    if (grid.empty()) return grid;
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res = grid;
    for (int i = 0; i < R - 1; ++i) {
        res[i] = grid[i + 1];
    }
    res[R - 1] = grid[0];
    return res;
}

// 往下移動：最後一列變第一列，其他列下移
vector<vector<int> > moveDown(const vector<vector<int> >& grid) {
    if (grid.empty()) return grid;
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res = grid;
    for (int i = R - 1; i > 0; --i) {
        res[i] = grid[i - 1];
    }
    res[0] = grid[R - 1];
    return res;
}

// 往左移動：每列向左循環
vector<vector<int> > moveLeft(const vector<vector<int> >& grid) {
    if (grid.empty()) return grid;
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res = grid;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            res[i][j] = grid[i][(j + 1) % C];
        }
    }
    return res;
}

// 往右移動：每列向右循環
vector<vector<int> > moveRight(const vector<vector<int> >& grid) {
    if (grid.empty()) return grid;
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res = grid;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            res[i][j] = grid[i][(j - 1 + C) % C];
        }
    }
    return res;
}

// 往左旋轉：逆時針 90 度
// 原 (i, j) -> 新 (C-1-j, i) ? 
// 範例: 3x3
// 1 2 3      3 6 9
// 4 5 6  ->  2 5 8
// 7 8 9      1 4 7
// 原 (0,0)=1 -> 新 (2,0)=1? 不對，新 (2,0) 是 1. 
// 新座標 (r', c') 對應舊座標 (c', R-1-r')? 
// 讓我們直接建構：新矩陣大小 C x R
// new[c][R-1-i] = old[i][c] ? 
// 或者：new[j][R-1-i] = old[i][j]
// 驗證：old[0][0]=1 -> new[0][2]=1. 正確 (第三列第一行是 1)
// old[0][2]=3 -> new[2][2]=3. 正確 (第三列第三行是 3? 不對，範例第一列第三行是 9)
// 範例結果：
// 3 6 9
// 2 5 8
// 1 4 7
// 所以 new[0][0]=3, new[0][1]=6, new[0][2]=9
// old[0][2]=3 -> new[0][0]
// old[1][2]=6 -> new[0][1]
// old[2][2]=9 -> new[0][2]
// 規律：new[r][c] = old[c][C-1-r] ? 不對，維度變了
// 原 R x C -> 新 C x R
// new[r][c] = old[c][C-1-r] 這邏輯有點亂
// 標準逆時針旋轉公式：new[i][j] = old[j][C-1-i] 這是針對方陣？
// 對於 R x C 轉 C x R:
// new[i][j] = old[j][C-1-i] 這裡 i 範圍 0..C-1, j 範圍 0..R-1
// 檢查：new[0][0] = old[0][3-1-0] = old[0][2] = 3. 正確。
// new[0][1] = old[1][2] = 6. 正確。
// new[0][2] = old[2][2] = 9. 正確。
// new[1][0] = old[0][1] = 2. 正確。
// new[2][0] = old[0][0] = 1. 正確。
vector<vector<int> > rotateLeft(const vector<vector<int> >& grid) {
    if (grid.empty()) return grid;
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res(C, vector<int>(R));
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            res[i][j] = grid[j][C - 1 - i];
        }
    }
    return res;
}

// 往右旋轉：順時針 90 度
// 範例:
// 1 2 3      7 4 1
// 4 5 6  ->  8 5 2
// 7 8 9      9 6 3
// new[0][0]=7 = old[2][0]
// new[0][1]=4 = old[1][0]
// new[0][2]=1 = old[0][0]
// 規律：new[i][j] = old[R-1-j][i]
// i: 0..C-1, j: 0..R-1
// new[0][0] = old[3-1-0][0] = old[2][0] = 7. 正確。
// new[0][2] = old[3-1-2][0] = old[0][0] = 1. 正確。
// new[1][0] = old[2][1] = 8. 正確。
vector<vector<int> > rotateRight(const vector<vector<int> >& grid) {
    if (grid.empty()) return grid;
    int R = grid.size();
    int C = grid[0].size();
    vector<vector<int> > res(C, vector<int>(R));
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            res[i][j] = grid[R - 1 - j][i];
        }
    }
    return res;
}

string gridToString(const vector<vector<int> >& grid) {
    string s = "";
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (j > 0) s += " ";
            s += to_string(grid[i][j]);
        }
        if (i < grid.size() - 1) s += "\n";
    }
    return s;
}

int solve() {
    int M1, N1, M2, N2;
    if (!(cin >> M1 >> N1 >> M2 >> N2)) return 0;
    
    vector<vector<int> > startGrid(M1, vector<int>(N1));
    for (int i = 0; i < M1; ++i) {
        for (int j = 0; j < N1; ++j) {
            cin >> startGrid[i][j];
        }
    }
    
    vector<vector<int> > targetGrid(M2, vector<int>(N2));
    for (int i = 0; i < M2; ++i) {
        for (int j = 0; j < N2; ++j) {
            cin >> targetGrid[i][j];
        }
    }
    
    string targetStr = gridToString(targetGrid);
    
    // BFS 狀態：字串表示的座位表
    // 距離：步數
    map<string, int> dist;
    queue<vector<vector<int> > > q;
    
    string startStr = gridToString(startGrid);
    dist[startStr] = 0;
    q.push(startGrid);
    
    int minStepsWithSwap = -1;
    
    while (!q.empty()) {
        vector<vector<int> > cur = q.front();
        q.pop();
        
        string curStr = gridToString(cur);
        int d = dist[curStr];
        
        // 如果已經超過某個合理步數（例如 10），可以考慮剪枝？
        // 但題目沒給範圍，先不剪枝，看是否會 TLE/MLE
        // 實際上 6 種操作，群的大小有限，最多就是所有排列數，但這裡是循環移位和旋轉
        // 對於 3x3，操作群大小不會太大
        
        // 嘗試 6 種移動
        vector<vector<vector<int> > > nextGrids;
        nextGrids.push_back(moveUp(cur));
        nextGrids.push_back(moveDown(cur));
        nextGrids.push_back(moveLeft(cur));
        nextGrids.push_back(moveRight(cur));
        nextGrids.push_back(rotateLeft(cur));
        nextGrids.push_back(rotateRight(cur));
        
        for (int k = 0; k < 6; ++k) {
            vector<vector<int> >& nxt = nextGrids[k];
            string nxtStr = gridToString(nxt);
            
            if (dist.find(nxtStr) == dist.end()) {
                dist[nxtStr] = d + 1;
                q.push(nxt);
                
                if (nxtStr == targetStr) {
                    // 找到不加交換的解
                    cout << d + 1 << endl;
                    return 1;
                }
            }
        }
        
        // 嘗試使用一次交換權利
        // 只在第一次遇到該狀態時嘗試交換？或者每次？
        // 題目說每筆測資只可用一次，所以在 BFS 中，從任何狀態都可以選擇使用一次交換
        // 但為了避免重複計算，我們可以在生成鄰居時，如果還沒用過交換，就嘗試交換
        // 但我們的狀態沒有記錄是否用過交換。
        // 策略：在 BFS 過程中，對於每個狀態，嘗試所有可能的兩兩交換，然後檢查是否等於目標
        // 因為交換只能用一次，所以交換後的狀態如果等於目標，則答案為 d+1 (交換算一步)
        // 注意：交換後不再繼續 BFS，因為只能用一次。
        // 但如果交換後不等於目標，就不能再移動了（因為交換只能用一次，且用完後若還需移動則不符合"只用一次交換"的假設？）
        // 題目意涵：總步數 = 移動次數 + (是否使用交換 ? 1 : 0)
        // 所以我們要找的是：min( 移動次數 such that 移動後==目標 , 移動次數+1 such that 移動後交換一次==目標 )
        
        // 因此，我們在每個狀態檢查：如果當前狀態經過一次交換能變成目標，則更新答案
        if (minStepsWithSwap == -1 || d + 1 < minStepsWithSwap) {
            // 嘗試所有兩兩交換
            int R = cur.size();
            int C = cur[0].size();
            bool found = false;
            for (int i1 = 0; i1 < R && !found; ++i1) {
                for (int j1 = 0; j1 < C && !found; ++j1) {
                    for (int i2 = 0; i2 < R && !found; ++i2) {
                        for (int j2 = 0; j2 < C && !found; ++j2) {
                            if (i1 == i2 && j1 == j2) continue;
                            // 交換
                            vector<vector<int> > swapped = cur;
                            swap(swapped[i1][j1], swapped[i2][j2]);
                            if (gridToString(swapped) == targetStr) {
                                minStepsWithSwap = d + 1;
                                found = true;
                            }
                        }
                    }
                }
            }
        }
        
        // 如果已經找到不加交換的解，且當前深度已經大於等於該解，則可以停止？
        // 但我們可能先找到交換的解，後來找到不加交換的解更優
        // 所以不能輕易停止，除非我們確定 BFS 層級已經超過目前最佳解
    }
    
    if (minStepsWithSwap != -1) {
        cout << minStepsWithSwap << " DD thanks Honglin for his great kindness, DD will never forget it." << endl;
        return 1;
    }
    
    cout << "Uh-oh, DD can't sit with Badspeed." << endl;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int X;
    if (cin >> X) {
        while (X--) {
            solve();
        }
    }
    
    return 0;
}
