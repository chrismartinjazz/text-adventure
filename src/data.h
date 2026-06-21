#ifndef DATA_H
#define DATA_H

#include "room.h"
#include "thing_list.h"
#include <map>
#include <utility> // for std::pair
#include <vector>

namespace data
{
    enum class Dn
    {
        North,
        South,
        West,
        East,
        maxDn
    };

    enum class Rm
    {
        TrollRoom,
        Forest,
        Cave,
        Dungeon,
        NoExit,
        maxRm
    };

    inline std::map<Rm, Room> make_room_map()
    {
        std::map<Rm, Room> rooms;

        rooms.try_emplace(
            Rm::TrollRoom,
            "Troll Room",
            "a dank, dark room that smells of troll",
            Rm::NoExit,
            Rm::Cave,
            Rm::NoExit,
            Rm::Forest
        );
        rooms.try_emplace(
            Rm::Forest,
            "Forest",
            "a light, airy forest shimmering with sunlight",
            Rm::NoExit,
            Rm::NoExit,
            Rm::TrollRoom,
            Rm::NoExit
        );
        rooms.try_emplace(
            Rm::Cave,
            "Cave",
            "a vast cave with walls covered by luminous moss",
            Rm::TrollRoom,
            Rm::NoExit,
            Rm::NoExit,
            Rm::Dungeon

        );
        rooms.try_emplace(
            Rm::Dungeon,
            "Dungeon",
            "a gloomy dungeon. Rats scurry aross its floor",
            Rm::NoExit,
            Rm::NoExit,
            Rm::Cave,
            Rm::NoExit
        );
        return rooms;
    }

    inline void add_things(std::map<data::Rm, Room>& rooms)
    {
        using data::Rm;
        std::vector<std::tuple<Rm, Thing>> things {
            { Rm::TrollRoom, { "carrot", "It is a very crunchy carrot" } },
            { Rm::Forest, { "sausage", "It is a plump pork sausage" } },
            { Rm::Forest, { "tree", "It is a gigantic oak tree", false } }
        };

        for (auto& [room, thing] : things)
            rooms.at(room).add(thing);
    }

    enum class WT // Word Type
    {
        Noun,
        Verb,
        Adjective,
        Conjunction,
        Article,
        Preposition,
        Unknown,
        Error
    };

    inline std::map<std::string, WT> vocab {
        { "acorn", WT::Noun },    { "bed", WT::Noun },
        { "bin", WT::Noun },      { "bone", WT::Noun },
        { "button", WT::Noun },   { "carrot", WT::Noun },
        { "chest", WT::Noun },    { "coin", WT::Noun },
        { "door", WT::Noun },     { "dust", WT::Noun },
        { "gardenia", WT::Noun }, { "key", WT::Noun },
        { "knife", WT::Noun },    { "lamp", WT::Noun },
        { "leaflet", WT::Noun },  { "lever", WT::Noun },
        { "pearl", WT::Noun },    { "rat", WT::Noun },
        { "sack", WT::Noun },     { "sausage", WT::Noun },
        { "sign", WT::Noun },     { "slot", WT::Noun },
        { "sword", WT::Noun },    { "tree", WT::Noun },
        { "i", WT::Verb },        { "inventory", WT::Verb },
        { "take", WT::Verb },     { "drop", WT::Verb },
        { "put", WT::Verb },      { "look", WT::Verb },
        { "open", WT::Verb },     { "close", WT::Verb },
        { "pull", WT::Verb },     { "push", WT::Verb },
        { "n", WT::Verb },        { "s", WT::Verb },
        { "w", WT::Verb },        { "e", WT::Verb },
        { "q", WT::Verb },        { "quit", WT::Verb },
        { "up", WT::Verb },       { "down", WT::Verb },
        { "save", WT::Verb },     { "load", WT::Verb },
        { "the", WT::Article },   { "a", WT::Article },
        { "an", WT::Article }
    };
} // namespace data

#endif