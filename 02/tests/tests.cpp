#include <gtest/gtest.h>
#include "decimal.hpp"
#include "exception.hpp"

using namespace decimal;

class DecimalTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Тесты конструкторов
TEST_F(DecimalTest, DefaultConstructor) {
    Decimal d;
    EXPECT_EQ(d.ShowNumber(), "0");
}

TEST_F(DecimalTest, SizeValueConstructor) {
    Decimal d(3, 5);
    EXPECT_EQ(d.ShowNumber(), "555");
}

TEST_F(DecimalTest, InitializerListConstructor) {
    Decimal d{1, 2, 3};
    EXPECT_EQ(d.ShowNumber(), "123");
    
    Decimal d2{0, 0, 1, 2, 3};
    EXPECT_EQ(d2.ShowNumber(), "123"); // ведущие нули должны удаляться
}

TEST_F(DecimalTest, StringConstructor) {
    Decimal d("12345");
    EXPECT_EQ(d.ShowNumber(), "12345");
    
    Decimal d2("000123");
    EXPECT_EQ(d2.ShowNumber(), "123"); // ведущие нули должны удаляться
}

TEST_F(DecimalTest, StringConstructorInvalidInput) {
    EXPECT_THROW(Decimal d("12a45"), exception::NaNException);
    EXPECT_THROW(Decimal d("12.45"), exception::NaNException);
}

TEST_F(DecimalTest, CopyConstructor) {
    Decimal d1("12345");
    Decimal d2(d1);
    EXPECT_EQ(d2.ShowNumber(), "12345");
}

TEST_F(DecimalTest, MoveConstructor) {
    Decimal d1("12345");
    Decimal d2(std::move(d1));
    EXPECT_EQ(d2.ShowNumber(), "12345");
}

// Тесты сравнения
TEST_F(DecimalTest, ComparisonOperators) {
    Decimal d1("123");
    Decimal d2("456");
    Decimal d3("123");
    Decimal d4("1234");
    Decimal d5("12");
    
    EXPECT_TRUE(d1.LessThen(d2));
    EXPECT_FALSE(d2.LessThen(d1));
    EXPECT_TRUE(d1.Equal(d3));
    EXPECT_FALSE(d1.Equal(d2));
    EXPECT_TRUE(d1.GreaterThen(d5));
    EXPECT_FALSE(d5.GreaterThen(d1));
    
    // Тесты с числами разной длины
    EXPECT_TRUE(d1.LessThen(d4));
    EXPECT_TRUE(d4.GreaterThen(d1));
}

// Тесты арифметических операций
TEST_F(DecimalTest, Addition) {
    // Базовое сложение
    Decimal d1("123");
    Decimal d2("456");
    Decimal result1 = Decimal::Add(d1, d2);
    EXPECT_EQ(result1.ShowNumber(), "579");
    
    // Сложение с переносом
    Decimal d3("999");
    Decimal d4("1");
    Decimal result2 = Decimal::Add(d3, d4);
    EXPECT_EQ(result2.ShowNumber(), "1000");
    
    // Сложение с нулем
    Decimal d5("0");
    Decimal result3 = Decimal::Add(d1, d5);
    EXPECT_EQ(result3.ShowNumber(), "123");
    
    // Большие числа
    Decimal d6("123456789");
    Decimal d7("987654321");
    Decimal result4 = Decimal::Add(d6, d7);
    EXPECT_EQ(result4.ShowNumber(), "1111111110");
}

TEST_F(DecimalTest, Subtraction) {
    Decimal d1("456");
    Decimal d2("123");
    Decimal result1 = Decimal::Sub(d1, d2);
    EXPECT_EQ(result1.ShowNumber(), "333");

    Decimal d3("1000");
    Decimal d4("1");
    Decimal result2 = Decimal::Sub(d3, d4);
    EXPECT_EQ(result2.ShowNumber(), "999");

    Decimal d5("123");
    Decimal result3 = Decimal::Sub(d5, d5);
    EXPECT_EQ(result3.ShowNumber(), "0");
        
}

TEST_F(DecimalTest, SubtractionNegativeResult) {
    Decimal d1("123");
    Decimal d2("456");
    
    EXPECT_THROW(Decimal::Sub(d1, d2), exception::NegativeException);
}

TEST_F(DecimalTest, Multiplication) {
    // Базовое умножение
    Decimal d1("12");
    Decimal d2("34");
    Decimal result1 = Decimal::Prod(d1, d2);
    EXPECT_EQ(result1.ShowNumber(), "408");
    
    // Умножение на ноль
    Decimal d3("0");
    Decimal result2 = Decimal::Prod(d1, d3);
    EXPECT_EQ(result2.ShowNumber(), "0");
    
    // Умножение на единицу
    Decimal d4("1");
    Decimal result3 = Decimal::Prod(d1, d4);
    EXPECT_EQ(result3.ShowNumber(), "12");
    
    // Большие числа
    Decimal d5("12345");
    Decimal d6("67890");
    Decimal result4 = Decimal::Prod(d5, d6);
    EXPECT_EQ(result4.ShowNumber(), "838102050");
    
    // Умножение с переносами
    Decimal d7("99");
    Decimal d8("99");
    Decimal result5 = Decimal::Prod(d7, d8);
    EXPECT_EQ(result5.ShowNumber(), "9801");
}

// Тесты пограничных случаев
TEST_F(DecimalTest, EdgeCases) {
    // Нули
    Decimal zero1("0");
    Decimal zero2("0000");
    EXPECT_EQ(zero1.ShowNumber(), "0");
    EXPECT_EQ(zero2.ShowNumber(), "0");
    EXPECT_TRUE(zero1.Equal(zero2));
    
    // Очень большие числа
    Decimal large("123456789012345678901234567890");
    EXPECT_EQ(large.ShowNumber(), "123456789012345678901234567890");
    
    // Числа с многими ведущими нулями
    Decimal withLeadingZeros("0000000123");
    EXPECT_EQ(withLeadingZeros.ShowNumber(), "123");
}

// Тесты метода Copy
TEST_F(DecimalTest, CopyMethod) {
    Decimal d1("12345");
    Decimal d2("67890");
    
    d1.Copy(d2);
    EXPECT_EQ(d1.ShowNumber(), "67890");
    EXPECT_TRUE(d1.Equal(d2));
}

// Тесты метода ShowNumber
TEST_F(DecimalTest, ShowNumberMethod) {
    Decimal d1("12345");
    Decimal d2(0, 0); // пустой
    Decimal d3{1, 2, 3};
    
    EXPECT_EQ(d1.ShowNumber(), "12345");
    EXPECT_EQ(d2.ShowNumber(), "0");
    EXPECT_EQ(d3.ShowNumber(), "123");
}

// Комплексные тесты
TEST_F(DecimalTest, ComplexOperations) {
    // (a + b) - c = d
    Decimal a("1000");
    Decimal b("500");
    Decimal c("300");
    
    Decimal sum = Decimal::Add(a, b);
    Decimal result = Decimal::Sub(sum, c);
    EXPECT_EQ(result.ShowNumber(), "1200");
    
    // a * b + c
    Decimal x("10");
    Decimal y("20");
    Decimal z("5");
    
    Decimal product = Decimal::Prod(x, y);
    Decimal final_result = Decimal::Add(product, z);
    EXPECT_EQ(final_result.ShowNumber(), "205");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}