#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

// 點數映射：2=15, A=14, K=13, Q=12, J=11, 10=10, ..., 3=3
int getRankValue(const string& r) {
    if (r == "2") return 15;
    if (r == "A") return 14;
    if (r == "K") return 13;
    if (r == "Q") return 12;
    if (r == "J") return 11;
    return stoi(r);
}

// 花色映射：+=3(S), -=2(H), *=1(D), /=0(C)
int getSuitValue(char s) {
    if (s == '+') return 3;
    if (s == '-') return 2;
    if (s == '*') return 1;
    return 0;
}

struct Card {
    int rank; // 3-15
    int suit; // 0-3
    string original;

    bool operator<(const Card& other) const {
        if (rank != other.rank) return rank < other.rank;
        return suit < other.suit;
    }
    
    bool operator==(const Card& other) const {
        return rank == other.rank && suit == other.suit;
    }
};

struct Hand {
    vector<Card> cards;
    int id; // 1-4

    void sortCards() {
        sort(cards.begin(), cards.end());
    }

    bool isEmpty() const {
        return cards.empty();
    }

    // 檢查是否為同花一條龍 (3~2 同花色)
    bool isDragon() const {
        if (cards.size() != 13) return false;
        int s = cards[0].suit;
        for (int i = 0; i < 13; ++i) {
            if (cards[i].suit != s) return false;
            if (cards[i].rank != i + 3) return false; // 3,4,5...15(2)
        }
        return true;
    }

