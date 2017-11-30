//
// Created by dowwind on 29/11/17.
//

#ifndef RUTILS_RUTILSPARSINGTOOLS_HPP
#define RUTILS_RUTILSPARSINGTOOLS_HPP

#include <string>
#include "RutilsException.hpp"

namespace rutils
{
    static std::string getStringBetweenDelimiter(const std::string &line,
                                                 const std::string &delimiter,
                                                 const std::string &oppositeDelimiter = "")
    {
        const auto openDelimiter = line.find(delimiter);
        const auto endDelimiter = line.find(oppositeDelimiter.empty() ? delimiter : oppositeDelimiter, oppositeDelimiter.empty() ? openDelimiter + 1 : 0);

        if (openDelimiter == std::string::npos || endDelimiter == std::string::npos)
            throw rutils::SyntaxError("Missing delimiter {" + delimiter + "}"
                                      + (oppositeDelimiter.empty() ? "" : "or {" + oppositeDelimiter + "}")
                                      + "in the line : " + line);
        if (openDelimiter > endDelimiter)
            throw rutils::SyntaxError("The open delimiter is behind the close delimiter in the line : " + line);
        return line.substr(openDelimiter + 1, endDelimiter - openDelimiter - 1);
    }

    static std::string getStringBetweenDelimiter(const std::string &line,
                                                 char delimiter,
                                                 char oppositeDelimiter = '\0')
    {
        const auto openDelimiter = line.find(delimiter);
        const auto endDelimiter = line.find(oppositeDelimiter == '\0' ? delimiter : oppositeDelimiter, oppositeDelimiter == '\0' ? openDelimiter + 1 : 0);

        if (openDelimiter == std::string::npos || endDelimiter == std::string::npos)
            throw rutils::SyntaxError("Missing delimiter {" + std::to_string(delimiter) + "}"
                                      + (oppositeDelimiter == '\0' ? "" : "or {" + std::to_string(oppositeDelimiter) + "}")
                                      + "in the line : " + line);
        if (openDelimiter > endDelimiter)
            throw rutils::SyntaxError("The open delimiter is behind the close delimiter in the line : " + line);
        return line.substr(openDelimiter + 1, endDelimiter - openDelimiter - 1);
    }

    static std::string removeAfterDelimiter(const std::string &line,
                                            const std::string &delimiter)
    {
        const auto delimiterPosition = line.find(delimiter);

        if (delimiterPosition == std::string::npos)
            return line;
        return line.substr(0, delimiterPosition);
    }

    static std::string removeAfterDelimiter(const std::string &line,
                                            char delimiter)
    {
        const auto delimiterPosition = line.find(delimiter);

        if (delimiterPosition == std::string::npos)
            return line;
        return line.substr(0, delimiterPosition);
    }

    static std::string trim(const std::string& str,
                            const std::string& whitespace = " \t")
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        if (strBegin == std::string::npos)
            return "";
        return str.substr(strBegin, strRange);
    }

}

#endif //RUTILS_RUTILSPARSINGTOOLS_HPP
