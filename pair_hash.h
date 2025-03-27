// pair_hash.h
#ifndef PAIR_HASH_H
#define PAIR_HASH_H

#include <functional>
///
///@file pair_hash.h
///@brief Header file containing the declaration of a custom hash function
///

/// 
/// @tparam T1 variable type of the first element of the pair
/// @tparam T2 variable type of the second element of the pair
/// @param p the pair the hash function will be applied to
/// @return Custom hash for the given pair
///
/// @brief A simple hash function to be used for pairs
template <typename T1, typename T2>
struct pair_hash {
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

#endif
