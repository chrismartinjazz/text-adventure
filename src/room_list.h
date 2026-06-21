#ifndef ROOM_LIST_H
#define ROOM_LIST_H

#include "data.h"
#include "room.h"
#include <map>
#include <string>
#include <vector>

class RoomList
{
  private:
    std::map<data::Rm, Room> m_map {};

  public:
    Room room_at(data::Rm room_id) { return m_map.at(room_id); }

    std::string describe()
    {
        if (m_map.size() == 0)
            return "Nothing in RoomList.";

        std::string output {};
        {
            for (const auto& [key, room] : m_map)
            {
                output += room.description() + "\r\n";
            }
        }
        return output;
    }
};

#endif