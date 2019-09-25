#include "common_header.h"


#ifdef WANT_TESTS
#define RandomNumberTest(testName, from, to) namespace {                        \
    TEST(Random_NumberTest, testName) {                                         \
        const auto random_number = Random_Number(from, to);                     \
                                                                                \
        EXPECT_LE(static_cast<decltype(random_number)>(from), random_number);   \
        EXPECT_GE(static_cast<decltype(random_number)>(to), random_number);     \
    }                                                                           \
}

RandomNumberTest(TestSameType, 0, 20);
RandomNumberTest(TestDiffType, 0, 20u);


TEST(BitsNumberTest, TestSanity) {
    EXPECT_EQ(16u, BitsNumber<int16_t>);
    EXPECT_EQ(16u, BitsNumber<uint16_t>);
    EXPECT_EQ(32u, BitsNumber<int32_t>);
    EXPECT_EQ(32u, BitsNumber<uint32_t>);
    EXPECT_EQ(64u, BitsNumber<int64_t>);
    EXPECT_EQ(64u, BitsNumber<uint64_t>);
}
#endif


const int signed_value = 5;
const unsigned unsigned_value = 5u;


static unsigned ZeroArgumentFunction() {
    return unsigned_value;
}

SIMPLE_BENCHMARK(ZeroArgumentFunction);

SIMPLE_TEST(ZeroArgumentFunction, TestSignedConstant, 5);
SIMPLE_TEST(ZeroArgumentFunction, TestUnsignedConstant, 5u);
SIMPLE_TEST(ZeroArgumentFunction, TestSignedVariable, signed_value);
SIMPLE_TEST(ZeroArgumentFunction, TestUnsignedVariable, unsigned_value);


template <typename T>
static auto TemplateFunction(T v) {
    return v;
}


const auto SingleBuiltinArgumentFunction = TemplateFunction<int>;

SIMPLE_BENCHMARK(SingleBuiltinArgumentFunction, 5);
SIMPLE_BENCHMARK(SingleBuiltinArgumentFunction, signed_value);

SIMPLE_TEST(SingleBuiltinArgumentFunction, TestConstant, 5, 5);
SIMPLE_TEST(SingleBuiltinArgumentFunction, TestSignedVariable, signed_value, signed_value);

MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SingleBuiltinArgumentFunction, TestConstant, 5);
MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SingleBuiltinArgumentFunction, TestSignedVariable,
                   signed_value);


static auto TwoArgumentsFunction(const int, const int) {
    return signed_value;
}

SIMPLE_BENCHMARK(TwoArgumentsFunction, 5, 5);
SIMPLE_BENCHMARK(TwoArgumentsFunction, signed_value, signed_value);

SIMPLE_TEST(TwoArgumentsFunction, TestConstant, 5, 5, 5);
SIMPLE_TEST(TwoArgumentsFunction, TestSignedVariable, signed_value, signed_value, signed_value);

MUTUAL_SIMPLE_TEST(TwoArgumentsFunction, TwoArgumentsFunction, TestConstant, 5, 5);
MUTUAL_SIMPLE_TEST(TwoArgumentsFunction, TwoArgumentsFunction, TestSignedVariable, signed_value,
                   signed_value);


static auto ThreeArgumentsFunction(const int, const int, const int) {
    return signed_value;
}

SIMPLE_BENCHMARK(ThreeArgumentsFunction, 5, 5, 5);
SIMPLE_BENCHMARK(ThreeArgumentsFunction, signed_value, signed_value, signed_value);

SIMPLE_TEST(ThreeArgumentsFunction, TestConstant, 5, 5, 5, 5);
SIMPLE_TEST(ThreeArgumentsFunction, TestSignedVariable, signed_value, signed_value, signed_value,
            signed_value);

MUTUAL_SIMPLE_TEST(ThreeArgumentsFunction, ThreeArgumentsFunction, TestConstant, 5, 5, 5);
MUTUAL_SIMPLE_TEST(ThreeArgumentsFunction, ThreeArgumentsFunction, TestSignedVariable, signed_value,
                   signed_value, signed_value);


static unsigned SignedUnsignedFunction(const int v) {
    return v;
}

SIMPLE_BENCHMARK(SignedUnsignedFunction, 5);
SIMPLE_BENCHMARK(SignedUnsignedFunction, signed_value);