    // 解析牌型並返回類型與比較值
    // 返回: {type, mainVal, subVal (如果需要)}
    // Type: 0=None, 1=Single, 2=Pair, 3=Straight, 4=FullHouse, 5=FourOfAKind, 6=StraightFlush, 7=Dragon
    vector<int> analyze() const {
        int n = cards.size();
        if (n == 0) return {0, 0, 0};
        if (isDragon()) return {7, 0, 0};

        if (n == 1) {
            return {1, cards[0].rank, cards[0].suit};
        }

        if (n == 2) {
            if (cards[0].rank == cards[1].rank) {
                return {2, cards[0].rank, max(cards[0].suit, cards[1].suit)};
            }
            return {0, 0, 0};
        }

        if (n == 5) {
            // 統計點數出現次數
            map<int, int> countMap;
            for (const auto& c : cards) countMap[c.rank]++;
            
            bool isSameSuit = true;
            for (size_t i = 1; i < cards.size(); ++i) {
                if (cards[i].suit != cards[0].suit) {
                    isSameSuit = false;
                    break;
                }
            }

            // 檢查順子
            bool isStraight = true;
            // 特殊順子 A2345 -> ranks: 3,4,5,6,14
            // 一般順子 x, x+1, x+2, x+3, x+4
            if (countMap.size() == 5) {
                int minR = cards[0].rank;
                int maxR = cards[4].rank;
                
                // 一般情況
                if (maxR - minR == 4) {
                    // OK
                } else if (minR == 3 && maxR == 14) {
                    // A2345 case: 3,4,5,6,14. 
                    // 需要確認中間是 4,5,6
                    if (!countMap.count(4) || !countMap.count(5) || !countMap.count(6)) {
                        isStraight = false;
                    }
                } else {
                    isStraight = false;
                }
            } else {
                isStraight = false;
            }

            // 大老二順子規則：23456 > 10JQKA > ... > A2345
            // 我們需要一個標準化的比較值
            int straightVal = -1;
            if (isStraight) {
                if (cards[4].rank == 6 && cards[0].rank == 2) { 
                    // 這裡邏輯有點問題，因為排序後 A2345 會是 3,4,5,6,14
                    // 23456 會是 2,3,4,5,6 -> rank 2 不存在，最小是 3
                    // 23456: 3,4,5,6,7? 不對，題目說 2>A>...>3
                    // 點數對應：2=15, A=14, K=13, Q=12, J=11, 10=10, 9=9, 8=8, 7=7, 6=6, 5=5, 4=4, 3=3
                    // 順子 23456: 點數為 6,7,8,9,10? 不對。
                    // 題目順序：2 > A > K ... > 3
                    // 順子 23456 指的是點數 2,3,4,5,6 嗎？
                    // 題目範例：23456 > 10JQKA
                    // 在大老二中，2 最大。所以 23456 是最大的順子。
                    // 對應的 rank 值：2(15), 3(3), 4(4), 5(5), 6(6)。這不連續。
                    // 啊，順子的定義是「順連」，但在大老二裡，2 可以接在 A 後面嗎？
                    // 題目說：23456 > 10JQKA > ... > A2345
                    // 且沒有 JQKA2, QKA23, KA234。
                    // 這表示順子的順序是循環的嗎？不，通常大老二順子是：
                    // 3-4-5-6-7, ..., 10-J-Q-K-A, A-2-3-4-5 (最小), 2-3-4-5-6 (最大)?
                    // 讓我們重新看題目：23456 > 10JQKA
                    // 如果 2 是 15, 3 是 3... 那 2,3,4,5,6 的 rank 是 15,3,4,5,6。這怎麼順？
                    // 原來大老二的順子規則特殊：
                    // 一般：3-4-5-6-7 ... 10-J-Q-K-A
                    // 特殊：A-2-3-4-5 (最小), 2-3-4-5-6 (最大) ?
                    // 題目明確列出：23456 > 10JQKA > 910JQK > ... > 34567 > A2345
                    // 所以最大的順子是 2-3-4-5-6。
                    // 第二大的順子是 10-J-Q-K-A。
                    // 最小的是 A-2-3-4-5。
                    // 我們的 rank 定義：2=15, A=14, K=13, ..., 3=3。
                    // 對於 10-J-Q-K-A: 10,11,12,13,14 -> 連續，max=14。
                    // 對於 3-4-5-6-7: 3,4,5,6,7 -> 連續，max=7。
                    // 對於 A-2-3-4-5: 3,4,5,6,14 (排序後)。這不是連續的。
                    // 對於 2-3-4-5-6: 3,4,5,6,15 (排序後)。這也不是連續的。
                    
                    // 我們需要特殊處理這兩種情況。
                    // 檢測 A2345: 包含 3,4,5,6,14 (A=14, 2=15? 不，2 是 15, A 是 14)
                    // A(14), 2(15), 3(3), 4(4), 5(5). 
                    // 排序後：3,4,5,14,15? 不對，2 是 15。
                    // 讓我們重新確認 rank 映射是否符合順子判斷。
                    // 如果 2=15, A=14, 3=3...
                    // A2345: A(14), 2(15), 3(3), 4(4), 5(5). 
                    // 排序後：3, 4, 5, 14, 15. 
                    // 23456: 2(15), 3(3), 4(4), 5(5), 6(6).
                    // 排序後：3, 4, 5, 6, 15.
                    
                    // 題目說的順子大小：
                    // 23456 (Max)
                    // 10JQKA
                    // ...
                    // 34567
                    // A2345 (Min)
                    
                    // 策略：計算一個「順子強度值」
                    // 如果是 3,4,5,6,15 (23456) -> Strength = 100 + 6 (以 6 為基準? 不，以 2 為基準最大)
                    // 讓我們用最大的牌來代表順子大小，但要特殊處理。
                    // 正常順子 (x, x+1, x+2, x+3, x+4): 強度 = x+4 (即最大牌的 rank)
                    // 例外 1: A2345 (3,4,5,6,14). 強度 = 0 (最小)
                    // 例外 2: 23456 (3,4,5,6,15). 強度 = 100 (最大)
                    // 等等，10JQKA 的 max 是 14 (A)。34567 的 max 是 7。
                    // 如果 23456 是最大的，它的強度必須大於 14。
                    // 如果 A2345 是最小的，它的強度必須小於 7 (最小的正常順子是 34567, max=7)。
                    
                    // 修正邏輯：
                    // 1. 檢查是否為 A2345: ranks 包含 {3,4,5,6,14} (注意 2 是 15, A 是 14, 這裡沒有 2)
                    //    題目寫 A2345，也就是 A, 2, 3, 4, 5。
                    //    Ranks: 14, 15, 3, 4, 5. 
                    //    排序後：3, 4, 5, 14, 15.
                    //    這有 5 張牌嗎？是的。
                    //    但是題目說 A2345 是順子。
                    //    我的 rank 映射：2=15, A=14.
                    //    所以 A2345 的 ranks 是 14, 15, 3, 4, 5.
                    //    排序後：3, 4, 5, 14, 15.
                    //    這不是 3,4,5,6,14。我之前的推導有误。
                    //    讓我們重新看：A, 2, 3, 4, 5.
                    //    Rank: 14, 15, 3, 4, 5.
                    //    這怎麼組成順子？在大老二規則裡，A2345 是特殊的順子。
                    //    它被視為 A-2-3-4-5。
                    //    在比較時，它是最小的。
                    
                    // 2. 檢查是否為 23456: 2, 3, 4, 5, 6.
                    //    Ranks: 15, 3, 4, 5, 6.
                    //    排序後：3, 4, 5, 6, 15.
                    //    這是最大的順子。
                    
                    // 3. 其他順子必須是連續的 rank。
                    //    例如 3,4,5,6,7 (max=7).
                    //    10,11,12,13,14 (max=14).
                    
                    // 算法：
                    // 收集所有 rank 到 vector v, sort.
                    // if v == {3,4,5,6,14} (A2345? 不，A=14, 2=15. A2345 應該是 14,15,3,4,5 -> 3,4,5,14,15)
                    // 讓我再確認一次題目：A2345.
                    // 點數：A, 2, 3, 4, 5.
                    // 映射：14, 15, 3, 4, 5.
                    // 排序：3, 4, 5, 14, 15.
                    // 這是 A2345 嗎？是的。
                    
                    // 23456: 2, 3, 4, 5, 6 -> 15, 3, 4, 5, 6 -> 3, 4, 5, 6, 15.
                    
                    // 所以：
                    // if v == {3, 4, 5, 14, 15} -> Type A2345 (Min)
                    // if v == {3, 4, 5, 6, 15} -> Type 23456 (Max)
                    // else if v[4] - v[0] == 4 && unique size == 5 -> Normal Straight. Value = v[4].
                    
                    // 比較值設計：
                    // Normal: value = v[4] (範圍 7~14).
                    // 23456: value = 20 (大於 14).
                    // A2345: value = 0 (小於 7).
                    
                    vector<int> v;
                    for(auto c : cards) v.push_back(c.rank);
                    sort(v.begin(), v.end());
                    
                    if (v == vector<int>{3, 4, 5, 14, 15}) {
                        straightVal = 0; // A2345
                    } else if (v == vector<int>{3, 4, 5, 6, 15}) {
                        straightVal = 20; // 23456
                    } else if (v.size() == 5 && v[4] - v[0] == 4) {
                        // 檢查是否真的連續 (防止 3,4,5,6,8 這種)
                        bool ok = true;
                        for(int i=1; i<5; ++i) if(v[i] != v[i-1]+1) ok=false;
                        if(ok) straightVal = v[4];
                        else isStraight = false;
                    } else {
                        isStraight = false;
                    }
                } else {
                     // 上面的 if (cards[4].rank == 6 ...) 是舊邏輯，已廢棄，改用 vector 比對
                     // 重新執行一次 vector 比對邏輯，因為上面那個 if 區塊只是示範思考
                     vector<int> v;
                     for(auto c : cards) v.push_back(c.rank);
                     sort(v.begin(), v.end());
                     
                     if (v == vector<int>{3, 4, 5, 14, 15}) {
                         straightVal = 0; 
                     } else if (v == vector<int>{3, 4, 5, 6, 15}) {
                         straightVal = 20; 
                     } else if (v.size() == 5 && v[4] - v[0] == 4) {
                         bool ok = true;
                         for(int i=1; i<5; ++i) if(v[i] != v[i-1]+1) ok=false;
                         if(ok) straightVal = v[4];
                         else isStraight = false;
                     } else {
                         isStraight = false;
                     }
                }
            }

            if (isStraight && isSameSuit) {
                return {6, straightVal, 0}; // Straight Flush
            }
            
            if (isStraight) {
                return {3, straightVal, 0}; // Straight
            }

            // Four of a kind
            if (countMap.size() == 2) {
                // 可能是 4+1 或 3+2
                for (auto const& [r, cnt] : countMap) {
                    if (cnt == 4) {
                        int single = (r == countMap.begin()->first) ? countMap.rbegin()->first : countMap.begin()->first;
                        return {5, r, single};
                    }
                }
            }

            // Full House
            if (countMap.size() == 2) {
                for (auto const& [r, cnt] : countMap) {
                    if (cnt == 3) {
                        int pairR = (r == countMap.begin()->first) ? countMap.rbegin()->first : countMap.begin()->first;
                        // 驗證另一個是不是 2
                        if (countMap[pairR] == 2) {
                            return {4, r, pairR};
                        }
                    }
                }
            }
            
            return {0, 0, 0};
        }

        return {0, 0, 0};
    }
    
