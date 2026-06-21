#ifndef THING_HOLDER_H
#define THING_HOLDER_H

#include "thing.h"
#include "thing_list.h"
#include <string>
#include <string_view>

class ThingHolder : public Thing
{
  protected:
    ThingList m_things {};

  public:
    ThingHolder(std::string_view name, std::string_view description)
        : Thing(name, description)
    {
    }

    template <typename T>
    void add(T thing)
    {
        m_things.add(std::move(thing));
    }

    Thing* this_ob(const std::string& name) { return m_things.this_ob(name); }

    MoveResult move_to(const std::string& name, ThingHolder& destination)
    {
        return m_things.move_to(name, destination.m_things);
    }
};

#endif