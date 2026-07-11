#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cardA[5][5], cardB[5][5];
    int calls[25];

    while (cin >> cardA[0][0]) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i == 0 && j == 0) continue;
                cin >> cardA[i][j];
            }
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                cin >> cardB[i][j];
            }
        }
        for (int i = 0; i < 25; ++i) {
            cin >> calls[i];
        }

        bool markedA[5][5] = {false};
        bool markedB[5][5] = {false};
        bool lineA[12] = {false};
        bool lineB[12] = {false};
        int countA = 0, countB = 0;

        for (int k = 0; k < 25; ++k) {
            int num = calls[k];

            // 處理 A 卡
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (cardA[i][j] == num) {
                        markedA[i][j] = true;

                        // 檢查行 j
                        bool win = true;
                        for (int r = 0; r < 5; ++r) {
                            if (!markedA[r][j]) {
                                win = false;
                                break;
                            }
                        }
                        if (win && !lineA[j]) {
                            lineA[j] = true;
                            countA++;
                        }

                        // 檢查列 i
                        win = true;
                        for (int c = 0; c < 5; ++c) {
                            if (!markedA[i][c]) {
                                win = false;
                                break;
                            }
                        }
                        if (win && !lineA[5 + i]) {
                            lineA[5 + i] = true;
                            countA++;
                        }

                        // 檢查主對角線
                        if (i == j) {
                            win = true;
                            for (int d = 0; d < 5; ++d) {
                                if (!markedA[d][d]) {
                                    win = false;
                                    break;
                                }
                            }
                            if (win && !lineA[10]) {
                                lineA[10] = true;
                                countA++;
                            }
                        }

                        // 檢查副對角線
                        if (i + j == 4) {
                            win = true;
                            for (int d = 0; d < 5; ++d) {
                                if (!markedA[d][4 - d]) {
                                    win = false;
                                    break;
                                }
                            }
                            if (win && !lineA[11]) {
                                lineA[11] = true;
                                countA++;
                            }
                        }
                    }
                }
            }

            // 處理 B 卡
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (cardB[i][j] == num) {
                        markedB[i][j] = true;

                        // 檢查行 j
                        bool win = true;
                        for (int r = 0; r < 5; ++r) {
                            if (!markedB[r][j]) {
                                win = false;
                                break;
                            }
                        }
                        if (win && !lineB[j]) {
                            lineB[j] = true;
                            countB++;
                        }

                        // 檢查列 i
                        win = true;
                        for (int c = 0; c < 5; ++c) {
                            if (!markedB[i][c]) {
                                win = false;
                                break;
                            }
                        }
                        if (win && !lineB[5 + i]) {
                            lineB[5 + i] = true;
                            countB++;
                        }

                        // 檢查主對角線
                        if (i == j) {
                            win = true;
                            for (int d = 0; d < 5; ++d) {
                                if (!markedB[d][d]) {
                                    win = false;
                                    break;
                                }
                            }
                            if (win && !lineB[10]) {
                                lineB[10] = true;
                                countB++;
                            }
                        }

                        // 檢查副對角線
                        if (i + j == 4) {
                            win = true;
                            for (int d = 0; d < 5; ++d) {
                                if (!markedB[d][4 - d]) {
                                    win = false;
                                    break;
                                }
                            }
                            if (win && !lineB[11]) {
                                lineB[11] = true;
                                countB++;
                            }
                        }
                    }
                }
            }

            if (countA >= 5 && countB >= 5) {
                cout << "AB " << num << "\n";
                break;
            } else if (countA >= 5) {
                cout << "A " << num << "\n";
                break;
            } else if (countB >= 5) {
                cout << "B " << num << "\n";
                break;
            }
        }
    }

    return 0;
}
