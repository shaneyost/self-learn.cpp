#include <iostream>
#include <string_view>

/*constexpr std::string_view MY_OTHER_STRING = "Hello World";*/

void practical_example_01(void)
{
    std::string s{"foo"};
    std::string_view sv = s;
    std::cout << sv << std::endl;
}

void practical_example_02(void)
{
    // Lets modify the view
    std::string_view sv{"foobar"};
    sv.remove_prefix(3);
    std::cout << sv << std::endl;
}

void practical_example_03(void)
{
    // There are many methods we can use on a string_view object
    std::string_view sv{"Shane Yost"};

    // Size & Capacity
    std::cout << "Size: " << sv.size() << std::endl;
    std::cout << "Size: " << sv.length() << std::endl;
    std::cout << "Is sv empty? " << sv.empty() << std::endl;

    // Element Access
    std::cout << "Character at index 1 (no bounds check): " << sv[1] << std::endl;
    std::cout << "Character at index 1 (bounds check): " << sv.at(1) << std::endl;
    std::cout << "First character: " << sv.front() << std::endl;
    std::cout << "Second character: " << sv.back() << std::endl;

    // Comparison
    std::string_view sv1{"Shane"};
    std::string_view sv2 = sv1;
    std::cout << "Comparing returned: " << sv1.compare(sv2) << std::endl;

    // so many more
}

void bad_example_01(void)
{
    std::string_view sv{};
    {
        std::string s{"Hello Shane"};
        sv = s;
    } // s is destroyed here
    std::cout << "Undefined behavior: " << sv << std::endl;
}

std::string getStrObj(void) { return std::string{"Han Solo"}; }
void bad_example_02(void)
{
    // Return values are temporary objects that are destroyed at the end of the full expression
    // containing the function call. I must either use this return value immediately or copy it to
    // use later.
    std::string_view sv{ getStrObj() };
    std::cout << "Undefined behavior: " << sv << std::endl;
}

int main ()
{
    practical_example_01();
    practical_example_02();
    practical_example_03();
    bad_example_01();
    bad_example_02();
    return 0;
}
