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

TEST_CASE("Sum2OneByteValues")
{
    const int VALUE_1 = 0xB;
    const int VALUE_2 = 0xC;
    const int VALUE = VALUE_1 + VALUE_2;

    BigInt v1(VALUE_1);
    BigInt v2(VALUE_2);
    BigInt v = v1 + v2;
    CHECK_EQ(VALUE, static_cast<int>(v));
}

TEST_CASE("Sum2TwoByteValuesOverflow")
{
    const int VALUE_1 = 0xBF;
    const int VALUE_2 = 0xFC;
    const int VALUE = VALUE_1 + VALUE_2;

    BigInt v1(VALUE_1);
    BigInt v2(VALUE_2);
    BigInt v = v1 + v2;
    CHECK_EQ(VALUE, static_cast<int>(v));
}

TEST_CASE("Multiply2With0")
{
    BigInt v1(0);
    BigInt v2(2);
    BigInt v = v1 * v2;
    CHECK_EQ(0, static_cast<int>(v));
}

TEST_CASE("Multiply98With76")
{
    BigInt v1(98);
    BigInt v2(76);

    BigInt v = v1 * v2;
    CHECK_EQ(7448, static_cast<int>(v));
}

TEST_CASE("MultiplyBigWithSmall")
{
    BigInt v1(uint64_t(0x980000000000));
    BigInt v2(uint64_t(0x76));

    BigInt v = v1 * v2;
    CHECK_EQ(19720840555790336, static_cast<uint64_t>(v));
}

TEST_CASE("BigInt::fromString(123)")
{
    BigInt v2 = BigInt::fromString("123");

    CHECK_EQ(123, static_cast<uint64_t>(v2));
}

// TEST(BigIntTest, MultiplyWithSum)
// {
//     BigInt v1(1);
//     BigInt v2(1);
//     BigInt v3(3);

//     BigInt v = v3 + v1 * v2;
//     ASSERT_EQ(4, static_cast<int>(v));
// }

TEST_CASE("ToStringEmpty")
{
    BigInt v;
    CHECK_EQ(std::string("0"), v.toString());
}

TEST_CASE("ToString9876543210")
{
    BigInt v(9876543210);
    CHECK_EQ(std::string("9876543210"), v.toString());
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

TEST_CASE("IsValid")
{
    BigInt v;
    BigInt v1(876543210);

    CHECK(v1.isValid());
    CHECK_FALSE(v.isValid());
}

TEST_CASE("IsValidAfterOper")
{
    BigInt v2(2);
    BigInt v1(2);
    BigInt v = v1 + v2;
    BigInt vm = v1 * v2;
    CHECK(v.isValid());
    CHECK(vm.isValid());
}

TEST_CASE("SumBigWithSmall")
{
    BigInt v1(uint64_t(0xFFFFFFFFFFFFFFFF));
    BigInt v2(uint64_t(10));

    BigInt v = v1 + v2;
    CHECK_EQ(BigInt::fromString("18446744073709551625"), v);
}
