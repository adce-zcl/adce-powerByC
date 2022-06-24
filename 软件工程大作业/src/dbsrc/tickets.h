#include <string>
class tickets
{
private:
    int id;
    int prices;
    int nums;
    int flight_id;
public:
    int get_id()
    {
        return id;
    }
    int get_prices()
    {
        return prices;
    }
    int get_nums()
    {
        return nums;
    }
    int get_flight_id()
    {
        return flight_id;
    }
    void set_id(int _id)
    {
        id = _id;
    }
    void set_prices(int _prices)
    {
        prices = _prices;
    }
    void set_nums(int _nums)
    {
        nums = _nums;
    }
    void set_flight_id(int _id)
    {
        flight_id = _id;
    }
};