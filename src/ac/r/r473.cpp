#include <bits/stdc++.h>
using namespace std;

struct Vec {
    int x, y, z;
};

int dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec cross(const Vec& a, const Vec& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* vectors of the six faces, order matches the statement:
       0 top, 1 front, 2 right, 3 left, 4 back, 5 bottom */
    const Vec face[6] = {
        { 0, 1, 0},   // 0 top
        { 0, 0, 1},   // 1 front
        { 1, 0, 0},   // 2 right
        {-1, 0, 0},   // 3 left
        { 0, 0,-1},   // 4 back
        { 0,-1, 0}    // 5 bottom
    };

    // generate all 24 rotations
    vector<array<int,6>> perms;
    for (int up = 0; up < 6; ++up) {
        for (int front = 0; front < 6; ++front) {
            if (up == front) continue;
            if (dot(face[up], face[front]) != 0) continue; // not orthogonal
            Vec right = cross(face[up], face[front]);
            if (abs(right.x) + abs(right.y) + abs(right.z) != 1) continue; // not unit

            array<int,6> p{};
            for (int i = 0; i < 6; ++i) {
                const Vec& v = face[i];
                // coordinates of v in the original basis (right0, up0, front0)
                int xr = dot(v, face[2]);   // right0 = face[2]
                int yu = dot(v, face[0]);   // up0    = face[0]
                int zf = dot(v, face[1]);   // front0 = face[1]

                // rotated vector
                int nx = xr * right.x + yu * face[up].x + zf * face[front].x;
                int ny = xr * right.y + yu * face[up].y + zf * face[front].y;
                int nz = xr * right.z + yu * face[up].z + zf * face[front].z;

                // find which face has this vector
                int to = -1;
                for (int j = 0; j < 6; ++j) {
                    if (face[j].x == nx && face[j].y == ny && face[j].z == nz) {
                        to = j;
                        break;
                    }
                }
                p[i] = to;   // original face i moves to position 'to'
            }
            // avoid duplicates
            bool exists = false;
            for (auto& q : perms) if (q == p) { exists = true; break; }
            if (!exists) perms.push_back(p);
        }
    }
    // perms must contain 24 elements
    // (assert not needed for final code)

    string line;
    while (cin >> line) {
        if (line.size() < 12) continue;          // safety
        string a = line.substr(0, 6);
        string b = line.substr(6, 6);
        bool equal = false;
        for (const auto& p : perms) {
            bool ok = true;
            for (int i = 0; i < 6; ++i) {
                if (a[i] != b[p[i]]) { ok = false; break; }
            }
            if (ok) { equal = true; break; }
        }
        cout << (equal ? "TRUE" : "FALSE") << '\n';
    }
    return 0;
}
