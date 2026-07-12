#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

void print_double(double x) {
    if (fabs(x) < 1e-12) x = 0;
    ostringstream oss;
    oss << fixed << setprecision(10) << x;
    string s = oss.str();
    size_t dot_pos = s.find('.');
    if (dot_pos != string::npos) {
        size_t last_non_zero = s.find_last_not_of('0');
        if (last_non_zero == dot_pos) {
            s.erase(dot_pos);
        } else if (last_non_zero != string::npos) {
            s.erase(last_non_zero + 1);
        }
    }
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, double> base_val = {
        {"CC", 1}, {"秋", 5}, {"猥褻洪", 12.5}, {"紅林", 20},
        {"Goodspeccy", -6}, {"Badspeed", -7.5}, {"Goodspeech", -20}
    };

    int X;
    if (!(cin >> X)) return 0;
    string delim = "跟DD說";

    for (int tc = 0; tc < X; ++tc) {
        double wake, defense;
        int M;
        cin >> wake >> defense >> M;
        string line;
        getline(cin, line); // consume newline

        unordered_set<string> silenced;
        string prev_speaker = "";
        bool initial_awake = (wake > 0);
        bool has_woken = false;
        string wake_cmd = "";

        for (int i = 0; i < M; ++i) {
            getline(cin, line);
            if (line.empty()) { i--; continue; }

            size_t pos = line.find(delim);
            if (pos == string::npos) continue;
            string speaker = line.substr(0, pos);
            string action = line.substr(pos + delim.length());

            if (silenced.count(speaker)) {
                continue;
            }

            // Combo: 紅林跟DD說我喜歡你
            if (speaker == "紅林" && action == "我喜歡你") {
                defense = 0;
                prev_speaker = speaker;
                continue;
            }

            // Step 1: Action Ability
            double mult = 1.0;
            bool ignore_def = false;

            if (action == "那邊有女生") {
                mult = 2.0;
            } else if (action == "DD端火鍋") {
                mult = 0.5;
            } else if (action == "起床了") {
                mult = 1.0;
            } else if (action == "頭皮屑好吃嗎") {
                wake *= 0.5;
                mult = 1.0;
            } else if (action == "我喜歡你") {
                ignore_def = true;
                mult = 1.0;
            } else if (action == "我就DD") {
                silenced.insert(speaker);
                mult = 1.0;
            } else if (action == "DD爛") {
                defense *= 0.5;
                mult = 1.0;
            } else if (action == "秋暗戀你") {
                defense *= 2.0;
                mult = 1.0;
            } else if (action == "你打呼很大聲") {
                if (!prev_speaker.empty()) {
                    silenced.insert(prev_speaker);
                }
                mult = 1.0;
            }

            // Step 2: Character Ability
            if (!silenced.count(speaker)) {
                double base = base_val[speaker];
                double val = base * mult;
                double delta = 0.0;
                if (val > 0) {
                    if (ignore_def) {
                        delta = val;
                    } else {
                        delta = max(0.0, val - defense);
                    }
                } else {
                    delta = val;
                }
                wake += delta;
            }

            // Check wake up
            if (!has_woken && !initial_awake && wake > 0) {
                has_woken = true;
                wake_cmd = speaker + "跟DD說" + action;
            }

            prev_speaker = speaker;
        }

        print_double(wake);
        cout << "\n";
        if (has_woken) {
            cout << wake_cmd << "\n";
        }
        if (initial_awake) {
            cout << "DD夢到了左翔\n";
        }
    }

    return 0;
}
