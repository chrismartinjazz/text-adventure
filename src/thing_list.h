#ifndef THING_LIST_H
#define THING_LIST_H

#include "text_helpers.h"
#include "thing.h"
#include <algorithm> // for std::find_if
#include <memory>    // for std::unique_ptr
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

enum class MoveResult
{
    Success,
    NotFound,
    CannotTake
};

class ThingList
{
    using VecPtrThing = std::vector<std::unique_ptr<Thing>>;

  protected:
    VecPtrThing m_thing_list {};

  public:
    ThingList() = default;
    ThingList(const ThingList&) = delete;
    ThingList& operator=(const ThingList&) = delete;
    ThingList(ThingList&&) = default;
    ThingList& operator=(ThingList&&) = default;

    bool contains(const Thing& thing) const
    {
        return std::find_if(
                   m_thing_list.begin(),
                   m_thing_list.end(),
                   [&thing](const std::unique_ptr<Thing>& p)
                   { return *p == thing; }
               ) != m_thing_list.end();
    }

    template <typename T>
    void add(T thing)
    {
        static_assert(std::is_base_of_v<Thing, T>, "T must derive from Thing");
        if (!contains(thing))
            m_thing_list.push_back(std::make_unique<T>(std::move(thing)));
    }

    template <typename T>
    void add(const std::vector<T>& things)
    {
        static_assert(std::is_base_of_v<Thing, T>, "T must derive from Thing");
        for (const auto& thing : things)
            add(thing);
    }

    Thing* this_ob(const std::string& name)
    {
        std::string name_cleaned { text::clean(name) };
        for (auto& thing : m_thing_list)
        {
            if (text::clean(thing->name()) == name_cleaned)
                return thing.get();
        }
        return nullptr;
    }

    MoveResult move_to(const std::string& name, ThingList& destination)
    {
        std::string name_cleaned { text::clean(name) };
        auto it = std::find_if(
            m_thing_list.begin(),
            m_thing_list.end(),
            [&name_cleaned](const std::unique_ptr<Thing>& p)
            { return text::clean(p->name()) == name_cleaned; }
        );

        if (it == m_thing_list.end())
            return MoveResult::NotFound;

        if (!(*it)->can_take())
            return MoveResult::CannotTake;

        destination.m_thing_list.push_back(std::move(*it));
        m_thing_list.erase(it);
        return MoveResult::Success;
    }

    std::string describe() const
    {
        if (m_thing_list.empty())
            return "nothing.";

        std::stringstream ss {};
        for (auto& thing : m_thing_list)
            ss << thing->name() << ". " << thing->description() << "; ";

        return ss.str();
    }
};

#endif