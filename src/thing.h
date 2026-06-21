#ifndef THING_H
#define THING_H

#include "basic_thing.h"
#include <string_view>

class Thing : public BasicThing
{
  private:
    bool m_can_take {};

  public:
    Thing(
        std::string_view name,
        std::string_view description,
        bool can_take = true
    )
        : BasicThing(name, description)
        , m_can_take { can_take }
    {
    }

    bool can_take() const { return m_can_take; }
    void set_can_take(bool value) { m_can_take = value; }
};

#endif