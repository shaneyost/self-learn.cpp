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

    // Just read through the docs and std::stoi takes a const std::string&. However, I get away
    // with passing a const char* because of a implicit conversion happening. A maybe cleaner more
    // explicit way to write it would be std::stoi(std::string(value))

    // Another reading through some docs concluded that the conversion from const char* to the
    // const std::string& does allocate a temporary string on the heap. For high performance or 
    // tight loops I might want to think about strtol. 

    // For a brief moment I starting thinking "if strtol doesn't give me exception based error
    // handling then why not just use atoi()?". After some more reading I found out that strtol
    // provides error detection specifically for underflow and overflow which is more than what
    // atoi() provides. Also strtol can error detect and handle invalid input which atoi doesn't. 
    // There's also more options in turns of return types than what atoi can provide too.
    
    const char* avalue = std::getenv("KITTY_PID");
    if (value)
    {
        try
        {
            int value_to_integer = std::stoi(std::string(avalue));
            std::cout << value_to_integer << std::endl;
        }
        catch (const std::invalid_argument)
        {
            std::cerr << "KITTY_PID is not a valid number" << std::endl;
        }
        catch (const std::out_of_range)
        {
            std::cerr << "KITTY_PID is out of integer range" << std::endl;
        }
    }
    else
    {
        std::cout << "KITTY_PIT is not set" << std::endl;
    }

    // So lets say we want to use strtol, what would that look like? I don't like the fact I have
    // to write out long int. 
    //
    // I could use smaller type like int but I risk truncation and I would have to manually check
    // for that which I also don't want to do. So it would be better to just uint64_t or write out
    // long it.
    
    const char* bvalue = std::getenv("KITTY_PID");
    if (value)
    {
        char* end;
        errno = 0;
        long int value_to_integer = std::strtol(bvalue, &end, 10);

        if (errno == ERANGE)
        {
            std::cerr << "KITTY_PID is out of range" << std::endl;
        }
        else if (end == value || *end != '\0')
        {
            std::cerr << "KITTY_PID is not a valid integer" << std::endl;
        }
        else
        {
            std::cout << "KITTY_PID: " << value_to_integer << std::endl;
        }
    }
    else
    {
        std::cout << "KITTY_PID is not set" << std::endl;
    }
    return 0;
}
