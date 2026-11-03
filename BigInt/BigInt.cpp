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
    // TODO: issue with 'overflow'

    uint64_t retval = 0;
    uint64_t decimalMul = 1;
    for (int i = 0; i <= _cnt; ++i) {
        if (_number[i] != 0) {
            retval += _number[i] * decimalMul;
        }
        decimalMul *= 10;
    }
    return retval;
}

BigInt BigInt::operator + (const BigInt &rhs) {
    BigInt retval(0);
    const auto maxIter = std::max(_cnt, rhs._cnt);
    for (int it = 0; it < maxIter; ++it) {
        const auto sum = _number[it] + rhs._number[it] + retval._number[it];
        retval._number[it] = sum % 10;
        if ( (sum >= 10) && (it < (SIZE - 1)) ) {
            retval._number[it + 1] += 1;
        }
    }
    int cnt = maxIter;
    // get carry over from prev addition
    if (retval._number[cnt] != 0) {
        cnt++;
    }
    retval._cnt = cnt;
    return retval;
}

BigInt BigInt::operator * (const BigInt &rhs) {
    BigInt retval(0);
    int thisCnt = _cnt;
    int rhsCnt = rhs._cnt;
    if (thisCnt == 0 || rhsCnt == 0) {
        return retval;
    }
    const uint8_t *first, *second;
    int firstCnt, secondCnt;
    if (thisCnt < rhsCnt) {
        first = _number;
        second = rhs._number;
        firstCnt = thisCnt;
        secondCnt = rhsCnt;
    } else {
        first = rhs._number;
        second = _number;
        firstCnt = rhsCnt;
        secondCnt = thisCnt;
    }
    for (int i = 0; i < secondCnt; ++i) {
        for (int j = 0; j < firstCnt; ++j) {
            auto tmp = second[i] * first[j];
            tmp += retval._number[j + i];
            retval._number[j + i] = tmp % 10;
            retval._number[i + j + 1] += tmp / 10;
        }
    }
    int cnt = secondCnt + firstCnt - 1;
    if (retval._number[cnt] != 0) {
        cnt = cnt + 1;
    }
    retval._cnt = cnt;
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
    return !operator==(rhs);
}

std::string BigInt::toString() const {
    int it = _cnt;
    std::string retval;
    retval.reserve(it);
    while (it > 0) {
        retval.push_back(_number[it - 1] + '0');
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
    retval._cnt = str.size();
    return retval;
}

std::ostream &operator<<(std::ostream &os, const BigInt &value) {
    os << value.toString();
    return os;
}