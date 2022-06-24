#include <string>
class user
{
private:
    int id;
    std::string name;
    std::string passwd;
    int type;
public:
    int get_id()
    {
        return id;
    }
    std::string get_name()
    {
        return name;
    }
    std::string get_passwd()
    {
        return passwd;
    }
    int get_type()
    {
        return type;
    }
    void set_id(int _id)
    {
        id = _id;
    }
    void set_name(std::string _name)
    {
        name = _name;
    }
    void set_passwd(std::string _passwd)
    {
        passwd = _passwd;
    }
    void set_type(int _type)
    {
        type = _type;
    }
};