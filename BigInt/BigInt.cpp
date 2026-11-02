#include "BigInt.hpp"

BigInt::BigInt(uint64_t a) {
    if (a == 0) {
        return; 
    }
    int i = 0;
    while (a != 0 && i < SIZE) {
        _number[i] = a % 10;
        i++;
        a = a / 10;
    }
    _cnt = i;
}

BigInt::operator uint64_t() const {
    uint64_t retval = 0;
    // TODO: issue with 'overflow'
    // TODO: optimize
    for (int i = SIZE; i >= 0; --i) {
        if (_number[i] != 0)
            retval += _number[i] * pow10(i);
    }
    return retval;
}

BigInt BigInt::operator + (const BigInt &rhs) {
    BigInt retval(0);
    auto maxIter = std::max(_cnt, rhs._cnt);
    for (int it = 0; it < maxIter; ++it) {
        const auto sum = _number[it] + rhs._number[it] + retval._number[it];
        retval._number[it] = sum % 10;
        if ( (sum >= 10) && (it < (SIZE - 1)) ) {
            retval._number[it + 1] += 1;
        }
    }
    // get carry over from prev addition
    if (retval._number[maxIter] != 0) {
        maxIter++;
    }
    retval._cnt = maxIter;
    return retval;
}

BigInt BigInt::operator * (const BigInt &rhs) {
    // TODO: optimize
    BigInt retval(0);
    int thisCnt = this->_cnt;
    int rhsCnt = rhs._cnt;
    if (thisCnt == 0 || rhsCnt == 0)
        return retval;
    const u_int8_t *first, *second;
    int firstCnt, secondCnt;
    if (thisCnt < rhsCnt) {
        first = this->_number;
        second = rhs._number;
        firstCnt = thisCnt;
        secondCnt = rhsCnt;
    } else {
        first = rhs._number;
        second = this->_number;
        firstCnt = rhsCnt;
        secondCnt = thisCnt;
    }
    for (int i = 0; i < secondCnt; ++i) {
        for (int j = 0; j < firstCnt; ++j) {
            retval._number[j + i] += second[i] * first[j];
        }
    }
    int tmp;
    for (int i = 0; i < (SIZE - 1); ++i) {
        tmp = retval._number[i];
        retval._number[i] = tmp % 10;
        retval._number[i + 1] += tmp / 10;
    }
    retval.cnt();
    return retval;
}

bool BigInt::operator == (const BigInt &rhs) const {
    if (_cnt == rhs._cnt) {
        for (int i = 0; i < _cnt; ++i) {
            if (_number[i] != rhs._number[i])
                return false;
        }
        return true;
    }
    return false;
}

bool BigInt::operator != (const BigInt &rhs) const {
    return (false == operator==(rhs));
}

std::string BigInt::toString() const {
    int it = _cnt;
    std::string retval;
    retval.reserve(it);
    while (it > 0) {
        retval.push_back(_number[it-1] + '0');
        it--;
    }
    return retval;
}

BigInt BigInt::fromString(const std::string &str) {
    BigInt retval(0);

    int it = str.size();
    for (const auto s: str) {
        if (isdigit(s)) {
            retval._number[it - 1] = s - '0';
            it--;
        } else {
            throw std::range_error("Wrong string passed: " + str);
        }
    }

    retval.cnt();
    return retval;
}

void BigInt::clear() {
    _cnt = 0;
    for (auto &it: _number) {
        it = 0;
    }
}
uint64_t BigInt::pow10(int a) const {
    uint64_t r = 1;
    while (--a >= 0) r *= 10;
    return r;
}
void BigInt::cnt() {
    for (int it = SIZE - 1; it >= 0; --it) {
        if (_number[it] != 0) {
            _cnt = it + 1;
            break;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const BigInt &value) {
    os << value.toString();
    return os;
}