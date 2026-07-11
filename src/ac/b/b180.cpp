#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Guest {
    int id;
    int t; // 待在水上樂園的時間
    int T; // 環繞探索樂園的時間
    int arrive_time; // 到達排隊區的時間
};

// 模擬過程：
// 1. 將所有旅客按照到达時間 (t) 排序。
// 2. 使用一個優先隊列 (min-heap) 來追蹤每輛車何時會回來 (可用時間)。
//    堆中儲存的是車輛可用的時間點。
// 3. 對於每一個旅客：
//    a. 檢查是否有車輛在旅客到達時或之前已經回來，且等待時間不超過 30 分鐘。
//       實際上，我們需要找到一輛車，使得 max(車回來時間, 旅客到達時間) - 旅客到達時間 <= 30。
//       也就是 車回來時間 <= 旅客到達時間 + 30。
//    b. 如果有多輛車滿足條件，為了節省車輛數，我們應該選擇哪一輛？
//       題目問的是「至少」需要幾部車。這是一個貪婪策略問題。
//       當一個旅客到來時，如果有空車（或即將回來且在容忍範圍內的車），我們就分配給他。
//       關鍵在於：如果有多輛車可用，該選哪一輛？
//       應該選最早回來的車嗎？還是選最晚回來的車（但在容忍範圍內）？
//       考慮到我們要最小化車輛總數，我們希望盡量複用現有的車，而不是開新車。
//       只要有一輛車能用，就不需要新車。
//       但是，如果我們隨便選一輛，可能會導致後面的旅客無車可用而必須增加新車。
//       正確的貪婪策略是：當旅客 i 到達時，在所有「能在旅客離開前趕到」的車輛中，
//       選擇「最早回來」的那一輛。為什麼？因為如果連最早回來的車都來不及（或者說，
//       如果最早回來的車都會讓旅客等待超過 30 分鐘），那麼其他更晚回來的車肯定也不行。
//       反過來說，如果最早回來的車可以用，那用它是最安全的，因為它釋放得最早，對後續影響最小？
//       不對，這裡的邏輯是：我們維護一個 min-heap，裡面是所有車輛的「下次可用時間」。
//       當旅客在時間 `arrive` 到達時，我們檢查 heap 頂端的車（最早可用的車）。
//       如果這輛車的可用時間 `free_time` 滿足 `free_time <= arrive + 30`，那麼這輛車就可以服務該旅客。
//       為什麼只看 heap 頂端？因為如果 heap 頂端的車（最早回來的）都無法在 `arrive + 30` 前到達（即 `free_time > arrive + 30`），
//       那麼 heap 裡其他的車（回來得更晚）肯定也無法滿足條件。這時就必須增加新車。
//       如果 heap 頂端的車滿足條件，我們就使用這輛車。這輛車的新可用時間將變為：
//       `max(free_time, arrive) + T`。
//       這裡 `max(free_time, arrive)` 是實際發車時間（車要等旅客，或旅客要等車）。
//       然後加上遊園時間 `T` 就是下次可用時間。
//    c. 如果 heap 為空，或者 heap 頂端的車無法滿足條件（等待超過 30 分鐘），則必須新增一輛車。
//       新車的初始可用時間可以視為 0 或者負無限大，但實際上第一趟行程直接從旅客到達時間開始算。
//       新車的服務結束時間 = `arrive + T`。

void solve() {
    int m;
    if (!(cin >> m)) return;

    vector<Guest> guests(m);
    for (int i = 0; i < m; ++i) {
        guests[i].id = i;
        cin >> guests[i].t >> guests[i].T;
        guests[i].arrive_time = guests[i].t;
    }

    // 按照到達時間排序
    sort(guests.begin(), guests.end(), [](const Guest& a, const Guest& b) {
        return a.arrive_time < b.arrive_time;
    });

    // Min-heap 儲存每輛車的「下次可用時間」
    priority_queue<int, vector<int>, greater<int> > cars;

    for (int i = 0; i < m; ++i) {
        int arrive = guests[i].arrive_time;
        int duration = guests[i].T;

        // 檢查是否有車可用
        bool found = false;
        if (!cars.empty()) {
            int earliest_free = cars.top();
            // 判斷最早回來的車是否能趕上
            // 旅客願意等待的最晚發車時間是 arrive + 30
            // 車實際發車時間是 max(earliest_free, arrive)
            // 等待時間 = max(earliest_free, arrive) - arrive
            // 條件：等待時間 <= 30  =>  max(earliest_free, arrive) <= arrive + 30
            // 這等同於：如果 earliest_free > arrive，則 earliest_free - arrive <= 30
            //          如果 earliest_free <= arrive，則等待時間為 0，一定滿足
            
            if (earliest_free <= arrive + 30) {
                // 可以使用這輛車
                cars.pop();
                int start_time = max(earliest_free, arrive);
                int next_free = start_time + duration;
                cars.push(next_free);
                found = true;
            }
        }

        if (!found) {
            // 需要新車
            // 新車直接從旅客到達時間開始服務（假設新車隨時待命，或者說新車加入的時刻就是旅客到達時刻）
            // 其實新車的邏輯是：發車時間 = arrive，結束時間 = arrive + T
            cars.push(arrive + duration);
        }
    }

    cout << cars.size() << endl;
}

int main() {
    // 處理多筆測資直到 EOF
    // 由於輸入格式是第一行 m，接下來 m 行。
    // 我們需要在 solve 內部讀取 m，如果讀取失敗則停止。
    // 上面的 solve 函數已經處理了讀取 m 的邏輯，但為了循環調用，我們需要調整結構。
    
    // 重新設計 main 循環
    cin.clear();
    while (true) {
        // 嘗試讀取 m
        int m;
        if (!(cin >> m)) break;
        
        vector<pair<int, int> > data(m);
        for (int i = 0; i < m; ++i) {
            cin >> data[i].first >> data[i].second;
        }

        // 排序
        sort(data.begin(), data.end());

        priority_queue<int, vector<int>, greater<int> > cars;

        for (int i = 0; i < m; ++i) {
            int arrive = data[i].first;
            int duration = data[i].second;

            bool use_existing = false;
            if (!cars.empty()) {
                int earliest_free = cars.top();
                if (earliest_free <= arrive + 30) {
                    cars.pop();
                    int start_time = max(earliest_free, arrive);
                    cars.push(start_time + duration);
                    use_existing = true;
                }
            }

            if (!use_existing) {
                cars.push(arrive + duration);
            }
        }

        cout << cars.size() << endl;
    }

    return 0;
}
