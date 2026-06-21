#ifndef ACTOR_H
#define ACTOR_H

#include "room.h"
#include "thing_holder.h"

#include <string>
#include <string_view>

class Actor : public ThingHolder
{
  private:
    Room* m_location;

  public:
    Actor(
        const std::string_view name,
        const std::string_view description,
        Room& location
    )
        : ThingHolder(name, description)
        , m_location { &location }
    {
    }
    ~Actor() = default;
    Actor(const Actor& other) = delete;
    Actor& operator=(const Actor& other) = delete;

    Room& location() const { return *m_location; }
    void set_location(Room& location) { m_location = &location; }
    MoveResult take(const std::string& name)
    {
        return m_location->move_to(name, *this);
    }
    MoveResult drop(const std::string& name)
    {
        return move_to(name, *m_location);
    }
};

#endif