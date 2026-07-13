#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    while (std::cin >> N) {
        std::vector<std::string> loc_order;
        std::map<std::string, int> loc_idx;
        std::vector<std::string> animal_order;
        std::map<std::string, int> animal_idx;
        std::map<std::string, std::map<std::string, int>> count;

        for (int i = 0; i < N; ++i) {
            std::string animal, loc;
            int num;
            std::cin >> animal >> num >> loc;
            
            if (loc_idx.find(loc) == loc_idx.end()) {
                loc_idx[loc] = loc_order.size();
                loc_order.push_back(loc);
            }
            
            if (animal_idx.find(animal) == animal_idx.end()) {
                animal_idx[animal] = animal_order.size();
                animal_order.push_back(animal);
            }
            
            count[loc][animal] += num;
        }

        for (size_t i = 0; i < loc_order.size(); ++i) {
            const std::string& loc = loc_order[i];
            std::cout << loc << " : ";
            bool first = true;
            for (size_t j = 0; j < animal_order.size(); ++j) {
                const std::string& animal = animal_order[j];
                auto it = count.find(loc);
                if (it != count.end()) {
                    auto it2 = it->second.find(animal);
                    if (it2 != it->second.end()) {
                        if (!first) {
                            std::cout << ", ";
                        }
                        first = false;
                        std::cout << animal << " " << it2->second;
                    }
                }
            }
            std::cout << "\n";
        }
    }
    return 0;
}
