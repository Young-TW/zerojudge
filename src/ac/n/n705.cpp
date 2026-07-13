#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Forward {
    int source;
    int start;
    int duration;
    int target;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    if (!(cin >> N)) return 0;
    
    cout << "CALL FORWARDING OUTPUT\n";
    for (int i = 1; i <= N; ++i) {
        vector<Forward> forwards;
        int source, time, duration, target;
        while (cin >> source && source != 0) {
            cin >> time >> duration >> target;
            forwards.push_back({source, time, duration, target});
        }
        
        cout << "SYSTEM " << i << "\n";
        int ext;
        while (cin >> time && time != 9000) {
            cin >> ext;
            int current = ext;
            vector<bool> visited(10000, false);
            visited[current] = true;
            
            while (true) {
                int next_target = -1;
                for (const auto& f : forwards) {
                    if (f.source == current && time >= f.start && time <= f.start + f.duration) {
                        next_target = f.target;
                        break;
                    }
                }
                if (next_target == -1) break;
                if (visited[next_target]) {
                    current = 9999;
                    break;
                }
                visited[next_target] = true;
                current = next_target;
            }
            
            cout << "AT " << setw(4) << setfill('0') << time 
                 << " CALL TO " << setw(4) << setfill('0') << ext 
                 << " RINGS " << setw(4) << setfill('0') << current << "\n";
        }
    }
    cout << "END OF OUTPUT\n";
    
    return 0;
}
