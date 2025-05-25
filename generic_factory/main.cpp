#include <iostream>

/*
 * Interface Class
 * Declares all methods (the API) that all concrete class must implement
 * - You cannot instantiate abstract classes.
 * */
class Device
{
public:
    virtual void run() = 0;
    virtual ~Device() = default;
};

/*
 * Concrete Class
 * Provides a specific implementation of the interface
 * */
class Gps : public Device
{
public:
    void run() override
    {
        std::cout << "Running Gps" << std::endl; 
    }
};
class Imu : public Device
{
public:
    void run() override
    {
        std::cout << "Running Imu" << std::endl; 
    }
};

/*
 * Creator class
 * Defines the factory method that creates objects based on type
 * */
class DeviceFactory
{
public:
    static std::unique_ptr<Device> create(std::string_view dev)
    {
        if (dev == "gps") return std::make_unique<Gps>();
        if (dev == "imu") return std::make_unique<Imu>();
        return nullptr;
    }
};

int main ()
{
    auto imu_device = DeviceFactory::create("imu");
    auto gps_device = DeviceFactory::create("gps");

    if (imu_device) imu_device->run();
    if (gps_device) gps_device->run();
}

/*
 *  1.  Does a creator class always need to have static methods so I never need to instantiate it?
 *  2.  Why does a class with static methods never need to be instantiated? Can it have a cpp?
 *  3.  If we can have non-static methods rewrite it with an example of one
 *  4.  Do we call it a factory class or creator class?
 *  5.  Confused by the book's implementation of a creator class. Maybe understand this more
 * */
