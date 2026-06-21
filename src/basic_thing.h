#ifndef BASIC_THING_H
#define BASIC_THING_H
#include <string>

class BasicThing
{
  protected:
    std::string m_name {};
    std::string m_description {};

  public:
    BasicThing(std::string_view name, std::string_view description);
    std::string name() const;
    std::string description() const;
    void set_name(std::string_view name);
    void set_description(std::string_view description);
    bool operator==(const BasicThing& other) const;
};

#endif