#ifndef WORD_AND_TYPE
#define WORD_AND_TYPE

#include "data.h"
#include <string>
#include <string_view>

class WordAndType
{
  private:
    std::string m_word {};
    data::WT m_type {};

  public:
    WordAndType(std::string_view word, data::WT type)
        : m_word { word }
        , m_type { type }
    {
    }

    std::string word() const { return m_word; }
    data::WT type() const { return m_type; }
};

#endif