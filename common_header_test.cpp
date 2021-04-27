#include "common_header.h"


#ifdef WANT_TESTS
#define RandomNumberTest(testName, from, to) namespace {                                            \
    TEST(Random_NumberTest, testName) {                                                             \
        const auto random_number = Random_Number(from, to);                                         \
                                                                                                    \
        EXPECT_LE(static_cast<std::remove_const_t<decltype(random_number)>>(from), random_number);  \
        EXPECT_GE(static_cast<std::remove_const_t<decltype(random_number)>>(to), random_number);    \
    }                                                                                               \
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


constexpr int signed_value = 5;
constexpr unsigned unsigned_value = 5;

static constexpr inline auto ZeroUnsignedFunction() {
    return unsigned_value;
}

SIMPLE_BENCHMARK0(ZeroUnsignedFunction);
SIMPLE_BENCHMARK(ZeroUnsignedFunction, Sample0);
THE_BENCHMARK(ZeroUnsignedFunction);

SIMPLE_TEST(ZeroUnsignedFunction, TestSignedConstant, 5);
SIMPLE_TEST(ZeroUnsignedFunction, TestUnsignedConstant, 5u);
SIMPLE_TEST(ZeroUnsignedFunction, TestSignedVariable, signed_value);
SIMPLE_TEST(ZeroUnsignedFunction, TestUnsignedVariable, unsigned_value);


template <typename T>
static constexpr inline auto TemplateFunction(T v) {
    return v;
}


constexpr auto SingleBuiltinArgumentFunction = TemplateFunction<int>;

THE_BENCHMARK(SingleBuiltinArgumentFunction, 5);
SIMPLE_BENCHMARK(SingleBuiltinArgumentFunction, Sample1, 5);
SIMPLE_BENCHMARK(SingleBuiltinArgumentFunction, Sample2, signed_value);

SIMPLE_TEST(SingleBuiltinArgumentFunction, TestConstant, 5, 5);
SIMPLE_TEST(SingleBuiltinArgumentFunction, TestSignedVariable, signed_value,
            signed_value);

MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SingleBuiltinArgumentFunction,
                   TestConstant, 5);
MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SingleBuiltinArgumentFunction,
                   TestSignedVariable, signed_value);


static constexpr inline auto TwoArgumentsFunction(const int, const int) {
    return signed_value;
}

SIMPLE_BENCHMARK(TwoArgumentsFunction, Sample1, 5, 5);
SIMPLE_BENCHMARK(TwoArgumentsFunction, Sample2, signed_value, signed_value);

SIMPLE_TEST(TwoArgumentsFunction, TestConstant, 5, 5, 5);
SIMPLE_TEST(TwoArgumentsFunction, TestSignedVariable, signed_value,
            signed_value, signed_value);

MUTUAL_SIMPLE_TEST(TwoArgumentsFunction, TwoArgumentsFunction, TestConstant, 5, 5);
MUTUAL_SIMPLE_TEST(TwoArgumentsFunction, TwoArgumentsFunction, TestSignedVariable,
                   signed_value, signed_value);


static constexpr inline auto ThreeArgumentsFunction(const int, const int, const int) {
    return signed_value;
}

SIMPLE_BENCHMARK(ThreeArgumentsFunction, Sample1, 5, 5, 5);
SIMPLE_BENCHMARK(ThreeArgumentsFunction, Sample2, signed_value,
                 signed_value, signed_value);

SIMPLE_TEST(ThreeArgumentsFunction, TestConstant, 5, 5, 5, 5);
SIMPLE_TEST(ThreeArgumentsFunction, TestSignedVariable, signed_value,
            signed_value, signed_value, signed_value);

MUTUAL_SIMPLE_TEST(ThreeArgumentsFunction, ThreeArgumentsFunction, TestConstant,
                   5, 5, 5);
MUTUAL_SIMPLE_TEST(ThreeArgumentsFunction, ThreeArgumentsFunction, TestSignedVariable,
                   signed_value, signed_value, signed_value);


