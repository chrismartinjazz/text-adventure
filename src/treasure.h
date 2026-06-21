#ifndef TREASURE_H
#define TREASURE_H

#include "basic_thing.h"

class Treasure : public BasicThing
{
  private:
    int m_value {};
    bool m_can_take {};

  public:
    Treasure(
        std::string_view name,
        std::string_view description,
        int value,
        bool can_take = true
    )
        : BasicThing(name, description)
        , m_value(value)
        , m_can_take(can_take)
    {
    }

    int value() const { return m_value; }
    bool can_take() const { return m_can_take; }
    void set_can_take(bool value) { m_can_take = value; }
};

#endif