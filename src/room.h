#ifndef ROOM_H
#define ROOM_H

#include "thing_holder.h"
#include "thing_list.h"
#include <sstream>
#include <string>

namespace data
{
    enum class Rm;
}

class Room : public ThingHolder
{
  private:
    data::Rm m_n {};
    data::Rm m_s {};
    data::Rm m_w {};
    data::Rm m_e {};

  public:
    Room(
        std::string name,
        std::string description,
        data::Rm n,
        data::Rm s,
        data::Rm w,
        data::Rm e
    );
    data::Rm n() const;
    data::Rm s() const;
    data::Rm w() const;
    data::Rm e() const;
    std::string display();
};

#endif