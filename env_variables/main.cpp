#include <iostream>
#include <cstdlib>
#include <string>

int main ()
{
    std::cout << std::getenv("USER") << std::endl;
    std::cout << std::getenv("KITTY_PID") << std::endl;

    // Sometimes I may want to process the C style string. For example, if the env is a number (or
    // we at last expect it to be a number we have a couple choices. However, one of these choices
    // will not provide as friendly of a error handling method as the other.

    // Lets try std::stoi

    const char* value = std::getenv("KITTY_PID");
    if (value)
    {
        try
        {
            int value_to_integer = std::stoi(value);
            std::cout << value_to_integer << std::endl;
        }
        catch (const std::invalid_argument&)
        {
            std::cerr << "KITTY_PID is not a valid number" << std::endl; 
        }
        catch (const std::out_of_range&)
        {
            std::cerr << "KITTY_PID is out of integer range" << std::endl;
        }
    }
    else
    {
        std::cout << "KITTY_PID is not set" << std::endl;
    }

    // We can use atoi but on failure all we get is a 0 returned. However, the env variable could
    // be a zero. So now what? This is the limitation behind atoi. 
    
    const char* another_value = std::getenv("KITTY_PID");
    if (another_value)
    {
        int value_to_integer = std::atoi(another_value);
        std::cout << value_to_integer << std::endl;
    }
    else
    {
        std::cout << "KITTY_PID is not set" << std::endl;
    }
    return 0;
}
