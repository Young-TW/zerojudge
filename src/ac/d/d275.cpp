#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();
    
    while (T--) {
        string line;
        if (!getline(cin, line)) break;
        
        stringstream ss(line);
        string track;
        int m_count = 0;
        int f_count = 0;
        int track_count = 0;
        
        while (ss >> track) {
            if (track.length() >= 2) {
                if (track[0] == 'M') m_count++;
                else if (track[0] == 'F') f_count++;
                
                if (track[1] == 'M') m_count++;
                else if (track[1] == 'F') f_count++;
            }
            track_count++;
        }
        
        if (track_count >= 2 && m_count == f_count) {
            cout << "LOOP\n";
        } else {
            cout << "NO LOOP\n";
        }
    }
    
    return 0;
}
