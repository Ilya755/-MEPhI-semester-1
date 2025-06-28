#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <cassert>

std::vector<std::unique_ptr<std::string>> Duplicate(std::vector<std::shared_ptr<std::string>> in) {
    std::vector<std::unique_ptr<std::string>> out;
    for (size_t i = 0; i < in.size(); ++i) {
        out.push_back(std::unique_ptr<std::string>(std::make_unique<std::string>(*in[i])));
    }
    return out;
}

std::vector<std::shared_ptr<std::string>> DeDuplicate(std::vector<std::unique_ptr<std::string>>& in) {
    std::vector<std::shared_ptr<std::string>> out;
    std::map<std::string, std::shared_ptr<std::string>> mp;
    for (size_t i = 0; i < in.size(); ++i) {
        mp[*in[i]] = std::make_shared<std::string>(*in[i]);
    }
    for (size_t i = 0; i < in.size(); ++i) {
        out.push_back(mp[*in[i]]);
    }
    return out;
}