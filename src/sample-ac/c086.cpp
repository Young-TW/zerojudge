#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    int N, X;
    int caseNum = 1;
    while (cin >> N >> X) {
        vector<int> cards(20);
        for (int i = 0; i < 20; ++i) {
            cin >> cards[i];
        }

        list<int> people;
        for (int i = 1; i <= N; ++i) {
            people.push_back(i);
        }

        bool finished = false;
        for (int k : cards) {
            if (people.size() <= X) {
                finished = true;
                break;
            }

            auto it = people.begin();
            int count = 1;
            while (it != people.end()) {
                if (count == k) {
                    it = people.erase(it);
                    count = 1;
                    if (people.size() == X) {
                        finished = true;
                        break;
                    }
                } else {
                    ++it;
                    ++count;
                }
            }
        }

        cout << "Selection #" << caseNum << endl;
        if (finished) {
            vector<int> result(people.begin(), people.end());
            for (int i = 0; i < result.size(); ++i) {
                if (i != 0) cout << " ";
                cout << result[i];
            }
            cout << endl;
        } else {
            vector<int> result(people.begin(), people.end());
            for (int i = 0; i < result.size(); ++i) {
                if (i != 0) cout << " ";
                cout << result[i];
            }
            cout << endl;
        }
        cout << endl;
        caseNum++;
    }
    return 0;
}
