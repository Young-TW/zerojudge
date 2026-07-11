#include <iostream>
#include <string>

using namespace std;

const int MAX_HASH = 456976;
int id[MAX_HASH];
int ts[MAX_HASH];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    int current_case = 0;
    
    while (cin >> N) {
        current_case++;
        int current_id = 1;
        string s;
        
        for (int i = 0; i < N; ++i) {
            cin >> s;
            int h = (s[0] - 'a') * 17576 + (s[1] - 'a') * 676 + (s[2] - 'a') * 26 + (s[3] - 'a');
            
            if (ts[h] == current_case) {
                cout << "Old! " << id[h] << "\n";
            } else {
                ts[h] = current_case;
                id[h] = current_id;
                cout << "New! " << current_id << "\n";
                current_id++;
            }
        }
    }
    
    return 0;
}
