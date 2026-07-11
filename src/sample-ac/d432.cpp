#include <iostream>
#include <string>

using namespace std;

void solve(const string& in, const string& post) {
    if (in.empty()) return;
    char root = post.back();
    cout << root;
    size_t pos = in.find(root);
    solve(in.substr(0, pos), post.substr(0, pos));
    solve(in.substr(pos + 1), post.substr(pos, post.size() - 1 - pos));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string in, post;
    while (cin >> in >> post) {
        solve(in, post);
        cout << "\n";
    }
    return 0;
}