SIMPLE_TEST(SignedUnsignedFunction, TestSignedConstant, 5, 5);
SIMPLE_TEST(SignedUnsignedFunction, TestUnsignedConstant, 5u, 5);
SIMPLE_TEST(SignedUnsignedFunction, TestSignedVariable, signed_value, signed_value);
SIMPLE_TEST(SignedUnsignedFunction, TestUnsignedVariable, unsigned_value, unsigned_value);

MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SignedUnsignedFunction, TestConstant, 5);
MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SignedUnsignedFunction, TestSignedVariable,
                   signed_value);
MUTUAL_SIMPLE_TEST(SignedUnsignedFunction, SingleBuiltinArgumentFunction, TestConstant, 5);
MUTUAL_SIMPLE_TEST(SignedUnsignedFunction, SingleBuiltinArgumentFunction, TestSignedVariable,
                   signed_value);


using ValueType = int;
const std::initializer_list<ValueType> initializer_list_single_value = {signed_value};
const std::vector<ValueType> vector_single_value = initializer_list_single_value;
const std::list<ValueType> list_single_value = initializer_list_single_value;

const std::initializer_list<ValueType> initializer_list_multi_values = {signed_value, signed_value, signed_value, signed_value};
const std::vector<ValueType> vector_multi_values = initializer_list_multi_values;
const std::list<ValueType> list_multi_values = initializer_list_multi_values;


const auto VectorFunction = TemplateFunction<std::vector<int>>;

SIMPLE_BENCHMARK(VectorFunction, {5});
SIMPLE_BENCHMARK(VectorFunction, {5, 5, 5});
SIMPLE_BENCHMARK(VectorFunction, initializer_list_single_value);
SIMPLE_BENCHMARK(VectorFunction, initializer_list_multi_values);
SIMPLE_BENCHMARK(VectorFunction, vector_single_value);
SIMPLE_BENCHMARK(VectorFunction, vector_multi_values);

//SIMPLE_TEST(VectorFunction, TestConstant, 5, 5);
//SIMPLE_TEST(VectorFunction, TestConstantReturn, {5}, vector_single_value);
SIMPLE_TEST(VectorFunction, TestInitializerReturnSingle, initializer_list_single_value,
            initializer_list_single_value);
SIMPLE_TEST(VectorFunction, TestInitializerReturnMulti, initializer_list_multi_values,
            initializer_list_multi_values);
SIMPLE_TEST(VectorFunction, TestVariableSingle, vector_single_value, vector_single_value);
SIMPLE_TEST(VectorFunction, TestVariableMulti, vector_multi_values, vector_multi_values);

MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestInitializerReturnSingle,
                   initializer_list_single_value);
MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestInitializerReturnMulti,
                   initializer_list_multi_values);
MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestVariableSingle, vector_single_value);
MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestVariableMulti, vector_multi_values);


const auto ListFunction = TemplateFunction<std::list<int>>;

SIMPLE_BENCHMARK(ListFunction, {5});
SIMPLE_BENCHMARK(ListFunction, {5, 5, 5});
SIMPLE_BENCHMARK(ListFunction, initializer_list_single_value);
SIMPLE_BENCHMARK(ListFunction, initializer_list_multi_values);
SIMPLE_BENCHMARK(ListFunction, list_single_value);
SIMPLE_BENCHMARK(ListFunction, list_multi_values);

//SIMPLE_TEST(ListFunction, TestConstant, 5, 5);
//SIMPLE_TEST(ListFunction, TestConstantReturn, {5}, list_single_value);
SIMPLE_TEST(ListFunction, TestInitializerReturnSingle, initializer_list_single_value,
            initializer_list_single_value);
SIMPLE_TEST(ListFunction, TestInitializerReturnMulti, initializer_list_multi_values,
            initializer_list_multi_values);
SIMPLE_TEST(ListFunction, TestVariableSingle, list_single_value, list_single_value);
SIMPLE_TEST(ListFunction, TestVariableMulti, list_multi_values, list_multi_values);

MUTUAL_SIMPLE_TEST(ListFunction, ListFunction, TestInitializerReturnSingle,
                   initializer_list_single_value);
MUTUAL_SIMPLE_TEST(ListFunction, ListFunction, TestInitializerReturnMulti,
                   initializer_list_multi_values);
MUTUAL_SIMPLE_TEST(ListFunction, ListFunction, TestVariableSingle, list_single_value);
MUTUAL_SIMPLE_TEST(ListFunction, ListFunction, TestVariableMulti, list_multi_values);
