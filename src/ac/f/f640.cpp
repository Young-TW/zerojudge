#include <iostream>
#include <string>

using namespace std;

long long parse() {
    string token;
    if (!(cin >> token)) {
        return 0;
    }
    if (token == "f") {
        long long x = parse();
        return 2 * x - 3;
    } else if (token == "g") {
        long long x = parse();
        long long y = parse();
        return 2 * x + y - 7;
    } else if (token == "h") {
        long long x = parse();
        long long y = parse();
        long long z = parse();
        return 3 * x - 2 * y + z;
    } else {
        return stoll(token);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << parse() << "\n";
    return 0;
}