    // 尋找能打過 currentPlay 的最小牌組
    // currentPlay: {type, val1, val2}
    // 回傳打出的牌組索引 (在 cards 中的索引)，若無則回傳 -1
    // 由於要輸出剩餘順序，我們需要模擬出牌並從 hand 中移除
    // 但這裡我們只返回「要打哪些牌」，由呼叫者處理移除
    vector<Card> findBestMove(const vector<int>& currentPlay) {
        int pType = currentPlay[0];
        int pVal1 = currentPlay[1];
        int pVal2 = currentPlay[2];
        
        int n = cards.size();
        vector<Card> bestHand;
        int bestScore = -1; // 用來比較哪組牌「最小」但又能贏
        
        // 如果可以出更高級別的牌型？
        // 規則：上家出同花，下家可以出比它高級的同花，或比同花等級高的牌型。
        // 等級：同花順 > 四條 > 葫蘆 > 順子。
        // 單張只能跟单張，一對只能跟一對。
        // 五張可以跟五張（同類型比大小）或 更高級類型的五張。
        
        // 枚舉所有可能的組合
        // 由於 N 很小 (最多 13)，可以用遞迴或 bitmask，但 13C5 很小，直接暴力枚舉
        // 實際上只需要枚舉 1, 2, 5 張的情況
        
        auto updateBest = [&](const vector<Card>& candidate, int cType, int cVal1, int cVal2) {
            if (cType == 0) return;
            
            bool canBeat = false;
            
            if (pType == 1) { // Single
                if (cType == 1) {
                    if (cVal1 > pVal1) canBeat = true;
                    else if (cVal1 == pVal1 && cVal2 > pVal2) canBeat = true;
                }
            } else if (pType == 2) { // Pair
                if (cType == 2) {
                    if (cVal1 > pVal1) canBeat = true;
                    else if (cVal1 == pVal1 && cVal2 > pVal2) canBeat = true;
                }
            } else if (pType >= 3 && pType <= 6) { // 5-card hands
                if (cType >= 3 && cType <= 6) {
                    if (cType > pType) canBeat = true;
                    else if (cType == pType) {
                        if (cVal1 > pVal1) canBeat = true;
                        else if (cVal1 == pVal1 && cVal2 > pVal2) canBeat = true;
                    }
                }
            } else if (pType == 7) { // Dragon, cannot beat
                canBeat = false;
            }
            
            if (canBeat) {
                // 我們要找「最小」的能贏的牌，以保留大牌
                // 定義牌的強度：總和？或者簡單地比較每張牌
                // 這裡簡化：優先選張數少的（不可能，因為類型固定），然後選單張點數和最小的
                int score = 0;
                for (const auto& c : candidate) score += c.rank * 10 + c.suit;
                
                if (bestHand.empty() || score < bestScore) {
                    bestHand = candidate;
                    bestScore = score;
                }
            }
        };

        if (pType == 1 || pType == 0) { // Can play Single
            for (int i = 0; i < n; ++i) {
                vector<Card> cand = {cards[i]};
                auto res = analyzeSubset(cand);
                updateBest(cand, res[0], res[1], res[2]);
            }
        }
        
        if (pType == 2 || pType == 0) { // Can play Pair
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    vector<Card> cand = {cards[i], cards[j]};
                    auto res = analyzeSubset(cand);
                    updateBest(cand, res[0], res[1], res[2]);
                }
            }
        }
        
        if ((pType >= 3 && pType <= 6) || pType == 0) { // Can play 5-card
            if (n >= 5) {
                vector<int> idx(n);
                for(int i=0; i<n; ++i) idx[i] = i;
                // C(n, 5)
                for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k)
                for (int l = k + 1; l < n; ++l)
                for (int m = l + 1; m < n; ++m) {
                    vector<Card> cand = {cards[i], cards[j], cards[k], cards[l], cards[m]};
                    auto res = analyzeSubset(cand);
                    updateBest(cand, res[0], res[1], res[2]);
                }
            }
        }
        
        // 特殊：如果自己有龍，直接出龍贏 (題目說若手牌為同花一條龍則直接勝出)
        // 但這是在開局還是任何時候？題目說 "若手牌為同花一條龍則直接勝出"
        // 通常是指開局檢查，或者輪到自己時如果湊成龍？
        // 題目輸入說明沒特別說開局檢查，但玩法裡提到。
        // 考慮到這題是模擬，如果輪到我，我手上有 13 張且是龍，我直接出完獲勝。
        // 但題目輸入已經是分好的手牌，遊戲進行中。
        // 如果某人手上剩 13 張且是龍，他還沒出過牌？
        // 題目說 "若手牌為同花一條龍則直接勝出"，這通常指開局發完牌就檢查。
        // 但在模擬過程中，如果某人手上剛好湊成龍（不可能，因為牌只會減少），除非他一開始就是龍。
        // 我們在主循環開始前檢查一次即可。
        // 在這裡 findBestMove 不需要處理龍，因為龍是瞬間勝利，不會作為普通牌型打出。
        // 除非... 對方出了什麼，我要壓龍？不可能，龍最大。
        
        return bestHand;
    }
    
    // 分析子集牌型
    vector<int> analyzeSubset(const vector<Card>& subset) const {
        Hand h;
        h.cards = subset;
        sort(h.cards.begin(), h.cards.end());
        return h.analyze();
    }
    
    // 移除特定牌
    void removeCards(const vector<Card>& toRemove) {
        for (const auto& rem : toRemove) {
            for (auto it = cards.begin(); it != cards.end(); ++it) {
                if (*it == rem) {
                    cards.erase(it);
                    break;
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    while (N--) {
        int x1, x2, x3, x4, G;
        cin >> x1 >> x2 >> x3 >> x4 >> G;
        vector<int> counts = {x1, x2, x3, x4};
        
        vector<Hand> players(4);
        bool dragonWin = false;
        int dragonWinner = -1;

        for (int i = 0; i < 4; ++i) {
            players[i].id = i + 1;
            for (int j = 0; j < counts[i]; ++j) {
                string s;
                cin >> s;
                char suitChar = s.back();
                string rankStr = s.substr(0, s.size() - 1);
                Card c;
                c.rank = getRankValue(rankStr);
                c.suit = getSuitValue(suitChar);
                c.original = s;
                players[i].cards.push_back(c);
            }
            players[i].sortCards();
            
            // 檢查龍
            if (players[i].isDragon()) {
                dragonWin = true;
                dragonWinner = players[i].id;
            }
        }

        if (dragonWin) {
            cout << dragonWinner;
            for (int i = 1; i <= 4; ++i) {
                if (i != dragonWinner) cout << " " << i;
            }
            cout << "\n";
            continue;
        }

        vector<int> resultOrder;
        vector<bool> finished(4, false);
        int finishedCount = 0;
        
        int currentPlayer = G - 1; // 0-based
        vector<int> lastPlay = {0, 0, 0}; // type, v1, v2. Type 0 means new round (free to play anything)
        int passCount = 0;

        // 遊戲開始第一輪誰出牌？
        // 題目說 "G代表從哪個玩家開始"
        // 並且 "開局出牌的順序為：五隻>一對>單張"
        // 這意味著第一個出牌的人可以自由選擇出 5 張、2 張或 1 張？
        // 不，通常大老二是拿到梅花 3 的先出，或者指定人先出。
        // 這裡 G 指定了起始玩家。
        // 起始玩家可以出任何合法的牌型嗎？
        // 題目說 "開局出牌的順序為：五隻>一對>單張" 這句話有點模糊。
        // 可能是指：如果起始玩家想主動出牌，他必須按照這個優先級？
        // 或者是指：遊戲開始時，大家輪流出牌，直到有人出不出來？
        // 解讀：通常第一個出牌的人可以自由出任何牌型（單、對、五）。
        // 但題目那句 "開局出牌的順序為：五隻>一對>單張" 可能是在暗示 AI 的策略？
        // 或者是限制起始玩家只能出五隻？如果不能出五隻才出對？
        // 讓我們看範例。
        // 範例輸入：G=3 (玩家 3 開始)
        // 玩家 3 手牌：5- 6- 8- 9- 10+ 10* 10/ 10- (8 張)
        // 玩家 3 有四個 10 (四條)。
        // 如果限制起始只能出五隻，玩家 3 可以出 10,10,10,10,X (四條帶一)。
        // 如果沒有限制，他可以出單張或對子。
        // 題目文字："開局出牌的順序為：五隻>一對>單張"
        // 這很可能是指「起始玩家」的出牌策略限制：優先出五張，若無則對，若無則單。
        // 或者是整個遊戲的出牌權轉移邏輯？不，後面有說 PASS 機制。
        // 假設這是對「起始玩家第一手牌」的限制。
        // 策略：起始玩家嘗試出五張，若不行則嘗試出對，若不行則出單。
        // 而其他時候，如果是新回合（所有人都 Pass），當前玩家可以自由出嗎？
        // 通常規則是：新一輪由最後贏家（或起始者）自由出任何牌型。
        // 但題目這句話可能暗示：每當一個新回合開始（即上一輪大家都 Pass），出牌者必須遵循 5>2>1 的順序？
        // 這不太合理，因為這樣遊戲會很僵化。
        // 另一種解讀：這只是在描述牌型的大小關係？不，牌型大小關係前面已經講過了。
        // 最可能的解讀：這是對「起始玩家」在第一輪的約束。
        // 或者，這是對所有「自由出牌權」獲得者的約束？
        // 讓我們假設：每當一個人獲得自由出牌權（包括起始，或贏得一輪後），他必須優先出五張，若無則對，若無則單。
        // 這樣符合 "開局出牌的順序" 的描述，雖然用詞有點怪。
        // 但再看一眼題目："開局出牌的順序為..."，可能僅限於 "開局" (Game Start)。
        // 之後贏的人可以自由出？
        // 為了安全起見，我們實現一個策略函數，當 freeToPlay 為真時，優先嘗試 5 張，再 2 張，再 1 張。
        
        // 狀態機
        // lastPlay.type == 0 表示新的一輪，當前玩家可以自由出牌。
        
        while (finishedCount < 4) {
            if (finished[currentPlayer]) {
                currentPlayer = (currentPlayer + 1) % 4;
                continue;
            }

            vector<Card> move;
            if (lastPlay[0] == 0) {
                // Free to play. Strategy: Try 5, then 2, then 1.
                // We need to find the SMALLEST valid hand of the highest possible priority type.
                // Priority: 5-card > 2-card > 1-card.
                
                vector<Card> best5, best2, best1;
                int score5 = -1, score2 = -1, score1 = -1;
                
                // Check 5
                if (players[currentPlayer].cards.size() >= 5) {
                     // Find smallest valid 5-card hand
                     // Iterate all combinations, find valid ones, pick smallest
                     // Valid types: 3,4,5,6 (Straight, FH, 4K, SF)
                     // Note: Dragon is handled at start, so ignore here.
                     int n = players[currentPlayer].cards.size();
                     vector<int> idx(n);
                     for(int i=0; i<n; ++i) idx[i] = i;
                     for (int i = 0; i < n; ++i)
                     for (int j = i + 1; j < n; ++j)
                     for (int k = j + 1; k < n; ++k)
                     for (int l = k + 1; l < n; ++l)
                     for (int m = l + 1; m < n; ++m) {
                        vector<Card> cand = {players[currentPlayer].cards[i], players[currentPlayer].cards[j], players[currentPlayer].cards[k], players[currentPlayer].cards[l], players[currentPlayer].cards[m]};
                        auto res = players[currentPlayer].analyzeSubset(cand);
                        if (res[0] >= 3 && res[0] <= 6) {
                            int s = 0; for(auto& c:cand) s+=c.rank*10+c.suit;
                            if (best5.empty() || s < score5) { best5 = cand; score5 = s; }
                        }
                     }
                }
                
                if (!best5.empty()) {
                    move = best5;
                } else {
                    // Check 2
                    int n = players[currentPlayer].cards.size();
                    for (int i = 0; i < n; ++i) {
                        for (int j = i + 1; j < n; ++j) {
                            vector<Card> cand = {players[currentPlayer].cards[i], players[currentPlayer].cards[j]};
                            auto res = players[currentPlayer].analyzeSubset(cand);
                            if (res[0] == 2) {
                                int s = cand[0].rank*10 + cand[0].suit + cand[1].rank*10 + cand[1].suit;
                                if (best2.empty() || s < score2) { best2 = cand; score2 = s; }
                            }
                        }
                    }
                    if (!best2.empty()) {
                        move = best2;
                    } else {
                        // Check 1
                        int n = players[currentPlayer].cards.size();
                        for (int i = 0; i < n; ++i) {
                            vector<Card> cand = {players[currentPlayer].cards[i]};
                            auto res = players[currentPlayer].analyzeSubset(cand);
                            if (res[0] == 1) {
                                int s = cand[0].rank*10 + cand[0].suit;
                                if (best1.empty() || s < score1) { best1 = cand; score1 = s; }
                            }
                        }
                        move = best1;
                    }
                }
                
                if (move.empty()) {
                    // Should not happen unless no cards?
                    passCount++;
                    currentPlayer = (currentPlayer + 1) % 4;
                    continue;
                }
                
                // Play the move
                auto res = players[currentPlayer].analyzeSubset(move);
                lastPlay = res;
                players[currentPlayer].removeCards(move);
                passCount = 0; // Reset pass count since a valid move was made
                
            } else {
                // Must beat lastPlay
                move = players[currentPlayer].findBestMove(lastPlay);
                
                if (move.empty()) {
                    // PASS
                    passCount++;
                } else {
                    auto res = players[currentPlayer].analyzeSubset(move);
                    lastPlay = res;
                    players[currentPlayer].removeCards(move);
                    passCount = 0;
                }
            }

            // Check if player won
            if (players[currentPlayer].isEmpty()) {
                resultOrder.push_back(players[currentPlayer].id);
                finished[currentPlayer] = true;
                finishedCount++;
                
                if (finishedCount == 4) break;
                
                // Winner starts new round?
                // In Big Two, the person who finishes doesn't start next round (they are out).
                // The next person in sequence starts? Or the person who would have been next?
                // Usually, the winner of the trick starts the next round. But if they are out,
                // the next available player starts?
                // Actually, if someone empties their hand, they are out.
                // The last played hand is still on the table? No, the round ends when someone wins?
                // No, the game continues until everyone finishes.
                // When someone empties hand, the current trick is discarded?
                // And the NEXT player (clockwise from the winner) starts a new round?
                // Let's assume: Winner is removed. Next player (who hasn't finished) starts fresh (lastPlay = 0).
                lastPlay = {0, 0, 0};
                passCount = 0;
                // Find next player
                int nextP = (currentPlayer + 1) % 4;
                while (finished[nextP]) nextP = (nextP + 1) % 4;
                currentPlayer = nextP;
                continue;
            }

            // Check if everyone passed
            if (passCount == 3) { // 3 others passed
                // Current player wins the trick and starts new round
                lastPlay = {0, 0, 0};
                passCount = 0;
                // Next player is the one after current
                int nextP = (currentPlayer + 1) % 4;
                while (finished[nextP]) nextP = (nextP + 1) % 4;
                currentPlayer = nextP;
                continue;
            }

            // Next player
            currentPlayer = (currentPlayer + 1) % 4;
        }

        for (int i = 0; i < 4; ++i) {
            if (i > 0) cout << " ";
            cout << resultOrder[i];
        }
        cout << "\n";
    }

    return 0;
}
