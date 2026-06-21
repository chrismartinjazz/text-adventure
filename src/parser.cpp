#include "actor.h"
#include "data.h"
#include "text_helpers.h"
#include "word_and_type.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

class Parser
{
  public:
    std::string parse_command(
        std::vector<std::string>& words,
        std::map<data::Rm, Room>& map,
        Actor& player
    )
    {
        std::vector<WordAndType> command {};
        data::WT type {};
        std::string errmsg {};
        std::string output {};

        for (auto& word : words)
        {
            if (data::vocab.contains(word))
            {
                type = data::vocab.at(word);
                if (type == data::WT::Article)
                    continue;
                else
                    command.push_back({ word, type });
            }
            else
            {
                command.push_back({ word, data::WT::Error });
                errmsg = "Sorry, I don't understand " + word;
            }
        }

        if (errmsg != "")
            output = errmsg;
        else
            output = process_command(command, map, player);
        return output;
    }

  private:
    std::string process_command(
        std::vector<WordAndType>& command,
        std::map<data::Rm, Room>& map,
        Actor& player
    )
    {
        std::string output {};
        if (command.empty())
        {
            output = "You must write a command!";
        }
        else if (command.size() > 2)
        {
            output = "That command is too long! 2 words only!";
        }
        else
        {
            switch (command.size())
            {
            case 1: output = process_verb(command, map, player); break;
            case 2: output = process_verb_noun(command, map, player); break;
            default: output = "Unable to process command"; break;
            }
        }
        return output;
    }

    std::string process_verb(
        std::vector<WordAndType>& command,
        std::map<data::Rm, Room>& map,
        Actor& player
    )
    {
        WordAndType wt = command[0];
        std::string output {};
        if (wt.word() == "n")
            output = move_player_to(map, player, player.location().n());
        else if (wt.word() == "s")
            output = move_player_to(map, player, player.location().s());
        else if (wt.word() == "w")
            output = move_player_to(map, player, player.location().w());
        else if (wt.word() == "e")
            output = move_player_to(map, player, player.location().e());
        else if (wt.word() == "look")
            output = look(player);
        else
            throw std::runtime_error("Command not found");
        return output;
    }

    std::string process_verb_noun(
        std::vector<WordAndType>& command,
        [[maybe_unused]] std::map<data::Rm, Room>& map,
        [[maybe_unused]] Actor& player
    )
    {
        WordAndType wt1 = command[0];
        WordAndType wt2 = command[1];
        std::string output {};
        if (wt1.type() != data::WT::Verb)
            output =
                "Can't do this because '" + wt1.word() + "' is not a command!";
        else if (wt2.type() != data::WT::Noun)
            output =
                "Can't do this because '" + wt2.word() + "' is not an object!";
        else
        {
            if (wt1.word() == "take")
                output = take_ob(player, wt2.word());
            else if (wt1.word() == "drop")
                output = drop_ob(player, wt2.word());
            else
                output = "I don't know how to " + wt1.word() + " a " +
                         wt2.word() + "!";
        }
        return output;
    }

    std::string move_player_to(
        std::map<data::Rm, Room>& map, Actor& player, data::Rm new_location
    )
    {
        if (new_location == data::Rm::NoExit)
        {
            return "There is no exit in that direction.";
        }
        player.set_location((map.at(new_location)));
        return "You are now in the " + player.location().name() + '.';
    }

    std::string look(Actor& player) { return player.location().display(); }

    std::string take_ob(Actor& player, const std::string& obname)
    {
        switch (player.take(obname))
        {
        case MoveResult::Success: return obname + " taken.";
        case MoveResult::NotFound: return "You don't see " + obname + "here.";
        case MoveResult::CannotTake: return "You can't take " + obname;
        default:
            throw std::runtime_error(
                "Could not take object - unexpected result"
            );
        }
    }

    std::string drop_ob(Actor& player, const std::string& obname)
    {
        switch (player.drop(obname))
        {
        case MoveResult::Success: return obname + "dropped.";
        case MoveResult::NotFound: return "You don't have " + obname;
        case MoveResult::CannotTake: return "You can't drop " + obname;
        default:
            throw std::runtime_error(
                "Could not drop object - unexpected result"
            );
        }
    }
};