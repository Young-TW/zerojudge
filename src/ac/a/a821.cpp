#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, R;
    while (std::cin >> N >> R) {
        std::unordered_map<std::string, int> id;
        std::vector<std::string> names;
        std::vector<std::unordered_set<int>> beat;
        std::vector<char> lost;          // 0 = never lost, 1 = lost at least once

        int readCnt = 0;
        std::string A, B;
        while (readCnt < R && (std::cin >> A >> B)) {
            // ensure both names have an id
            if (id.find(A) == id.end()) {
                int newId = static_cast<int>(names.size());
                id[A] = newId;
                names.push_back(A);
                beat.emplace_back();
                lost.push_back(0);
            }
            if (id.find(B) == id.end()) {
                int newId = static_cast<int>(names.size());
                id[B] = newId;
                names.push_back(B);
                beat.emplace_back();
                lost.push_back(0);
            }
            int u = id[A];
            int v = id[B];
            beat[u].insert(v);   // duplicates are ignored automatically
            lost[v] = 1;
            ++readCnt;
        }

        int M = static_cast<int>(names.size());
        std::string answer;
        for (int i = 0; i < M; ++i) {
            if (!lost[i] && static_cast<int>(beat[i].size()) == M - 1) {
                answer = names[i];
                break;
            }
        }
        std::cout << answer << '\n';
    }
    return 0;
}
