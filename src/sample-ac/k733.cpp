#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline int abs_int(int x) {
    return x < 0 ? -x : x;
}

struct Block {
    unsigned long long internal_dist;
    int first_target;
    int last_target;
    bool is_empty;
    int repeat_count;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        vector<Block> blocks;
        blocks.push_back({0, -1, -1, true, 0});
        for (size_t i = 0; i < s.length(); ++i) {
            if (s[i] == 'T') {
                int xx = (s[i+1] - '0') * 10 + (s[i+2] - '0');
                i += 2;
                Block& curr = blocks.back();
                if (curr.is_empty) {
                    curr.is_empty = false;
                    curr.first_target = xx;
                    curr.last_target = xx;
                    curr.internal_dist = 0;
                } else {
                    curr.internal_dist += abs_int(xx - curr.last_target);
                    curr.last_target = xx;
                }
            } else if (s[i] == 'L') {
                int x = s[i+1] - '0';
                i += 1;
                blocks.push_back({0, -1, -1, true, x});
            } else if (s[i] == 'E') {
                Block loop_body = blocks.back();
                blocks.pop_back();
                Block& parent = blocks.back();
                int R = loop_body.repeat_count;
                unsigned long long C = loop_body.internal_dist;
                int t1 = loop_body.first_target;
                int tk = loop_body.last_target;
                unsigned long long loop_internal_dist = (unsigned long long)R * C + (unsigned long long)(R - 1) * abs_int(t1 - tk);
                if (parent.is_empty) {
                    parent.is_empty = false;
                    parent.first_target = t1;
                    parent.last_target = tk;
                    parent.internal_dist = loop_internal_dist;
                } else {
                    parent.internal_dist += abs_int(t1 - parent.last_target) + loop_internal_dist;
                    parent.last_target = tk;
                }
            }
        }
        unsigned long long total_dist = 0;
        if (!blocks.back().is_empty) {
            total_dist = abs_int(blocks.back().first_target - 10) + blocks.back().internal_dist;
        }
        cout << total_dist << "\n";
    }
    return 0;
}
