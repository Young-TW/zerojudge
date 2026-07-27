#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int R = 8000;
    const int SAMPLES_PER_NOTE = 2000;
    const double PI = acos(-1.0);
    // frequencies for notes 1..7
    const double freq[8] = {
        0.0,
        261.63, // 1
        293.66, // 2
        329.63, // 3
        349.23, // 4
        392.00, // 5
        440.00, // 6
        493.88  // 7
    };

    string line;
    bool firstCase = true;
    while (getline(cin, line)) {
        // ignore empty lines
        if (line.empty()) continue;

        vector<int> samples;
        samples.reserve(line.size() * SAMPLES_PER_NOTE);

        double curFreq = 0.0;
        double delta = 0.0;
        double phase = 0.0;

        for (char c : line) {
            if (c == '0') {                     // rest
                for (int i = 0; i < SAMPLES_PER_NOTE; ++i)
                    samples.push_back(0);
                curFreq = 0.0;
                delta = 0.0;
                phase = 0.0;
            } else if (c >= '1' && c <= '7') { // new note
                curFreq = freq[c - '0'];
                delta = 2.0 * PI * curFreq / R;
                phase = 0.0;
                for (int i = 0; i < SAMPLES_PER_NOTE; ++i) {
                    int val = (int)std::lround(32767.0 * sin(phase));
                    samples.push_back(val);
                    phase += delta;
                }
            } else if (c == '-') {              // tie
                if (curFreq == 0.0) {            // safety, treat as rest
                    for (int i = 0; i < SAMPLES_PER_NOTE; ++i)
                        samples.push_back(0);
                } else {
                    for (int i = 0; i < SAMPLES_PER_NOTE; ++i) {
                        int val = (int)std::lround(32767.0 * sin(phase));
                        samples.push_back(val);
                        phase += delta;
                    }
                }
            }
            // any other character is ignored (should not appear)
        }

        // output
        cout << R << ' ' << samples.size() << '\n';
        for (size_t i = 0; i < samples.size(); ++i) {
            if (i) cout << ' ';
            cout << samples[i];
        }
        cout << '\n';
    }
    return 0;
}
