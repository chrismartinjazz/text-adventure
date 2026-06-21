#include "basic_thing.h"

BasicThing::BasicThing(std::string_view name, std::string_view description)
    : m_name { name }
    , m_description { description }
{
}

std::string BasicThing::name() const
{
    return m_name;
}

std::string BasicThing::description() const
{
    return m_description;
}

void BasicThing::set_name(std::string_view name)
{
    m_name = name;
}

void BasicThing::set_description(std::string_view description)
{
    m_description = description;
}

bool BasicThing::operator==(const BasicThing& other) const
{
    return name() == other.name();
}