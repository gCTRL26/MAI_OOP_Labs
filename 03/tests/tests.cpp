#include <gtest/gtest.h>
#include <sstream>
#include "figure.hpp"
#include "diamond.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "vector.hpp"
#include "exception.hpp"

using namespace figure;
using namespace vector;

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(3.5, -2.1);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, -2.1);
}

TEST(PointTest, EqualityOperator) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(1.0, 2.000000001);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator) {
    Point p1(1.0, 2.0);
    Point p2(1.1, 2.0);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p1);
}

TEST(PointTest, DistanceCalculation) {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    
    EXPECT_DOUBLE_EQ(Distance(p1, p2), 5.0);
}

TEST(PointTest, StreamOutput) {
    Point p(1.5, -2.5);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(1.5, -2.5)");
}

TEST(PointTest, StreamInput) {
    Point p;
    std::stringstream ss("3.14 2.71");
    ss >> p;
    
    EXPECT_DOUBLE_EQ(p.x, 3.14);
    EXPECT_DOUBLE_EQ(p.y, 2.71);
}

TEST(DiamondTest, DefaultConstructor) {
    Diamond d;
    EXPECT_NO_THROW(d);
    EXPECT_GT(d.Area(), 0.0);
}

TEST(DiamondTest, ValidDiamondCreation) {
    Point p1(0, 1), p2(1, 0), p3(0, -1), p4(-1, 0);
    Diamond d(p1, p2, p3, p4);
    
    EXPECT_NEAR(d.Area(), 2.0, EPS);
    EXPECT_DOUBLE_EQ(d.Center().x, 0.0);
    EXPECT_DOUBLE_EQ(d.Center().y, 0.0);
}

TEST(DiamondTest, InvalidDiamondThrowsException) {
    Point p1(0, 0), p2(1, 1), p3(2, 2), p4(3, 3);
    
    EXPECT_THROW({
        Diamond d(p1, p2, p3, p4);
    }, exceptions::InvalidPointsException);
}

