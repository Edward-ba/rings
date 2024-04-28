#include <functional>
#include <iostream>
#include <vector> 
#include <ostream>
#include <iterator>
#include <algorithm>

std::vector<int>getNumbers(int begin, int end, int inc=1) {

    std::vector<int> numbers;
    for (int i = begin; i < end; i += inc) {
        numbers.push_back(i);
    }

    return numbers; 
}

void func() {

   int i = 3;
   int j = 5;

   // The following lambda expression captures i by value and j by reference.
   std::function<int (void)> f = [i, &j] { return i + j; };

   // Change the values of i and j.
   i = 22;
   j = 44;

   // Call f and print its result.
   std::cout << "f():" << f() << std::endl;

    auto foo0 = []<typename T>(const std::vector<T>& vec) { 
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(std::cout, " ")); 
        std::cout << std::endl;
    };


    // std::function<const std::vector<T>&> foo1 = []<typename T>(const std::vector<T>& vec) { 
    //     std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(std::cout, " ")); 
    //     std::cout << std::endl;
    // };


    std::vector eg = {1, 2, 3};
    foo0(eg);


}
struct Basics {
    int i;
    char c;
    float f;
    double d;
    auto operator<=>(const Basics&) const = default;
};
 
struct Arrays {
    int ai[1];
    char ac[2];
    float af[3];
    double ad[2][2];
    auto operator<=>(const Arrays&) const = default;
};
 
struct Bases : Basics, Arrays {
    auto operator<=>(const Bases&) const = default;
};
 

template <typename T>        
struct ImplicitClass {
    ImplicitClass (T t) {
        std::cout << t << '\n';
    }
};


template <typename T>
struct NoImplict {
    explicit NoImplict(T t) {    
        std::cout << t << '\n';
    }
};

int main() {

    ImplicitClass num0 = 1;
    ImplicitClass str = "one";

    NoImplict num1(1);
    NoImplict abc("abc");


    func();
    std::cout << "----\n" << std::endl;

    const auto numbers= getNumbers(-10, 11);
    for (auto n: numbers) 
        std::cout << n << " ";
    std::cout << "\n";

    for (auto n: getNumbers(0, 101, 5)) 
        std::cout << n << " "; 
    std::cout << "\n";
    std::cout << "----\n" << std::endl;

    constexpr Bases a = { { 0, 'c', 1.f, 1. },
    { { 1 }, { 'a', 'b' }, { 1.f, 2.f, 3.f }, { { 1., 2. }, { 3., 4. } } } };

    constexpr Bases b = { { 0, 'c', 1.f, 1. },
    { { 1 }, { 'a', 'b' }, { 1.f, 2.f, 3.f }, { { 1., 2. }, { 3., 4. } } } };
    
    static_assert(a == b);
    static_assert(!(a != b));
    static_assert(!(a < b));
    static_assert(a <= b);
    static_assert(!(a > b));
    static_assert(a >= b);
    
}