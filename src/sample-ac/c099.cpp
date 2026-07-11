#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<string, int> name_to_id;
    vector<string> id_to_name;
    vector<int> parent_id;

    auto get_id = [&](const string& s) -> int {
        if (name_to_id.count(s)) return name_to_id[s];
        int id = id_to_name.size();
        name_to_id[s] = id;
        id_to_name.push_back(s);
        parent_id.push_back(-1);
        return id;
    };

    string child, parent;
    while (cin >> child >> parent) {
        if (child == "no.child") break;
        int c_id = get_id(child);
        int p_id = get_id(parent);
        parent_id[c_id] = p_id;
    }

    string q_child, q_parent;
    while (cin >> q_child >> q_parent) {
        int p_id = get_id(q_child);
        int q_id = get_id(q_parent);

        if (p_id == q_id) {
            cout << "no relation\n";
            continue;
        }

        map<int, int> anc_p;
        int curr = p_id;
        int dist = 0;
        while (curr != -1) {
            anc_p[curr] = dist;
            curr = parent_id[curr];
            dist++;
        }

        curr = q_id;
        dist = 0;
        int lca = -1;
        int dist_q = 0;
        while (curr != -1) {
            if (anc_p.count(curr)) {
                lca = curr;
                dist_q = dist;
                break;
            }
            curr = parent_id[curr];
            dist++;
        }

        if (lca == -1) {
            cout << "no relation\n";
            continue;
        }

        int dist_p = anc_p[lca];

        if (lca == p_id) {
            int k = dist_q - 1;
            if (k == 0) {
                cout << "parent\n";
            } else if (k == 1) {
                cout << "grand parent\n";
            } else {
                for (int i = 0; i < k - 1; ++i) cout << "great ";
                cout << "grand parent\n";
            }
        } else if (lca == q_id) {
            int k = dist_p - 1;
            if (k == 0) {
                cout << "child\n";
            } else if (k == 1) {
                cout << "grand child\n";
            } else {
                for (int i = 0; i < k - 1; ++i) cout << "great ";
                cout << "grand child\n";
            }
        } else {
            int m = dist_p - 1;
            int n = dist_q - 1;
            int k = m < n ? m : n;
            int j = m > n ? m - n : n - m;
            if (k == 0 && j == 0) {
                cout << "sibling\n";
            } else if (j == 0) {
                cout << k << " cousin\n";
            } else {
                cout << k << " cousin removed " << j << "\n";
            }
        }
    }

    return 0;
}
