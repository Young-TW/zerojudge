#include <iostream>
#include <vector>
#include <string>

using namespace std;

int target;
vector<string> answers;

/* depth‑first search
   cur   : current value
   nxt   : smallest integer that has not been used yet
   expr  : expression built so far
*/
void dfs(int cur, int nxt, const string &expr) {
    if (cur == target) {                 // found a solution
        answers.push_back(expr);
        return;
    }
    if (cur > target) return;            // cannot become smaller again

    /* 1) add nxt */
    if (cur + nxt <= target) {
        dfs(cur + nxt, nxt + 1,
            expr + " + " + to_string(nxt));
    }

    /* 2) multiply by 2 */
    if (cur * 2 <= target) {
        dfs(cur * 2, nxt,
            expr + " * 2");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        if (n == 0) break;               // termination
        target = n;
        answers.clear();

        dfs(1, 2, "1");                  // start expression

        if (answers.empty())
            cout << "cheat!\n";
        else
            for (const string &s : answers)
                cout << s << '\n';
    }
    return 0;
}
