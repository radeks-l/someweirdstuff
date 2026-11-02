/*
 * permutations.cpp
 *
 *  Created on: 11.12.2016
 *      Author: radek
 */

#include "permutations.hpp"

PermutationsGenerator::PermutationsGenerator(int p_numBits):
    mNumOfBits(p_numBits) {
    mEndMaskOneBit = (0x01 << (mNumOfBits - 1));
    mEndMaskTwoBits = (0x03 << (mNumOfBits - 2));
}

PermutationsResult PermutationsGenerator::operator()(std::uint32_t p_value) {
    PermutationsResult result;
    std::uint32_t mask = 0x01;
    std::uint32_t currentValue = 0;
    while (mask <= mEndMaskOneBit) {
        currentValue = p_value ^ mask;
        result.emplace_back(currentValue, 1);
        mask <<= (1);
    }
    std::uint32_t lowerBitMask = 0x1;
    std::uint32_t greatherBitMask = lowerBitMask << 1;
    mask = greatherBitMask | lowerBitMask;
    while (mask <= mEndMaskTwoBits) {
        currentValue = p_value ^ mask;
        result.emplace_back(currentValue, 2);
        greatherBitMask <<= 1;
        if (greatherBitMask > mEndMaskTwoBits) {
            lowerBitMask <<= 1;
            greatherBitMask = lowerBitMask << 1;
        }
        mask = greatherBitMask | lowerBitMask;
    }
    return result;
}

std::ostream &operator<<(std::ostream &stream, const ValueDistance &toPrint) {
    stream << "(" << std::get<0>(toPrint) << ", " << std::get<1>(toPrint) << ")";
    return stream;
}

struct TestHelper {
    TestHelper() { totalTests = 0; failures = 0; }
    ~TestHelper() {
        std::cout << "TESTS: " << totalTests << ", ";
        std::cout << "FAILURES: " << failures << std::endl;
    }
    int totalTests;
    int failures;
};

#define TEST_RESULT(currentValue, expectedValue)             \
    do {                                                    \
        testHelper.totalTests++;                            \
        if (currentValue != expectedValue) {                \
            std::cout << "error: " << currentValue;            \
            std::cout << " != " << expectedValue;            \
            std::cout << std::endl;                            \
            testHelper.failures++;                            \
        }                                                    \
    } while(0)

void PermutationsTest() {
    {
        TestHelper testHelper;
        PermutationsGenerator perm(3);
        auto result = perm(7);
        std::cout << "res size: " << result.size() << std::endl;
        std::cout << "=======================================================" << std::endl;
        for (auto &it: result) {
            std::cout << it << std::endl;
        }
        std::cout << "=======================================================" << std::endl;
        TEST_RESULT(result[0], ValueDistance(6, 1));
        TEST_RESULT(result[1], ValueDistance(5, 1));
        TEST_RESULT(result[2], ValueDistance(3, 1));
        TEST_RESULT(result[3], ValueDistance(4, 2));
        TEST_RESULT(result[4], ValueDistance(2, 2));
        TEST_RESULT(result[5], ValueDistance(1, 2));
    }
    {
        TestHelper testHelper;
        PermutationsGenerator perm(4);
        auto result = perm(0);
        std::cout << "res size: " << result.size() << std::endl;
        std::cout << "=======================================================" << std::endl;
        for (auto &it: result) {
            std::cout << it << std::endl;
        }
        std::cout << "=======================================================" << std::endl;
        TEST_RESULT(result[0], ValueDistance(1, 1));
        TEST_RESULT(result[1], ValueDistance(2, 1));
        TEST_RESULT(result[2], ValueDistance(4, 1));
        TEST_RESULT(result[3], ValueDistance(8, 1));
        TEST_RESULT(result[4], ValueDistance(3, 2));
        TEST_RESULT(result[5], ValueDistance(5, 2));
        TEST_RESULT(result[6], ValueDistance(9, 2));
        TEST_RESULT(result[7], ValueDistance(6, 2));
        TEST_RESULT(result[8], ValueDistance(10, 2));
        TEST_RESULT(result[9], ValueDistance(12, 2));
    }
}
