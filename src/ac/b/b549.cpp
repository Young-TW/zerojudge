#include <bits/stdc++.h>
using namespace std;

/* check whether the sequence of numbers (ordered by time) has
   longest decreasing subsequence length <= 2 */
bool ok(const map<int,int>& mp) {
    vector<int> tail;
    tail.reserve(mp.size());
    for (const auto& p : mp) {
        int v = -p.second;                     // decreasing -> increasing on -v
        auto it = lower_bound(tail.begin(), tail.end(), v);
        if (it == tail.end()) tail.push_back(v);
        else *it = v;
    }
    return tail.size() <= 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    int n;
    while (cin >> n) {
        vector<char> cmd(n);
        vector<int> tm(n);
        for (int i = 0; i < n; ++i) {
            cin >> cmd[i] >> tm[i];
        }

        map<int,int> time2num;                 // time -> file number
        set<int> freeNum;                      // still unused numbers
        for (int i = 0; i <= 999; ++i) freeNum.insert(i);
        unordered_map<int,int> orderOfNum;     // number -> insertion order
        int curOrder = 0;

        for (int i = 0; i < n; ++i) {
            if (cmd[i] == 'A') {               // add
                int t = tm[i];
                int chosen = -1;
                for (int num : freeNum) {
                    time2num.emplace(t, num);  // temporary insert
                    if (ok(time2num)) {
                        chosen = num;          // keep it
                        break;
                    }
                    time2num.erase(t);         // rollback
                }
                // problem guarantees existence
                freeNum.erase(chosen);
                orderOfNum[chosen] = curOrder++;
                // the pair (t,chosen) is already in time2num
            } else {                            // delete
                int t = tm[i];
                auto it = time2num.find(t);
                int num = it->second;
                time2num.erase(it);
                freeNum.insert(num);
                orderOfNum.erase(num);
            }
        }

        // collect remaining photos, sort by insertion order descending
        vector<pair<int,int>> vec;               // (order , num)
        vec.reserve(orderOfNum.size());
        for (const auto& kv : orderOfNum) vec.emplace_back(kv.second, kv.first);
        sort(vec.begin(), vec.end(),
             [](const pair<int,int>& a, const pair<int,int>& b){
                 return a.first > b.first;       // newer first
             });

        int newest = vec[0].second;
        int secondNewer = vec[1].second;

        if (!firstCase) cout << "--\n";
        firstCase = false;
        cout << "PIC" << setw(3) << setfill('0') << secondNewer << "\n";
        cout << "PIC" << setw(3) << setfill('0') << newest << "\n";
    }
    return 0;
}
