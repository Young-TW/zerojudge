#include <bits/stdc++.h>
using namespace std;

static const double PI = acos(-1.0);
static const int SAMPLE_RATE = 8000;
static const int AMPLITUDE = 32767;

int noteIndex(char letter, char accidental) {
    // base indices for natural notes
    int base;
    switch (letter) {
        case 'C': base = 0; break;
        case 'D': base = 2; break;
        case 'E': base = 4; break;
        case 'F': base = 5; break;
        case 'G': base = 7; break;
        case 'A': base = 9; break;
        case 'B': base = 11; break;
        default:  base = 0; // never happens
    }
    if (accidental == '#') base += 1;
    else if (accidental == 'b') base -= 1;
    // bring into [0,11] range (the envelope never uses out‑of‑range notes)
    if (base < 0) base += 12;
    if (base >= 12) base -= 12;
    return base;
}

double frequencyFromNote(const string& note) {
    // note format: Letter [#|b] Octave
    char letter = note[0];
    char accidental = 0;
    int pos = 1;
    if (note[1] == '#' || note[1] == 'b') {
        accidental = note[1];
        pos = 2;
    }
    int octave = note[pos] - '0';

    int idx = noteIndex(letter, accidental);
    // semitone distance from A4
    int n = (octave - 4) * 12 + (idx - 9);
    return 440.0 * pow(2.0, n / 12.0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string note;
    while (cin >> note) {
        int P;
        if (!(cin >> P)) break;
        vector<double> xs(P), ys(P);
        for (int i = 0; i < P; ++i) {
            cin >> xs[i] >> ys[i];
        }

        double f = frequencyFromNote(note);
        vector<int> samples;
        samples.reserve(SAMPLE_RATE);

        int seg = 0; // current segment index
        for (int i = 0; i < SAMPLE_RATE; ++i) {
            double t = static_cast<double>(i) / SAMPLE_RATE; // 0 <= t < 1

            while (seg + 1 < P && t > xs[seg + 1]) ++seg;

            double y;
            if (seg + 1 == P) {
                y = ys.back(); // t == 1.0 would fall here, but never happens
            } else {
                double x0 = xs[seg], x1 = xs[seg + 1];
                double y0 = ys[seg], y1 = ys[seg + 1];
                if (fabs(x1 - x0) < 1e-12) y = y0; // degenerate, should not occur
                else
                    y = y0 + (y1 - y0) * (t - x0) / (x1 - x0);
            }

            double v = sin(2.0 * PI * f * t) * AMPLITUDE * y;
            long long iv = llround(v);
            if (iv > 32767) iv = 32767;
            if (iv < -32768) iv = -32768;
            samples.push_back(static_cast<int>(iv));
        }

        cout << SAMPLE_RATE << ' ' << SAMPLE_RATE << '\n';
        for (int i = 0; i < SAMPLE_RATE; ++i) {
            if (i) cout << ' ';
            cout << samples[i];
        }
        cout << '\n';
    }
    return 0;
}
