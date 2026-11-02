#include <cstdint>

struct compare_less {
    constexpr bool operator()(char lhs, char rhs) {
        return lhs < rhs;
    }
};

template<std::size_t len, typename Compare, std::size_t idx>
struct CompareHelper {
    static constexpr bool compare(const char (&str_lhs)[len], const char (&str_rhs)[len], Compare comp) {
        return comp(str_lhs[idx], str_rhs[idx]) ||
            (idx + 1 < len) &&
            CompareHelper<len, Compare, idx+1>::compare(str_lhs, str_rhs, comp);
    }
};

template<std::size_t len, typename Compare>
struct CompareHelper<len, Compare, len> {
    static constexpr bool compare(...) {
        return false;
    }
};

template<std::size_t n, typename Compare = compare_less>
constexpr bool compare(const char (&str_lhs)[n], const char (&str_rhs)[n]) {
    return CompareHelper<n, Compare, 0>::compare(str_lhs, str_rhs, Compare());
}

int main(void) {
    static_assert(compare("12345", "12346"), "Is NOK!");
    static_assert(!compare("12346", "12345"), "Is NOK!");
    return 0;
}
