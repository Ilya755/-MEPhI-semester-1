#include "task.h"

using namespace std;

void PopulateHashMap(
    std::unordered_map<SuperKey, std::string>& hashMap,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
) {
    for (const auto& element : toAdd) {
        hashMap[element.first] = element.second;
    }
}
