#include <string>
#include <cstdint>
#include <stdexcept>

class BigInt {
public:
    BigInt() {}
    BigInt(uint64_t a);

    operator uint64_t() const;
    BigInt operator + (const BigInt &rhs);
    BigInt operator * (const BigInt &rhs);
    bool operator == (const BigInt &rhs) const;
    bool operator != (const BigInt &rhs) const;
    std::string toString() const;

    static BigInt fromString(const std::string &str);

private:
    enum { SIZE = 44000, INVALID };
    int _cnt = 1;
    uint8_t _number[SIZE] = {0};

    void clear();
    uint64_t pow10(int a) const;
    void cnt();
};

std::ostream &operator<<(std::ostream &os, const BigInt &value);