static constexpr inline unsigned SignedUnsignedFunction(const int v) {
    return v;
}

SIMPLE_BENCHMARK(SignedUnsignedFunction, Sample1, 5);
SIMPLE_BENCHMARK(SignedUnsignedFunction, Sample2, signed_value);

SIMPLE_TEST(SignedUnsignedFunction, TestSignedConstant, 5, 5);
SIMPLE_TEST(SignedUnsignedFunction, TestUnsignedConstant, 5u, 5);
SIMPLE_TEST(SignedUnsignedFunction, TestSignedVariable, signed_value, signed_value);
SIMPLE_TEST(SignedUnsignedFunction, TestUnsignedVariable, unsigned_value,
            unsigned_value);

MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SignedUnsignedFunction,
                   TestConstant, 5);
MUTUAL_SIMPLE_TEST(SingleBuiltinArgumentFunction, SignedUnsignedFunction,
                   TestSignedVariable, signed_value);
MUTUAL_SIMPLE_TEST(SignedUnsignedFunction, SingleBuiltinArgumentFunction,
                   TestConstant, 5);
MUTUAL_SIMPLE_TEST(SignedUnsignedFunction, SingleBuiltinArgumentFunction,
                   TestSignedVariable, signed_value);

MUTUAL_RANDOM_TEST(SignedUnsignedFunction, SingleBuiltinArgumentFunction, 1, 5);


constexpr auto DoubleFunction = TemplateFunction<double>;

constexpr double double_value = 5.0;

SIMPLE_DOUBLE_TEST(DoubleFunction, TestConstant, 5.0, 5.0);
SIMPLE_DOUBLE_TEST(DoubleFunction, TestSignedVariable, double_value, double_value);


using ValueType = int;
constexpr std::initializer_list<ValueType> initializer_list_single_value = {signed_value};
const std::vector<ValueType> vector_single_value = initializer_list_single_value;
const std::list<ValueType> list_single_value = initializer_list_single_value;

constexpr std::initializer_list<ValueType> initializer_list_multi_values = {signed_value, signed_value, signed_value, signed_value};
const std::vector<ValueType> vector_multi_values = initializer_list_multi_values;
const std::list<ValueType> list_multi_values = initializer_list_multi_values;

static inline auto ZeroVectorSingleFunction() {
    return vector_single_value;
}

static inline auto ZeroVectorMultiFunction() {
    return vector_multi_values;
}

SIMPLE_BENCHMARK(ZeroVectorSingleFunction, void);
SIMPLE_BENCHMARK(ZeroVectorMultiFunction, void);

SIMPLE_TEST0(ZeroVectorSingleFunction, TestConstantReturn, {5});
SIMPLE_TEST0(ZeroVectorSingleFunction, TestInitializerReturnSingle,
             initializer_list_single_value);
SIMPLE_TEST0(ZeroVectorSingleFunction, TestVariableSingle, vector_single_value);

SIMPLE_TEST0(ZeroVectorMultiFunction, TestConstantReturn, {5, 5, 5, 5});
SIMPLE_TEST0(ZeroVectorMultiFunction, TestInitializerReturnSingle,
             initializer_list_multi_values);
SIMPLE_TEST0(ZeroVectorMultiFunction, TestVariableSingle, vector_multi_values);


constexpr auto VectorFunction = TemplateFunction<std::vector<ValueType>>;

SIMPLE_BENCHMARK(VectorFunction, Sample1, {5});
SIMPLE_BENCHMARK(VectorFunction, Sample2, {5, 5, 5});
SIMPLE_BENCHMARK(VectorFunction, Sample3, initializer_list_single_value);
SIMPLE_BENCHMARK(VectorFunction, Sample4, initializer_list_multi_values);
SIMPLE_BENCHMARK(VectorFunction, Sample5, vector_single_value);
SIMPLE_BENCHMARK(VectorFunction, Sample6, vector_multi_values);

