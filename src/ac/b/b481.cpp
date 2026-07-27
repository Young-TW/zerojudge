#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const int R = 8000;
    const int N = 8000;
    const double PI = std::acos(-1.0);
    const double AMPL = 32767.0;

    std::string note;
    double a5, a3, a1;
    while (std::cin >> note >> a5 >> a3 >> a1) {
        // ----- parse note -----
        char base = note[0];
        int accidental = 0;
        std::size_t idx = 1;
        if (note.size() >= 2) {
            if (note[1] == '#') { accidental = 1; idx = 2; }
            else if (note[1] == 'b') { accidental = -1; idx = 2; }
        }
        int octave = note[idx] - '0';          // single digit 1..7

        int natural = 0;                       // offset from C
        switch (base) {
            case 'C': natural = 0; break;
            case 'D': natural = 2; break;
            case 'E': natural = 4; break;
            case 'F': natural = 5; break;
            case 'G': natural = 7; break;
            case 'A': natural = 9; break;
            case 'B': natural = 11; break;
        }
        int note_offset = natural + accidental;   // may be -1 .. 12, but inputs stay valid
        int semitone = (octave - 4) * 12 + (note_offset - 9); // distance from A4

        double freq = 440.0 * std::pow(2.0, semitone / 12.0);

        // ----- generate samples -----
        std::vector<int> samples;
        samples.reserve(N);
        for (int i = 0; i < N; ++i) {
            double t = static_cast<double>(i) / R;
            double x = std::sin(2.0 * PI * freq * t);          // -1 .. 1
            double y = a5 * std::pow(x, 5) + a3 * std::pow(x, 3) + a1 * x;
            long long s = std::lround(y * AMPL);
            if (s > 32767) s = 32767;
            if (s < -32768) s = -32768;
            samples.push_back(static_cast<int>(s));
        }

        // ----- output -----
        std::cout << R << ' ' << N << '\n';
        for (int i = 0; i < N; ++i) {
            if (i) std::cout << ' ';
            std::cout << samples[i];
        }
        std::cout << '\n';
    }
    return 0;
}
