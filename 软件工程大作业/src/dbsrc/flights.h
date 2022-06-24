#include <string>
class flights
{
private:
    int id;
    std::string start;
    std::string end;
    std::string start_time;
    std::string end_time;
public:
    int get_id()
    {
        return id;
    }
    std::string get_start()
    {
        return start;
    }
    std::string get_end()
    {
        return end;
    }
    std::string get_start_time()
    {
        return start_time;
    }
    std::string get_end_time()
    {
        return end_time;
    }
    void set_id(int _id)
    {
        id = _id;
    }
    void set_start(std::string _start)
    {
        start = _start;
    }
    void set_end(std::string _end)
    {
        end = _end;
    }
    void set_start_time(std::string _start_time)
    {
        start_time = _start_time;
    }
    void set_end_time(std::string _end_time)
    {
        end_time = _end_time;
    }
};