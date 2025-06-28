#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

template <typename K, typename V>
class LruCache {
private:
    using data_list = std::list<std::pair<K, V>>;

    data_list data_;
    std::unordered_map<K, typename data_list::iterator> mp_;
    size_t max_size_;
    size_t cur_size_;

public:
    LruCache(size_t max_size) 
        : max_size_(max_size)
        , cur_size_(0)
        {}

    void Put(const K& key, const V& value) {
        if (mp_.find(key) != mp_.end()) {
            cur_size_--;
            data_.erase(mp_[key]);
        }
        else if (cur_size_ == max_size_) {
            cur_size_--;
            mp_.erase((*data_.begin()).first);
            data_.erase(data_.begin());
        }
        data_.push_back(std::make_pair(key, value));
        mp_[key] = --data_.end();
        cur_size_++;
    }
    bool Get(const K& key, V* value) {
        if (mp_.find(key) == mp_.end()) {
            return false;
        }
        else {
            *value = (*mp_[key]).second;        
            data_.erase(mp_[key]);
            data_.push_back(std::make_pair(key, *value));
            mp_[key] = --data_.end();
            return true;
        }
    }
};
