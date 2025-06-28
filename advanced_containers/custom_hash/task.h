#include <unordered_map>
#include <vector>
#include <string>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};

/*
 * Напишите хэш-функцию, реализовав специализацию шаблона std::hash для типа SuperKey
 * Напишите функцию PopulateHashMap, которая добавляет в hashMap пары ключ-значение из данного вектора toAdd
 */

void PopulateHashMap(
    std::unordered_map<SuperKey, std::string>& hashMap,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
);

namespace std {
    template <>
    struct hash<SuperKey> {
        std::size_t operator()(const SuperKey& key) const {
            std::size_t h1 = hash<std::string>{}(key.StrPart);
            std::size_t h2 = hash<int>{}(key.IntPart);
            std::size_t h3 = hash<float>{}(key.FloatPart);
            return h1 ^ h2 ^ h3;
        }
    };
}