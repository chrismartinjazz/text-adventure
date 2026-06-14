#include "room.cpp"
#include "ui_helpers.h"
#include <iostream>
#include <string_view>
#include <vector>

bool move_player_to_location(std::size_t& location_index, int new_location)
{
    if (new_location < 0)
    {
        std::cout << "You can't go that way.\n";
        return false;
    }
    location_index = static_cast<std::size_t>(new_location);
    return true;
}

int main()
{
    Room room0 { "Troll Room", "a dank, dark room that smells of troll",
                 -1,           2,
                 -1,           1 };
    Room room1 { "Forest", "a light, airy forest shimmering with sunlight",
                 -1,       -1,
                 0,        -1 };
    Room room2 { "Cave", "a vast cave with walls covered by luminous moss",
                 0,      -1,
                 -1,     3 };
    Room room3 { "Dungeon", "a gloomy dungeon. Rats scurry aross its floor",
                 -1,        -1,
                 2,         -1 };

    std::vector<Room> map { room0, room1, room2, room3 };
    std::size_t location_index { 0 };

    std::string input {};
    do
    {
        Room& location { map[location_index] };
        std::cout << location.display();
        input = ui::ask_input("> ");
        if (input.size() == 1)
        {
            switch (input[0])
            {
            case 'n':
                move_player_to_location(location_index, location.n());
                break;
            case 's':
                move_player_to_location(location_index, location.s());
                break;
            case 'w':
                move_player_to_location(location_index, location.w());
                break;
            case 'e':
                move_player_to_location(location_index, location.e());
                break;
            default: break;
            }
        }
    } while (input != "q");
    return 0;
}