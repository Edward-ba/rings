#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int age_;
public:
    Person()
    : name_("blank")
    , age_(0) {

    }

    Person(std::string name, int age)
    : name_(name)
    , age_(age) {

    }


    void dump() {
        std::cout << "name:" << name_ << " age:" << age_ << std::endl;
    }
};


int main(int argc, char* argv[]) {
    if (argc > 1)
        std::cout << "Hello World " << argv[1] << std::endl;
    else
        std::cout << "name of my program is " << argv[0] << std::endl;

    Person p0;
    p0.dump();

    if (argc > 2) {
        Person p1(argv[1], atoi(argv[2]));
        p1.dump();
    }
}
