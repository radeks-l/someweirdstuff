#include "BigInt.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("BigInt init")
{
    BigInt a;
    CHECK_EQ(0, static_cast<int>(a));
}

TEST_CASE("InitWith10")
{
    const int VALUE = 10;
    BigInt a(VALUE);

    CHECK_EQ(VALUE, static_cast<int>(a));
}

TEST_CASE("InitWithFourBytesValue")
{
    const int VALUE = 0xFFAABBCC;
    BigInt a(VALUE);

    CHECK_EQ(VALUE, static_cast<int>(a));
}

TEST_CASE("ToStringEmpty")
{
    BigInt v;
    CHECK_EQ(std::string("0"), v.toString());
}
TEST_CASE("ToString")
{
    BigInt v(5);
    CHECK_EQ(std::string("5"), v.toString());
}
TEST_CASE("ToString_11")
{
    BigInt v(11);
    CHECK_EQ(std::string("11"), v.toString());
}

TEST_CASE("ToString9876543210")
{
    BigInt v(9876543210);
    CHECK_EQ(std::string("9876543210"), v.toString());
}

TEST_CASE("operator uint64_t")
{
    const int VALUE = 100201;
    BigInt a(VALUE);
    const uint64_t VALUE_2 = 900201;
    BigInt a_2(VALUE_2);

    CHECK_EQ(VALUE, static_cast<int>(a));
    CHECK_EQ(VALUE_2, static_cast<uint64_t>(a_2));
}

TEST_CASE("Sum2OneByteValues")
{
    const int VALUE_1 = 11;
    const int VALUE_2 = 12;
    const int VALUE = VALUE_1 + VALUE_2;
    BigInt v1(VALUE_1);
    BigInt v2(VALUE_2);
    BigInt v = v1 + v2;

    CHECK_EQ(VALUE, static_cast<int>(v));
    CHECK_EQ(std::string("23"), v.toString());
    CHECK_EQ(std::string("23"), BigInt(VALUE).toString());
}

TEST_CASE("Sum2WithCarry")
{
    const int VALUE_1 = 6823;
    const int VALUE_2 = 96899;
    const int VALUE = VALUE_1 + VALUE_2;
    BigInt v1(VALUE_1);
    BigInt v2(VALUE_2);
    BigInt v = v1 + v2;

    CHECK_EQ(uint64_t(VALUE), uint64_t(v));
    CHECK_EQ(std::string("103722"), v.toString());
    CHECK_EQ(std::string("103722"), BigInt(VALUE).toString());
    CHECK_EQ(v, BigInt(VALUE));
}

TEST_CASE("Multiply2With0")
{
    BigInt v1(0);
    BigInt v2(2);
    BigInt v = v1 * v2;

    CHECK_EQ(0, static_cast<int>(v));
}

TEST_CASE("Multiply999With999")
{
    BigInt v1(999);
    BigInt v2(999);
    BigInt v = v1 * v2;

    CHECK_EQ(998001, static_cast<uint64_t>(v));
    CHECK_EQ(BigInt::fromString("998001"), v);
}

TEST_CASE("Multiply98With76")
{
    BigInt v1(98);
    BigInt v2(76);
    BigInt v = v1 * v2;

    CHECK_EQ(7448, static_cast<int>(v));
}

TEST_CASE("MultiplayBigWithSmall")
{
    BigInt v1(uint64_t(0x980000000000));
    BigInt v2(uint64_t(0x76));

    BigInt v = v1 * v2;
    CHECK_EQ(19720840555790336, static_cast<uint64_t>(v));
}

// TEST_CASE("MultiplyLongTest")
// {
//     const uint64_t sqrtMaxUint64 = sqrt(UINT64_MAX);
//     for (uint64_t it = 0; it < sqrtMaxUint64; ++it) {
//         BigInt v1(it);
//         BigInt v2(it);
//         BigInt v = v1 * v2;

//         CAPTURE(it);
//         REQUIRE_EQ(it * it, static_cast<uint64_t>(v));
//     }
// }

TEST_CASE("BigInt::fromString(123)")
{
    BigInt v2 = BigInt::fromString("123");

    CHECK_EQ(123, static_cast<uint64_t>(v2));
}

TEST_CASE("MultiplyWithSum")
{
    BigInt v1(1);
    BigInt v2(2);
    BigInt v3(3);
    BigInt v = v3 + v1 * v2;

    CHECK_EQ(5, static_cast<int>(v));
}

TEST_CASE("CompareOperatorEq")
{
    BigInt v(9876543210);

    CHECK_EQ(v, v);
}

TEST_CASE("CompareOperatorNeq")
{
    BigInt v(9876543210);
    BigInt v1(876543210);

    CHECK_NE(v1, v);
}

TEST_CASE("AssignOperator")
{
    BigInt v;
    BigInt v1(876543210);
    v = v1;

    CHECK_EQ(v1, v);
}

TEST_CASE("SumBigWithSmall")
{
    BigInt v1(uint64_t(0xFFFFFFFFFFFFFFFF));
    BigInt v2(uint64_t(10));
    BigInt v = v1 + v2;

    CHECK_EQ(BigInt::fromString("18446744073709551625"), v);
}

TEST_CASE("MultiplyTwoBig")
{
    BigInt v1(uint64_t(0xFFFFFFFFFFFFFFFF));
    BigInt v2(uint64_t(0xFFFFFFFFFFFFFFFF));
    BigInt v = v1 * v2;

    CHECK_EQ(BigInt::fromString("340282366920938463426481119284349108225"), v);
}
