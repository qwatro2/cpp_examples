#pragma once

#include <functional>
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0), n_buckets_(0) {
    }

    explicit UnorderedSet(size_t count) : n_elements_(0), n_buckets_(count), data_(count) {
    }

    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : n_elements_(0), n_buckets_(0) {
        for (auto it = first; it != last; ++it) {
            ++n_elements_;
            ++n_buckets_;
            data_.push_back(std::list<KeyT>());
        }

        for (auto it = first; it != last; ++it) {
            auto index = std::hash<KeyT>{}(*it) % n_buckets_;
            data_[index].push_back(*it);
        }
    }

    UnorderedSet(const UnorderedSet& other)
        : n_elements_(other.n_elements_), n_buckets_(other.n_buckets_), data_(other.data_) {
    }

    UnorderedSet(UnorderedSet&& other)
        : n_elements_(other.n_elements_), n_buckets_(other.n_buckets_), data_(std::move(other.data_)) {
        other.n_elements_ = 0;
        other.n_buckets_ = 0;
    }

    ~UnorderedSet() = default;

    UnorderedSet& operator=(const UnorderedSet& other) {
        if (this != &other) {
            UnorderedSet<KeyT>(other).Swap(*this);
        }

        return *this;
    }

    UnorderedSet& operator=(UnorderedSet&& other) noexcept {
        UnorderedSet<KeyT>(std::move(other)).Swap(*this);

        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        data_.clear();
        n_elements_ = 0;
        n_buckets_ = 0;
    }

    void Insert(const KeyT& key) {
        if (n_elements_ == n_buckets_) {
            Rehash(n_buckets_ == 0 ? 1 : n_buckets_ * 2);
        }

        ++n_elements_;
        auto index = std::hash<KeyT>{}(key) % n_buckets_;
        data_[index].push_back(key);
    }

    void Insert(KeyT&& key) {
        if (n_elements_ == n_buckets_) {
            Rehash(n_buckets_ == 0 ? 1 : n_buckets_ * 2);
        }

        ++n_elements_;
        auto index = std::hash<KeyT>{}(key) % n_buckets_;
        data_[index].push_back(std::move(key));
    }

    void Erase(const KeyT& key) {
        auto index = std::hash<KeyT>{}(key) % n_buckets_;

        for (auto it = data_[index].begin(); it != data_[index].end(); ++it) {
            if (*it == key) {
                data_[index].erase(it);
                break;
            }
        }

        --n_elements_;
    }

    bool Find(const KeyT& key) const {
        if (n_buckets_ == 0) {
            return static_cast<bool>(n_buckets_);
        }

        auto index = std::hash<KeyT>{}(key) % n_buckets_;

        if (data_[index].empty()) {
            return false;
        }

        for (auto it = data_[index].begin(); it != data_[index].end(); ++it) {
            if (key == *it) {
                return true;
            }
        }

        return false;
    }

    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count != n_buckets_ && new_bucket_count >= n_elements_) {
            std::vector<std::list<KeyT>> new_table(new_bucket_count);

            for (auto i = 0; i < n_buckets_; ++i) {
                if (!data_[i].empty()) {
                    while (true) {
                        auto current = data_[i].begin();
                        auto index = std::hash<KeyT>{}(*current) % new_bucket_count;
                        auto next = current;
                        ++next;
                        new_table[index].splice(new_table[index].end(), data_[i], current, next);
                        if (next == data_[i].end()) {
                            break;
                        }
                    }
                }
            }

            data_ = std::move(new_table);
            n_buckets_ = new_bucket_count;
        }
    }

    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count > n_buckets_) {
            std::vector<std::list<KeyT>> new_table(new_bucket_count);

            for (auto i = 0; i < n_buckets_; ++i) {
                if (!data_[i].empty()) {
                    while (true) {
                        auto current = data_[i].begin();
                        auto index = std::hash<KeyT>{}(*current) % new_bucket_count;
                        auto next = current;
                        ++next;
                        new_table[index].splice(new_table[index].end(), data_[i], current, next);
                        if (next == data_[i].end()) {
                            break;
                        }
                    }
                }
            }

            data_ = std::move(new_table);
            n_buckets_ = new_bucket_count;
        }
    }

    size_t BucketCount() const {
        return n_buckets_;
    }

    size_t BucketSize(size_t id) const {
        return id >= n_buckets_ ? 0 : data_[id].size();
    }

    size_t Bucket(const KeyT& key) const {
        return std::hash<KeyT>{}(key) % n_buckets_;
    }

    double LoadFactor() const {
        return n_buckets_ == 0 ? 0 : static_cast<double>(n_elements_) / n_buckets_;
    }

private:
    void Swap(UnorderedSet<KeyT>& other) {
        std::swap(data_, other.data_);
        std::swap(n_buckets_, other.n_buckets_);
        std::swap(n_elements_, other.n_elements_);
    }

    size_t n_elements_;
    size_t n_buckets_;
    std::vector<std::list<KeyT>> data_;
};
