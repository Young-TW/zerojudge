#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int X = 0, Y = 0;
int spawn_X = 0, spawn_Y = 0;
int HP = 10, SAT = 10;
int walk_acc = 0, run_acc = 0;
vector<pair<string, int>> backpack;
map<string, int> food_sat;
map<string, int> monsters;
map<pair<int, int>, vector<pair<string, int>>> dropped_items;

void pick_item(const string& name, int count) {
    for (auto &item : backpack) {
        if (item.first == name) {
            item.second += count;
            return;
        }
    }
    backpack.push_back({name, count});
}

void check_dropped_items() {
    auto it = dropped_items.find({X, Y});
    if (it != dropped_items.end()) {
        for (auto &item : it->second) {
            pick_item(item.first, item.second);
        }
        dropped_items.erase(it);
    }
}

void die() {
    if (!backpack.empty()) {
        dropped_items[{X, Y}].insert(dropped_items[{X, Y}].end(), backpack.begin(), backpack.end());
        backpack.clear();
    }
    X = spawn_X;
    Y = spawn_Y;
    HP = 10;
    SAT = 10;
    walk_acc = 0;
    run_acc = 0;
    check_dropped_items();
}

void move(const string& dir, int steps) {
    if (dir == "East") X += steps;
    else if (dir == "West") X -= steps;
    else if (dir == "North") Y += steps;
    else if (dir == "South") Y -= steps;
}

void walk(const string& dir, int steps) {
    move(dir, steps);
    walk_acc += steps;
    int consume = walk_acc / 50;
    walk_acc %= 50;
    SAT -= consume;
    if (SAT <= 0) {
        SAT = 0;
        die();
        return;
    }
    check_dropped_items();
}

void run(const string& dir, int steps) {
    move(dir, steps);
    run_acc += steps;
    int consume = run_acc / 25;
    run_acc %= 25;
    SAT -= consume;
    if (SAT <= 0) {
        SAT = 0;
        die();
        return;
    }
    check_dropped_items();
}

void sleep() {
    spawn_X = X;
    spawn_Y = Y;
}

void create(const string& monster, int hp) {
    monsters[monster] = hp;
}

void attacked(const string& monster) {
    int atk = monsters[monster];
    HP -= atk;
    if (HP <= 0) {
        HP = 0;
        die();
    }
}

void eat(const string& food, int count) {
    for (auto it = backpack.begin(); it != backpack.end(); ++it) {
        if (it->first == food) {
            it->second -= count;
            int sat_gain = food_sat[food] * count;
            SAT += sat_gain;
            if (SAT > 10) {
                int extra = SAT - 10;
                int heal = extra / 2;
                HP += heal;
                if (HP >= 10) {
                    HP = 10;
                    SAT = 10;
                } else {
                    SAT = 10 + (extra % 2);
                }
            }
            if (it->second == 0) {
                backpack.erase(it);
            }
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cmd;
    while (cin >> cmd) {
        if (cmd == "Print") {
            string target;
            cin >> target;
            if (target == "HP") {
                cout << "HP:" << HP << "\n";
            } else if (target == "SAT") {
                cout << "SAT:" << SAT << "\n";
            } else if (target == "At") {
                cout << "At:(" << X << "," << Y << ")\n";
            } else if (target == "Backpack") {
                cout << "Backpack:\n";
                for (auto &item : backpack) {
                    cout << item.first << " " << item.second << "\n";
                }
            }
        } else if (cmd == "Walk") {
            string dir;
            int steps;
            cin >> dir >> steps;
            walk(dir, steps);
        } else if (cmd == "Run") {
            string dir;
            int steps;
            cin >> dir >> steps;
            run(dir, steps);
        } else if (cmd == "Sleep") {
            sleep();
        } else if (cmd == "Create") {
            string monster;
            int hp;
            cin >> monster >> hp;
            create(monster, hp);
        } else if (cmd == "Attacked") {
            string by, monster;
            cin >> by >> monster;
            attacked(monster);
        } else if (cmd == "Pick") {
            string line;
            getline(cin, line);
            stringstream ss(line);
            string name;
            int n;
            ss >> name >> n;
            int e;
            if (ss >> e) {
                food_sat[name] = e;
            }
            pick_item(name, n);
        } else if (cmd == "Eat") {
            string food;
            int n;
            cin >> food >> n;
            eat(food, n);
        }
    }
    return 0;
}
