#include <gtest/gtest.h>
#include "diamond.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"
#include "vector.hpp"
#include "exception.hpp"

using namespace figure;
using namespace vector;

class DiamondTest : public ::testing::Test {
protected:
    void SetUp() override {
        default_diamond = std::make_unique<Diamond<double>>();
    }
    
    std::unique_ptr<Diamond<double>> default_diamond;
};

class PentagonTest : public ::testing::Test {
protected:
    void SetUp() override {
        default_pentagon = std::make_unique<Pentagon<double>>();
    }
    
    std::unique_ptr<Pentagon<double>> default_pentagon;
};

class HexagonTest : public ::testing::Test {
protected:
    void SetUp() override {
        default_hexagon = std::make_unique<Hexagon<double>>();
    }
    
    std::unique_ptr<Hexagon<double>> default_hexagon;
};

class VectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        int_vector.PushBack(1);
        int_vector.PushBack(2);
        int_vector.PushBack(3);
    }
    
    Vector<int> int_vector;
    Vector<std::shared_ptr<Figure<double>>> figure_vector;
};

TEST_F(DiamondTest, DefaultConstructor) {
    EXPECT_NO_THROW({
        Diamond<double> diamond;
    });
}

TEST_F(DiamondTest, DefaultDiamondCenter) {
    auto center = default_diamond->Center();
    EXPECT_NEAR(center.x, 0.0, EPS);
    EXPECT_NEAR(center.y, 0.0, EPS);
}

TEST_F(DiamondTest, DefaultDiamondArea) {
    double area = default_diamond->Area();
    EXPECT_NEAR(area, 2.0, EPS);
    EXPECT_GT(area, 0.0);
}

TEST_F(DiamondTest, DiamondDoubleConversion) {
    double area = static_cast<double>(*default_diamond);
    EXPECT_NEAR(area, 2.0, EPS);
}

TEST_F(DiamondTest, DiamondCopyConstructor) {
    Diamond<double> copy(*default_diamond);
    EXPECT_TRUE(*default_diamond == copy);
}

TEST_F(DiamondTest, DiamondAssignmentOperator) {
    Diamond<double> diamond;
    diamond = *default_diamond;
    EXPECT_TRUE(*default_diamond == diamond);
}

TEST_F(DiamondTest, ValidDiamondCreation) {
    Point<double> p1(0, 1), p2(1, 0), p3(0, -1), p4(-1, 0);
    EXPECT_NO_THROW({
        Diamond<double> diamond(p1, p2, p3, p4);
    });
}

TEST_F(DiamondTest, InvalidDiamondThrowsException) {
    Point<double> p1(0, 0), p2(1, 1), p3(2, 2), p4(3, 3);
    EXPECT_THROW({
        Diamond<double> diamond(p1, p2, p3, p4);
    }, exceptions::InvalidPointsException);
}

TEST_F(DiamondTest, DiamondEquality) {
    Diamond<double> diamond1;
    Diamond<double> diamond2;
    EXPECT_TRUE(diamond1 == diamond2);
}

TEST_F(DiamondTest, DiamondInequality) {
    Point<double> p1(0, 2), p2(2, 0), p3(0, -2), p4(-2, 0);
    Diamond<double> diamond1;
    Diamond<double> diamond2(p1, p2, p3, p4);
    EXPECT_TRUE(diamond1 != diamond2);
}

TEST_F(PentagonTest, DefaultConstructor) {
    EXPECT_NO_THROW({
        Pentagon<double> pentagon;
    });
}

TEST_F(PentagonTest, DefaultPentagonCenter) {
    auto center = default_pentagon->Center();
    EXPECT_NEAR(center.x, 0.0, EPS);
    EXPECT_NEAR(center.y, 0.0, EPS);
}

TEST_F(PentagonTest, DefaultPentagonArea) {
    double area = default_pentagon->Area();
    EXPECT_GT(area, 0.0);
}

TEST_F(PentagonTest, PentagonDoubleConversion) {
    double area = static_cast<double>(*default_pentagon);
    EXPECT_GT(area, 0.0);
}

TEST_F(PentagonTest, PentagonCopyConstructor) {
    Pentagon<double> copy(*default_pentagon);
    EXPECT_NEAR(copy.Area(), default_pentagon->Area(), EPS);
}

TEST_F(HexagonTest, DefaultConstructor) {
    EXPECT_NO_THROW({
        Hexagon<double> hexagon;
    });
}

TEST_F(HexagonTest, DefaultHexagonCenter) {
    auto center = default_hexagon->Center();
    EXPECT_NEAR(center.x, 0.0, EPS);
    EXPECT_NEAR(center.y, 0.0, EPS);
}