//SIMPLE_TEST(VectorFunction, TestConstant, 5, 5);
SIMPLE_TEST(VectorFunction, TestConstantReturnSingle, {5}, vector_single_value);
//SIMPLE_TEST(VectorFunction, TestConstantReturnMulti_Short, ({5, 5, 5, 5}), vector_multi_values);
SIMPLE_TEST(VectorFunction, TestConstantReturnMulti_Long, STRIP_PARENTHESES({5, 5, 5, 5}),
            vector_multi_values);
SIMPLE_TEST(VectorFunction, TestInitializerReturnSingle, initializer_list_single_value,
            initializer_list_single_value);
SIMPLE_TEST(VectorFunction, TestInitializerReturnMulti, initializer_list_multi_values,
            initializer_list_multi_values);
SIMPLE_TEST(VectorFunction, TestVariableSingle, vector_single_value,
            vector_single_value);
SIMPLE_TEST(VectorFunction, TestVariableMulti, vector_multi_values,
            vector_multi_values);

MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestInitializerReturnSingle,
                   initializer_list_single_value);
MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestInitializerReturnMulti,
                   initializer_list_multi_values);
MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestVariableSingle,
                   vector_single_value);
MUTUAL_SIMPLE_TEST(VectorFunction, VectorFunction, TestVariableMulti,
                   vector_multi_values);


constexpr auto ListFunction = TemplateFunction<std::list<ValueType>>;

SIMPLE_BENCHMARK(ListFunction, Sample1, {5});
SIMPLE_BENCHMARK(ListFunction, Sample2, {5, 5, 5});
SIMPLE_BENCHMARK(ListFunction, Sample3, initializer_list_single_value);
SIMPLE_BENCHMARK(ListFunction, Sample4, initializer_list_multi_values);
SIMPLE_BENCHMARK(ListFunction, Sample5, list_single_value);
SIMPLE_BENCHMARK(ListFunction, Sample6, list_multi_values);

//SIMPLE_TEST(ListFunction, TestConstant, 5, 5);
SIMPLE_TEST(ListFunction, TestConstantReturn, {5}, list_single_value);
//SIMPLE_TEST(ListFunction, TestConstantReturnMulti_Short, ({5, 5, 5, 5}), list_multi_values);
SIMPLE_TEST(ListFunction, TestConstantReturnMulti_Long, STRIP_PARENTHESES({5, 5, 5, 5}),
            list_multi_values);
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


static inline auto
ConstVectorToList(const std::vector<ValueType> &array) {
    return ContainerCast<std::list<ValueType>>(array);
}

static inline auto
NonconstVectorToList(std::vector<ValueType> array) {
    return ContainerCast<std::list<ValueType>>(std::move(array));
}

SIMPLE_TEST(ConstVectorToList, TestInitializerReturnSingle,
            initializer_list_single_value, initializer_list_single_value);
SIMPLE_TEST(ConstVectorToList, TestInitializerReturnMulti,
            initializer_list_multi_values, initializer_list_multi_values);

SIMPLE_TEST(NonconstVectorToList, TestInitializerReturnSingle,
            initializer_list_single_value, initializer_list_single_value);
SIMPLE_TEST(NonconstVectorToList, TestInitializerReturnMulti,
            initializer_list_multi_values, initializer_list_multi_values);

MUTUAL_SIMPLE_TEST(ListFunction, ConstVectorToList, TestInitializerReturnSingle,
                   initializer_list_single_value);
MUTUAL_SIMPLE_TEST(ListFunction, ConstVectorToList, TestInitializerReturnMulti,
                   initializer_list_multi_values);

MUTUAL_SIMPLE_TEST(ListFunction, NonconstVectorToList, TestInitializerReturnSingle,
                   initializer_list_single_value);
MUTUAL_SIMPLE_TEST(ListFunction, NonconstVectorToList, TestInitializerReturnMulti,
                   initializer_list_multi_values);
