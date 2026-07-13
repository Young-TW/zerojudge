#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    long long time;
    int dc, dr, db;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, D;
    while (cin >> n >> D) {
        for (int i = 0; i < n; ++i) {
            int s;
            cin >> s;
            
            vector<Event> events;
            
            for (int j = 0; j < s; ++j) {
                long long Td, Ts, Th;
                int Rcore, Rram, Rbw;
                cin >> Td >> Ts >> Th >> Rcore >> Rram >> Rbw;
                
                if (Th == 0) continue;
                
                long long H = (long long)D * 24;
                long long start = (Td - 1) * 24 + Ts;
                long long end = start + Th;
                
                if (end <= H) {
                    events.push_back({start, Rcore, Rram, Rbw});
                    events.push_back({end, -Rcore, -Rram, -Rbw});
                } else {
                    events.push_back({start, Rcore, Rram, Rbw});
                    events.push_back({H, -Rcore, -Rram, -Rbw});
                    events.push_back({0, Rcore, Rram, Rbw});
                    events.push_back({end - H, -Rcore, -Rram, -Rbw});
                }
            }
            
            int zero;
            cin >> zero;
            
            sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
                return a.time < b.time;
            });
            
            int cur_c = 0, cur_r = 0, cur_b = 0;
            int max_c = 0, max_r = 0, max_b = 0;
            
            for (size_t j = 0; j < events.size(); ++j) {
                cur_c += events[j].dc;
                cur_r += events[j].dr;
                cur_b += events[j].db;
                
                while (j + 1 < events.size() && events[j+1].time == events[j].time) {
                    j++;
                    cur_c += events[j].dc;
                    cur_r += events[j].dr;
                    cur_b += events[j].db;
                }
                
                max_c = max(max_c, cur_c);
                max_r = max(max_r, cur_r);
                max_b = max(max_b, cur_b);
            }
            
            cout << max_c << " " << max_r << " " << max_b << "\n";
        }
    }
    
    return 0;
}