TEST_F(HexagonTest, DefaultHexagonArea) {
    double area = default_hexagon->Area();
    EXPECT_GT(area, 0.0);
    EXPECT_NEAR(area, 2.598, 0.1);
}

TEST_F(HexagonTest, HexagonDoubleConversion) {
    double area = static_cast<double>(*default_hexagon);
    EXPECT_GT(area, 0.0);
}

TEST_F(HexagonTest, InvalidHexagonThrowsException) {
    Point<double> p1(0, 0), p2(0, 0), p3(0, 0), p4(0, 0), p5(0, 0), p6(0, 0);
    
    EXPECT_THROW({
        Hexagon<double> hexagon(p1, p2, p3, p4, p5, p6);
    }, exceptions::InvalidPointsException);
}

TEST_F(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.Size(), 0);
    EXPECT_TRUE(v.IsEmpty());
    EXPECT_EQ(v.Capacity(), 0);
}

TEST_F(VectorTest, PushBackIncreasesSize) {
    Vector<int> v;
    v.PushBack(42);
    EXPECT_EQ(v.Size(), 1);
    EXPECT_FALSE(v.IsEmpty());
    EXPECT_EQ(v[0], 42);
}

TEST_F(VectorTest, FrontAndBackMethods) {
    EXPECT_EQ(int_vector.Front(), 1);
    EXPECT_EQ(int_vector.Back(), 3);
}

TEST_F(VectorTest, OutOfRangeAccessThrows) {
    Vector<int> empty;
    EXPECT_THROW(empty.Front(), exceptions::VectorOutOfRange);
    EXPECT_THROW(empty.Back(), exceptions::VectorOutOfRange);
    EXPECT_THROW(empty.PopBack(), exceptions::VectorOutOfRange);
}

TEST_F(VectorTest, CopyConstructor) {
    Vector<int> copy(int_vector);
    EXPECT_EQ(copy.Size(), int_vector.Size());
    EXPECT_EQ(copy[0], int_vector[0]);
    EXPECT_EQ(copy[1], int_vector[1]);
    EXPECT_EQ(copy[2], int_vector[2]);
}

