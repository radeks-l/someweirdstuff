/*
 * permutations.hpp
 *
 *  Created on: 31 sie 2016
 *      Author: Radek
 */

#ifndef PERMUTATIONS_HPP_
#define PERMUTATIONS_HPP_

#include <cstdint>
#include <vector>
#include <tuple>
#include <iostream>

typedef std::tuple<std::uint32_t, int> ValueDistance;
typedef std::vector<ValueDistance> PermutationsResult;

class PermutationsGenerator {
public:
    PermutationsGenerator(int p_numBits);
    PermutationsResult operator()(std::uint32_t p_value);
private:
    int mNumOfBits;
    std::uint32_t mEndMaskOneBit;
    std::uint32_t mEndMaskTwoBits;
};

std::ostream &operator<<(std::ostream &stream, const ValueDistance &toPrint);

void PermutationsTest();


#endif /* PERMUTATIONS_HPP_ */
