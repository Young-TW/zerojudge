#include <bits/stdc++.h>
using namespace std;

/* ---------- dice orientation ---------- */
struct Ori {
    uint8_t f[6];                 // 0 top,1 bottom,2 north,3 south,4 west,5 east
    bool operator==(const Ori& o) const {
        for (int i = 0; i < 6; ++i) if (f[i] != o.f[i]) return false;
        return true;
    }
};

struct OriHash {
    size_t operator()(const Ori& o) const noexcept {
        size_t h = 0;
        for (int i = 0; i < 6; ++i) h = h * 31 + o.f[i];
        return h;
    }
};

vector<Ori> orientations;               // size = 24
int transOri[24][4];                    // 0:N,1:S,2:W,3:E

Ori roll(const Ori& a, int dir) {
    Ori g;
    const uint8_t* o = a.f;
    switch (dir) {
        case 0: // north
            g.f[0] = o[3]; g.f[1] = o[2];
            g.f[2] = o[0]; g.f[3] = o[1];
            g.f[4] = o[4]; g.f[5] = o[5];
            break;
        case 1: // south
            g.f[0] = o[2]; g.f[1] = o[3];
            g.f[2] = o[1]; g.f[3] = o[0];
            g.f[4] = o[4]; g.f[5] = o[5];
            break;
        case 2: // west
            g.f[0] = o[5]; g.f[1] = o[4];
            g.f[2] = o[2]; g.f[3] = o[3];
            g.f[4] = o[0]; g.f[5] = o[1];
            break;
        case 3: // east
            g.f[0] = o[4]; g.f[1] = o[5];
            g.f[2] = o[2]; g.f[3] = o[3];
            g.f[4] = o[1]; g.f[5] = o[0];
            break;
    }
    return g;
}

void build_orientations() {
    Ori start;
    for (int i = 0; i < 6; ++i) start.f[i] = i;   // identity
    unordered_map<Ori,int,OriHash> id;
    queue<Ori> q;
    q.push(start);
    id[start] = 0;
    orientations.push_back(start);
    while (!q.empty()) {
        Ori cur = q.front(); q.pop();
        int curId = id[cur];
        for (int d = 0; d < 4; ++d) {
            Ori nxt = roll(cur, d);
            auto it = id.find(nxt);
            if (it == id.end()) {
                int nid = (int)orientations.size();
                id[nxt] = nid;
                orientations.push_back(nxt);
                q.push(nxt);
                transOri[curId][d] = nid;
            } else {
                transOri[curId][d] = it->second;
            }
        }
    }
}

/* ---------- state packing ---------- */
inline uint32_t pack(uint8_t pos, uint8_t ori, uint16_t board, uint8_t faces) {
    return (uint32_t)pos |
           ((uint32_t)ori << 4) |
           ((uint32_t)board << 9) |
           ((uint32_t)faces << 25);
}
inline void unpack(uint32_t key, uint8_t &pos, uint8_t &ori,
                   uint16_t &board, uint8_t &faces) {
    pos   =  key        & 0xF;
    ori   = (key >> 4)  & 0x1F;
    board = (key >> 9)  & 0xFFFF;
    faces = (key >> 25) & 0x3F;
}

/* ---------- BFS ---------- */
int bfs(uint8_t startPos, uint16_t startBoard) {
    const uint8_t goalFaces = 0x3F;          // 6 bits set
    unordered_set<uint32_t> visited;
    visited.reserve(2000000);
    struct Node { uint32_t key; int dist; };
    queue<Node> q;
    uint32_t startKey = pack(startPos, 0, startBoard, 0);
    visited.insert(startKey);
    q.push({startKey, 0});

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        uint8_t pos, ori, faces;
        uint16_t board;
        unpack(cur.key, pos, ori, board, faces);
        if (faces == goalFaces) return cur.dist;

        int r = pos / 4, c = pos % 4;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;
            uint8_t npos = nr * 4 + nc;
            uint8_t nori = transOri[ori][d];
            const Ori &o = orientations[nori];
            uint8_t bottom = o.f[1];               // index of new bottom face

            bool tileHas   = (board >> npos) & 1u;
            bool bottomHas = (faces >> bottom) & 1u;

            uint16_t nboard = board;
            uint8_t nfaces = faces;
            if (tileHas != bottomHas) {
                nboard ^= (1u << npos);
                nfaces ^= (1u << bottom);
            }

            uint32_t nkey = pack(npos, nori, nboard, nfaces);
            if (visited.insert(nkey).second) {
                q.push({nkey, cur.dist + 1});
            }
        }
    }
    return -1;   // impossible
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    build_orientations();

    int T;
    if (!(cin >> T)) return 0;
    string line;
    getline(cin, line);               // consume end‑of‑line after T

    for (int tc = 0; tc < T; ++tc) {
        // skip blank lines
        while (getline(cin, line)) {
            if (!line.empty()) break;
        }
        vector<string> g(4);
        g[0] = line;
        for (int i = 1; i < 4; ++i) getline(cin, g[i]);

        uint8_t startPos = 0;
        uint16_t startBoard = 0;
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                char ch = g[r][c];
                int idx = r * 4 + c;
                if (ch == 'D') startPos = idx;
                else if (ch == 'X') startBoard |= (1u << idx);
            }
        }

        int ans = bfs(startPos, startBoard);
        if (ans == -1) cout << "impossible\n";
        else           cout << ans << "\n";
    }
    return 0;
}