TEST(DiamondTest, CopyConstructor) {
    Diamond d1(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    Diamond d2(d1);
    
    EXPECT_DOUBLE_EQ(d1.Area(), d2.Area());
}

TEST(DiamondTest, AssignmentOperator) {
    Diamond d1(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    Diamond d2;
    d2 = d1;
    
    EXPECT_DOUBLE_EQ(d1.Area(), d2.Area());
}

TEST(DiamondTest, AreaCalculation) {
    Diamond d(Point(0, 3), Point(2, 0), Point(0, -3), Point(-2, 0));
    EXPECT_NEAR(d.Area(), 12.0, EPS);
}

TEST(DiamondTest, CenterCalculation) {
    Diamond d(Point(1, 2), Point(2, 1), Point(1, 0), Point(0, 1));
    Point center = d.Center();
    
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(DiamondTest, DoubleConversion) {
    Diamond d(Point(0, 2), Point(1, 0), Point(0, -2), Point(-1, 0));
    double area = static_cast<double>(d);
    
    EXPECT_NEAR(area, 4.0, EPS);
}

TEST(DiamondTest, EqualityOperator) {
    Diamond d1(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    Diamond d2(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    Diamond d3(Point(0, 2), Point(2, 0), Point(0, -2), Point(-2, 0));
    
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
}

TEST(DiamondTest, StreamOperations) {
    Diamond d1(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    std::stringstream ss;
    
    ss << d1;
    EXPECT_FALSE(ss.str().empty());
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle r;
    EXPECT_NO_THROW(r);
    EXPECT_GT(r.Area(), 0.0);
}

TEST(RectangleTest, ValidRectangleCreation) {
    Rectangle r(Point(0, 0), Point(0, 2), Point(3, 2), Point(3, 0));
    EXPECT_NEAR(r.Area(), 6.0, EPS);
}

TEST(RectangleTest, SquareCreation) {
    Rectangle square(Point(0, 0), Point(0, 2), Point(2, 2), Point(2, 0));
    EXPECT_NEAR(square.Area(), 4.0, EPS);
}

TEST(RectangleTest, InvalidRectangleThrowsException) {
    Point p1(0, 0), p2(1, 1), p3(2, 2), p4(3, 3); 
    
    EXPECT_THROW({
        Rectangle r(p1, p2, p3, p4);
    }, exceptions::InvalidPointsException);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle r(Point(0, 0), Point(0, 5), Point(4, 5), Point(4, 0));
    EXPECT_NEAR(r.Area(), 20.0, EPS);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle r(Point(1, 1), Point(1, 3), Point(4, 3), Point(4, 1));
    Point center = r.Center();
    
    EXPECT_DOUBLE_EQ(center.x, 2.5);
    EXPECT_DOUBLE_EQ(center.y, 2.0);
}

TEST(RectangleTest, DoubleConversion) {
    Rectangle r(Point(0, 0), Point(0, 3), Point(4, 3), Point(4, 0));
    double area = static_cast<double>(r);
    
    EXPECT_NEAR(area, 12.0, EPS);
}

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid t;
    EXPECT_NO_THROW(t);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid t;
    Point center = t.Center();

    EXPECT_NO_THROW(t.Center());
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid t;
    EXPECT_GE(t.Area(), 0.0);
}

class VectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        diamond = new Diamond(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
        rectangle = new Rectangle(Point(0, 0), Point(0, 2), Point(3, 2), Point(3, 0));
        trapezoid = new Trapezoid();
    }
    
    void TearDown() override {
        delete diamond;
        delete rectangle;
        delete trapezoid;
    }
    
    Diamond* diamond;
    Rectangle* rectangle;
    Trapezoid* trapezoid;
};

TEST_F(VectorTest, DefaultConstructor) {
    Vector v;
    EXPECT_TRUE(v.IsEmpty());
    EXPECT_EQ(v.Size(), 0);
    EXPECT_EQ(v.Capacity(), 0);
}

TEST_F(VectorTest, InitializerListConstructor) {
    Vector v = {diamond, rectangle};
    EXPECT_EQ(v.Size(), 2);
    EXPECT_FALSE(v.IsEmpty());
}

TEST_F(VectorTest, PushBack) {
    Vector v;
    v.PushBack(diamond);
    
    EXPECT_EQ(v.Size(), 1);
    EXPECT_EQ(&v[0], diamond);
}

TEST_F(VectorTest, AccessOperators) {
    Vector v = {diamond, rectangle};
    
    EXPECT_EQ(&v[0], diamond);
    EXPECT_EQ(&v[1], rectangle);
}

TEST_F(VectorTest, FrontAndBack) {
    Vector v = {diamond, rectangle};
    
    EXPECT_EQ(&v.Front(), diamond);
    EXPECT_EQ(&v.Back(), rectangle);
}

TEST_F(VectorTest, ReserveAndCapacity) {
    Vector v;
    size_t new_cap = 10;
    
    v.Reserve(new_cap);
    EXPECT_GE(v.Capacity(), new_cap);
    EXPECT_TRUE(v.IsEmpty());
}

TEST_F(VectorTest, Clear) {
    Vector v = {diamond, rectangle};
    
    EXPECT_EQ(v.Size(), 2);
    v.Clear();
    EXPECT_TRUE(v.IsEmpty());
    EXPECT_EQ(v.Size(), 0);
}

TEST_F(VectorTest, Insert) {
    Vector v = {diamond};
    v.Insert(0, rectangle);
    
    EXPECT_EQ(v.Size(), 2);
    EXPECT_EQ(&v[0], rectangle);
}

TEST_F(VectorTest, Erase) {
    Vector v = {diamond, rectangle};
    
    v.Erase(0, 1);
    EXPECT_EQ(v.Size(), 1);
    EXPECT_EQ(&v[0], rectangle);
}

TEST_F(VectorTest, PopBack) {
    Vector v = {diamond, rectangle};
    
    v.PopBack();
    EXPECT_EQ(v.Size(), 1);
    EXPECT_EQ(&v[0], diamond);
}

TEST_F(VectorTest, TotalArea) {
    Vector v = {diamond, rectangle};
    double total = v.TotalArea();
    
    EXPECT_GT(total, 0.0);
    EXPECT_NEAR(total, diamond->Area() + rectangle->Area(), EPS);
}

TEST_F(VectorTest, CopyConstructor) {
    Vector v1 = {diamond, rectangle};
    Vector v2(v1);
    
    EXPECT_EQ(v1.Size(), v2.Size());
}

TEST_F(VectorTest, AssignmentOperator) {
    Vector v1 = {diamond, rectangle};
    Vector v2;
    v2 = v1;
    
    EXPECT_EQ(v1.Size(), v2.Size());
}

TEST_F(VectorTest, SeparateCenter) {
    Vector v = {diamond, rectangle};

    EXPECT_NO_THROW(v.SeparateCenter());
}

TEST_F(VectorTest, SeparateArea) {
    Vector v = {diamond, rectangle};

    EXPECT_NO_THROW(v.SeparateArea());
}

TEST(IntegrationTest, VectorWithMultipleFigures) {
    Diamond* d = new Diamond(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    Rectangle* r = new Rectangle(Point(0, 0), Point(0, 2), Point(3, 2), Point(3, 0));
    Trapezoid* t = new Trapezoid();
    
    Vector v;
    v.PushBack(d);
    v.PushBack(r);
    v.PushBack(t);
    
    EXPECT_EQ(v.Size(), 3);
    EXPECT_GT(v.TotalArea(), 0.0);

    delete d;
    delete r;
    delete t;
}

TEST(IntegrationTest, FigurePolymorphism) {
    Diamond d(Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0));
    Rectangle r(Point(0, 0), Point(0, 2), Point(3, 2), Point(3, 0));
    
    Figure* figure1 = &d;
    Figure* figure2 = &r;

    EXPECT_GT(figure1->Area(), 0.0);
    EXPECT_GT(figure2->Area(), 0.0);
    EXPECT_NO_THROW(figure1->Center());
    EXPECT_NO_THROW(figure2->Center());
}

TEST(ExceptionTest, InvalidDiamondPoints) {
    EXPECT_THROW({
        Diamond d(Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 3));
    }, exceptions::InvalidPointsException);
}

TEST(ExceptionTest, InvalidRectanglePoints) {
    EXPECT_THROW({
        Rectangle r(Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 3));
    }, exceptions::InvalidPointsException);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}