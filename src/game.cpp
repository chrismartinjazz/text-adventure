#include "actor.h"
#include "data.h"
#include "parser.cpp"
#include "room.h"
#include "text_helpers.h"
#include "thing_list.h"
#include "ui_helpers.h"
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class Game
{
  private:
    std::map<data::Rm, Room> m_map { data::make_room_map() };
    Parser m_parser {};
    const std::vector<std::string> m_commands { "n", "s", "w", "e", "look" };
    Actor m_player;

  public:
    Game()
        : m_map { data::make_room_map() }
        , m_player { "You", "The Player", m_map.at(data::Rm::TrollRoom) }
    {
        start_game();
    }

    void start_game()
    {
        data::add_things(m_map);
        std::cout
            << "Welcome to the Great Adventure!\r\nYou are in the "
            << m_player.location().name() << ". It is "
            << m_player.location().description()
            << ".\nWhere do you want to go now?\r\nEnter: N, S, W or E.\r\n";
        std::string input {};
        std::string output {};
        do
        {
            input = ui::ask_input("> ");
            output = run_command(input);
            std::cout << output << '\n';
        } while (input != "q");
    }

    std::string run_command(const std::string& input)
    {
        std::string cleaned_input { text::clean(input) };

        if (cleaned_input == "q")
            return "ok";

        if (cleaned_input == "")
            return "You must enter a command.";

        std::vector<std::string> words {
            text::split_by_delimiters(cleaned_input)
        };

        return m_parser.parse_command(words, m_map, m_player);
    }
};