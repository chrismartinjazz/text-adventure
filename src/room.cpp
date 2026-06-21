#include "room.h"
#include "basic_thing.h"
#include "data.h"
#include "thing_list.h"
#include <sstream>
#include <string>

Room::Room(
    std::string name,
    std::string description,
    data::Rm n,
    data::Rm s,
    data::Rm w,
    data::Rm e
)
    : ThingHolder { name, description }
    , m_n { n }
    , m_s { s }
    , m_w { w }
    , m_e { e }
{
}
data::Rm Room::n() const
{
    return m_n;
}
data::Rm Room::s() const
{
    return m_s;
}
data::Rm Room::w() const
{
    return m_w;
}
data::Rm Room::e() const
{
    return m_e;
}
std::string Room::display()
{
    std::stringstream ss {};
    ss << "[" << m_name << "] This is " << description()
       << "\nHere there is: " << m_things.describe();
    return ss.str();
}