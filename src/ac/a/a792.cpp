#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    while (getline(cin, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\n' || line.back() == '\t')) {
            line.pop_back();
        }
        if (line.empty()) continue;
        
        unordered_map<string, int> actor_to_id;
        vector<string> id_to_actor;
        vector<vector<int>> adj;
        
        auto get_id = [&](const string& name) {
            if (actor_to_id.find(name) == actor_to_id.end()) {
                int id = id_to_actor.size();
                actor_to_id[name] = id;
                id_to_actor.push_back(name);
                adj.push_back({});
                return id;
            }
            return actor_to_id[name];
        };

        vector<string> actors_to_query;
        bool in_movies = false;
        bool in_actors = false;
        bool ended = false;

        do {
            while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\n' || line.back() == '\t')) {
                line.pop_back();
            }
            if (line.empty()) {
                continue;
            }
            
            stringstream ss(line);
            string token;
            ss >> token;
            if (token == "[MOVIES]") {
                in_movies = true;
                in_actors = false;
                vector<int> actor_ids;
                while (ss >> token) {
                    actor_ids.push_back(get_id(token));
                }
                for (size_t i = 0; i < actor_ids.size(); ++i) {
                    for (size_t j = i + 1; j < actor_ids.size(); ++j) {
                        adj[actor_ids[i]].push_back(actor_ids[j]);
                        adj[actor_ids[j]].push_back(actor_ids[i]);
                    }
                }
            } else if (token == "[ACTORS]") {
                in_movies = false;
                in_actors = true;
                while (ss >> token) {
                    actors_to_query.push_back(token);
                }
            } else if (token == "[END]") {
                ended = true;
                break;
            } else {
                if (in_movies) {
                    vector<int> actor_ids;
                    while (ss >> token) {
                        actor_ids.push_back(get_id(token));
                    }
                    for (size_t i = 0; i < actor_ids.size(); ++i) {
                        for (size_t j = i + 1; j < actor_ids.size(); ++j) {
                            adj[actor_ids[i]].push_back(actor_ids[j]);
                            adj[actor_ids[j]].push_back(actor_ids[i]);
                        }
                    }
                } else if (in_actors) {
                    actors_to_query.push_back(token);
                    while (ss >> token) {
                        actors_to_query.push_back(token);
                    }
                }
            }
        } while (getline(cin, line));

        if (!ended && actors_to_query.empty() && adj.empty()) {
            break;
        }

        int kevin_bacon_id = -1;
        if (actor_to_id.find("KevinBacon") != actor_to_id.end()) {
            kevin_bacon_id = actor_to_id["KevinBacon"];
        } else {
            kevin_bacon_id = get_id("KevinBacon");
        }

        vector<int> dist(id_to_actor.size(), -1);
        queue<int> q;
        q.push(kevin_bacon_id);
        dist[kevin_bacon_id] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        for (const string& actor : actors_to_query) {
            if (actor == "KevinBacon") {
                cout << actor << " has a Bacon number of 0\n";
            } else if (actor_to_id.find(actor) != actor_to_id.end()) {
                int id = actor_to_id[actor];
                if (dist[id] != -1) {
                    cout << actor << " has a Bacon number of " << dist[id] << "\n";
                }
            }
        }
    }

    return 0;
}
