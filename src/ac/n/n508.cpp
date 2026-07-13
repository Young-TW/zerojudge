#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Event {
    int time;
    int type;
    bool operator<(const Event& other) const {
        if (time != other.time) return time < other.time;
        return type < other.type;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<Event> events;
        events.reserve(N * 2);
        for (int i = 0; i < N; ++i) {
            string s1;
            int id;
            char c;
            int sh, sm, eh, em;
            cin >> s1 >> id >> c >> sh >> c >> sm >> c >> eh >> c >> em;
            int start_time = sh * 60 + sm;
            int end_time = eh * 60 + em;
            events.push_back({start_time, 1});
            events.push_back({end_time, -1});
        }
        sort(events.begin(), events.end());
        int current = 0;
        int max_rooms = 0;
        for (size_t i = 0; i < events.size(); ++i) {
            current += events[i].type;
            if (current > max_rooms) {
                max_rooms = current;
            }
        }
        cout << max_rooms << "\n";
    }
    return 0;
}
