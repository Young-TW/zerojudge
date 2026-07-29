#include <bits/stdc++.h>
using namespace std;

static const double PI = acos(-1.0);

/* return fundamental frequency of a note string, e.g. "C#4" */
double noteFrequency(const string &s) {
    // natural note offsets from C
    static const int base[7] = {0, 2, 4, 5, 7, 9, 11}; // C D E F G A B
    char letter = s[0];
    int idx = string("CDEFGAB").find(letter);
    int offset = base[idx];

    size_t pos = 1;
    if (s[pos] == '#' || s[pos] == 'b') {
        if (s[pos] == '#') offset += 1;
        else offset -= 1;
        ++pos;
    }
    int octave = s[pos] - '0';

    int midi = (octave + 1) * 12 + offset;          // MIDI note number
    double freq = 440.0 * pow(2.0, (midi - 69) / 12.0);
    return freq;
}

/* clamp integer to [-32768,32767] */
int clampSample(long long v) {
    if (v > 32767) return 32767;
    if (v < -32768) return -32768;
    return static_cast<int>(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int R = 8000;
    const int N = 8000;

    string note;
    while (cin >> note) {
        double a[7]; // 1‑based
        for (int i = 1; i <= 6; ++i) cin >> a[i];
        double sum = 0.0;
        for (int i = 1; i <= 6; ++i) sum += a[i];

        double amp[7];
        for (int i = 1; i <= 6; ++i)
            amp[i] = 32767.0 * a[i] / sum;

        double f0 = noteFrequency(note);

        cout << R << ' ' << N << '\n';
        for (int n = 0; n < N; ++n) {
            double t = static_cast<double>(n) / R;
            double val = 0.0;
            for (int i = 1; i <= 6; ++i) {
                double angle = 2.0 * PI * i * f0 * t;
                val += amp[i] * sin(angle);
            }
            long long rounded = llround(val);
            int sample = clampSample(rounded);
            if (n) cout << ' ';
            cout << sample;
        }
        cout << '\n';
    }
    return 0;
}