TEST_F(VectorTest, MoveConstructor) {
    Vector<int> moved(std::move(int_vector));
    EXPECT_EQ(moved.Size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
    EXPECT_EQ(int_vector.Size(), 0); 
}

TEST_F(VectorTest, AssignmentOperator) {
    Vector<int> assigned;
    assigned = int_vector;
    EXPECT_EQ(assigned.Size(), 3);
    EXPECT_EQ(assigned[0], 1);
}

TEST_F(VectorTest, MoveAssignmentOperator) {
    Vector<int> moved;
    moved = std::move(int_vector);
    EXPECT_EQ(moved.Size(), 3);
    EXPECT_EQ(int_vector.Size(), 0);
}

TEST_F(VectorTest, ReserveIncreasesCapacity) {
    Vector<int> v;
    size_t old_capacity = v.Capacity();
    v.Reserve(20);
    EXPECT_GE(v.Capacity(), 20);
    EXPECT_LE(old_capacity, v.Capacity());
}

TEST_F(VectorTest, InsertElement) {
    int_vector.Insert(1, 99);
    EXPECT_EQ(int_vector.Size(), 4);
    EXPECT_EQ(int_vector[0], 1);
    EXPECT_EQ(int_vector[1], 99);
    EXPECT_EQ(int_vector[2], 2);
    EXPECT_EQ(int_vector[3], 3);
}

TEST_F(VectorTest, InsertAtEnd) {
    int_vector.Insert(3, 99);
    EXPECT_EQ(int_vector.Size(), 4);
    EXPECT_EQ(int_vector[3], 99);
}

TEST_F(VectorTest, InsertAtBeginning) {
    int_vector.Insert(0, 99);
    EXPECT_EQ(int_vector.Size(), 4);
    EXPECT_EQ(int_vector[0], 99);
    EXPECT_EQ(int_vector[1], 1);
}

TEST_F(VectorTest, EraseElements) {
    int_vector.Erase(1, 2);
    EXPECT_EQ(int_vector.Size(), 2);
    EXPECT_EQ(int_vector[0], 1);
    EXPECT_EQ(int_vector[1], 3);
}

TEST_F(VectorTest, EraseFromBeginning) {
    int_vector.Erase(0, 1);
    EXPECT_EQ(int_vector.Size(), 2);
    EXPECT_EQ(int_vector[0], 2);
    EXPECT_EQ(int_vector[1], 3);
}

TEST_F(VectorTest, EraseFromEnd) {
    int_vector.Erase(2, 3);
    EXPECT_EQ(int_vector.Size(), 2);
    EXPECT_EQ(int_vector[0], 1);
    EXPECT_EQ(int_vector[1], 2);
}

TEST_F(VectorTest, ClearMakesVectorEmpty) {
    int_vector.Clear();
    EXPECT_TRUE(int_vector.IsEmpty());
    EXPECT_EQ(int_vector.Size(), 0);
}

TEST_F(VectorTest, DataMethodReturnsRawPointer) {
    int* data = int_vector.Data();
    EXPECT_NE(data, nullptr);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
}

TEST_F(VectorTest, InitializerListConstructor) {
    Vector<int> v{10, 20, 30};
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST_F(VectorTest, SizeConstructor) {
    Vector<int> v(5);
    EXPECT_EQ(v.Size(), 5);
}

TEST_F(VectorTest, SizeValueConstructor) {
    Vector<int> v(3, 42);
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 42);
    EXPECT_EQ(v[2], 42);
}

TEST_F(VectorTest, FigureVectorTotalArea) {
    figure_vector.PushBack(std::make_shared<Diamond<double>>());
    figure_vector.PushBack(std::make_shared<Hexagon<double>>());
    
    double total_area = figure_vector.TotalArea<double>();
    EXPECT_GT(total_area, 0.0);
}

TEST_F(VectorTest, FigureVectorSeparateCenter) {
    figure_vector.PushBack(std::make_shared<Diamond<double>>());

    testing::internal::CaptureStdout();
    figure_vector.SeparateCenter();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(VectorTest, FigureVectorSeparateArea) {
    figure_vector.PushBack(std::make_shared<Pentagon<double>>());
    
    testing::internal::CaptureStdout();
    figure_vector.SeparateArea();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST(ExceptionTest, InvalidPointsExceptionMessage) {
    try {
        Point<double> p1(0, 0), p2(1, 1), p3(2, 2), p4(3, 3);
        Diamond<double> diamond(p1, p2, p3, p4);
        FAIL() << "Expected InvalidPointsException";
    } catch (const exceptions::InvalidPointsException& e) {
        EXPECT_STREQ(e.what(), "Diamond: wrong points");
    }
}

TEST(ExceptionTest, VectorOutOfRangeException) {
    Vector<int> empty;
    
    EXPECT_THROW(empty.PopBack(), exceptions::VectorOutOfRange);
    EXPECT_THROW(empty.Front(), exceptions::VectorOutOfRange);
    EXPECT_THROW(empty.Back(), exceptions::VectorOutOfRange);
}

TEST(PointTest, PointEquality) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.1, 2.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, PointInequality) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.1, 2.0);
    
    EXPECT_TRUE(p1 != p2);
}

TEST(PointTest, DistanceCalculation) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(3.0, 4.0);
    
    double dist = Distance(p1, p2);
    EXPECT_NEAR(dist, 5.0, EPS);
}

TEST(PointTest, PointOutputOperator) {
    Point<double> p(1.5, 2.5);
    
    testing::internal::CaptureStdout();
    std::cout << p;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(1.5, 2.5)");
}

TEST(EdgeCaseTest, LargeVectorOperations) {
    Vector<int> v;
    const size_t LARGE_SIZE = 1000;
    
    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        v.PushBack(static_cast<int>(i));
    }
    
    EXPECT_EQ(v.Size(), LARGE_SIZE);
    EXPECT_GE(v.Capacity(), LARGE_SIZE);
    
    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        EXPECT_EQ(v[i], static_cast<int>(i));
    }
    
    v.Clear();
    EXPECT_TRUE(v.IsEmpty());
}

TEST(EdgeCaseTest, VectorSelfAssignment) {
    Vector<int> v{1, 2, 3};
    v = v;
    EXPECT_EQ(v.Size(), 3);
    EXPECT_EQ(v[0], 1);
}

TEST(EdgeCaseTest, EmptyVectorOperations) {
    Vector<int> empty;
    
    EXPECT_NO_THROW(empty.Clear());
    EXPECT_NO_THROW(empty.Reserve(10));
    EXPECT_NO_THROW(empty.Data());
    EXPECT_TRUE(empty.IsEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    std::cout << "Running all tests..." << std::endl;
    std::cout << "===============================" << std::endl;
    
    int result = RUN_ALL_TESTS();
    
    std::cout << "===============================" << std::endl;
    if (result == 0) {
        std::cout << "All tests passed! ✓" << std::endl;
    } else {
        std::cout << "Some tests failed! ✗" << std::endl;
    }
    
    return result;
}