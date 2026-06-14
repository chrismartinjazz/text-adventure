#include <sstream>
#include <string>

class Room
{
  private:
    std::string m_name {};
    std::string m_description {};
    int m_n {};
    int m_s {};
    int m_w {};
    int m_e {};

  public:
    Room(std::string name, std::string description, int n, int s, int w, int e)
        : m_name { name }
        , m_description { description }
        , m_n { n }
        , m_s { s }
        , m_w { w }
        , m_e { e }
    {
    }
    std::string name() const { return m_name; }
    std::string description() const
    {
        return std::string { "This is " + m_description };
    }
    int n() const { return m_n; }
    int s() const { return m_s; }
    int w() const { return m_w; }
    int e() const { return m_e; }
    void set_name(std::string_view name) { m_name = name; }
    void set_description(std::string_view description)
    {
        m_description = description;
    }
    // void set_n(int n) { m_n = n; }
    // void set_n(int s) { m_s = s; }
    // void set_n(int w) { m_w = w; }
    // void set_n(int e) { m_e = e; }

    std::string display()
    {
        std::stringstream ss {};
        ss << m_name << ": " << description() << '\n';
        return ss.str();
    }
};