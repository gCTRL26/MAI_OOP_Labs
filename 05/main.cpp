#include <iostream>
#include "vector.hpp"

struct Person {
    int age;
    std::string name;
};

std::ostream& operator<<(std::ostream& os, const Person& ppl) {
    os << ppl.name << " " << ppl.age;
    return os;
}

int main() {
    vector::Vector<int> v;
    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);
    v.PushBack(4);
    for (auto it = v.Begin(); it != v.End(); ++it) {
        std::cout << *it << std::endl;
    }
    vector::Vector<Person> pers;
    pers.PushBack({15, "Nicolya"});
    pers.PushBack({19, "Max"});
    pers.PushBack({15, "Milana"});
    for (auto it = pers.Begin(); it != pers.End(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}