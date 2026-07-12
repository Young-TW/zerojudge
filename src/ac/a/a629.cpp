#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int prefix[7] = {0, 2, 4, 5, 7, 9, 11};
string note_names[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

int get_D(int k) {
    int q = k / 7;
    int r = k % 7;
    if (r < 0) {
        r += 7;
        q--;
    }
    return q * 12 + prefix[r];
}

int note_to_num(char c) {
    switch (c) {
        case 'A': return 9;
        case 'B': return 11;
        case 'C': return 0;
        case 'D': return 2;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 7;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    while (getline(cin, line)) {
        int p = 0;
        while (p < line.length() && isspace(line[p])) p++;
        if (p == line.length()) continue;
        
        char c = line[p++];
        int curr_note = note_to_num(c);
        
        while (p < line.length() && isspace(line[p])) p++;
        if (p < line.length() && line[p] == '#') {
            curr_note++;
            p++;
        }
        curr_note = (curr_note + 12) % 12;
        
        cout << note_names[curr_note];
        
        int curr_idx = 0;
        while (p < line.length()) {
            while (p < line.length() && isspace(line[p])) p++;
            if (p == line.length()) break;
            
            int sign = 1;
            if (line[p] == '+') {
                sign = 1;
                p++;
            } else if (line[p] == '-') {
                sign = -1;
                p++;
            }
            
            while (p < line.length() && isspace(line[p])) p++;
            int num = 0;
            while (p < line.length() && isdigit(line[p])) {
                num = num * 10 + (line[p] - '0');
                p++;
            }
            int n = sign * num;
            int S;
            if (n > 0) S = n - 1;
            else S = n + 1;
            
            int next_idx = curr_idx + S;
            int offset = get_D(next_idx) - get_D(curr_idx);
            curr_note = (curr_note + offset) % 12;
            if (curr_note < 0) curr_note += 12;
            curr_idx = next_idx;
            
            cout << " " << note_names[curr_note];
        }
        cout << "\n";
    }
    
    return 0;
}
