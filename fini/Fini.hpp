//
// Created by ganz on 19/08/17.
//

#ifndef FSON_FSON_HPP
#define FSON_FSON_HPP

# include <iostream>
# include <fstream>
# include <algorithm>
# include <string>
# include <unordered_map>
# include <list>
# include <vector>
# include <iomanip>
# include <map>
# include "flog.hpp"

namespace futils
{
    class   INI
    {
        struct Line
        {
            int         nbr{0};
            std::string content{""};
            std::ostream &print(std::ostream &os = std::cout) const
            {
                os << std::setw(5) << nbr << "|\t" << content << std::endl;
                return os;
            }
        };

        struct Token
        {
            Token() = default;
            Token(std::string const &name, std::string const &value): name(name), value(value)
            {
                if (this->value.find(","))
                    this->list = futils::string::split(value, ',');
            }
            std::string name{""};
            std::string value{""};
            std::string content{""};
            std::vector<std::string>    list{};
            int         size() {return this->list.size();}
            int         lineNbr{-1};
            void    operator = (std::string const &val)
            {
                if (val == "")
                    throw std::runtime_error("Missing argument for "
                                             + this->name
                                             + " line "
                                             + std::to_string(this->lineNbr));
                if (val[0] == '\"' && val[val.size() - 1] == '\"')
                {
                    value = val;
                    value.erase(0, 1);
                    value = value.substr(0, value.size() - 1);
                }
                else
                    value = val;
            }
            
            void    operator = (int nbr)
            {
                value = std::to_string(nbr);
            }

            void    operator = (bool b) {
                value = b == true ? "true" : "false";
            }
    
            std::string const &get(int idx)
            {
                return this->list[idx];
            }
    
            operator std::string() const {return this->value;}
            explicit operator bool() const {
                return this->value == "true"; }
            explicit operator int() const {
                return std::stoi(this->value);
            }
        };

        friend std::ostream &operator << (std::ostream &os, Token const &tok)
        {
            os << tok.name << "=" << tok.value << std::endl;
            return os;
        }

    public:
        struct  Section
        {
            std::string         name{""};
            int                 lineNbr{-1};
            std::string         content{""};
            std::unordered_map<std::string, Token>  tokens{};
            std::map<int, std::string>                  tokenLineIndex{};

            void                set(Token *ptr)
            {
                this->tokens[ptr->name] = *ptr;
                this->tokenLineIndex[ptr->lineNbr] = ptr->name;
            }

            void                set(Token const &ref, int linenbr)
            {
                this->tokens[ref.name] = ref;
                this->tokenLineIndex[linenbr] = ref.name;
            }

            Token   &operator [] (std::string const &name)
            {
                if (this->tokens.find(name) == this->tokens.end())
                {
//                    This creates a solve for a petty bug
//                    Better solution is to change from map to vector
//                    and use capacity, reserve and size functions
                    auto line = this->tokenLineIndex.end()->first + 1;
                    this->tokens[name].name = name;
                    this->tokens[name].lineNbr = line;
                    this->tokenLineIndex[line] = name;
                }
                return this->tokens[name];
            }

            const Token &operator [] (std::string const &name) const
            {
                return this->tokens.at(name);
            }

            void                writeContentTo(std::ofstream &file) const
            {
                for (auto const &tok: this->tokenLineIndex)
                {
                    auto actualToken = this->tokens.at(tok.second);
                    if (actualToken.name[0] != '#')
                        file << actualToken.name << "=" << actualToken.value << std::endl;
                    else
                        file << actualToken.content << std::endl;
                }
                if (content != "")
                    file << content << std::endl;
            }
        };

    private:
        std::vector<char>   forbiddenCharacters{' ', '\n'};
        std::list<Line>     content{};
        std::string         input{""};
        std::string         filepath{""};
        std::fstream        iniFile;
        std::unordered_map<std::string, Section>        sections;
        std::unordered_map<std::string, std::string>    globalTokens;
        std::map<int, Section *>                        sectionIndexTable;

        bool            isSectionString(std::string const &ref) const
        {
            std::string cpy{this->epur(ref)};
            return (cpy[0] == '[' && cpy[cpy.size() - 1] == ']');
        }

        std::string     extractSectionName(std::string const &ref) const
        {
            std::string cpy{this->epur(ref)};
            return cpy.substr(1, cpy.size() - 2);
        }

        std::string     extractTokenName(std::string const &ref) const
        {
            auto    delimPos = ref.find("=");
            return ref.substr(0, delimPos);
        }

        std::string     extractTokenValue(std::string const &ref) const
        {
            auto    delimPos = ref.find("=");
            return ref.substr(delimPos + 1, ref.size());
        }

        bool            isToken(std::string const &ref) const
        {
            auto index = ref.find("=");
            return (index != std::string::npos);
        }

        void            loadINI()
        {
            if (!this->iniFile.is_open())
                return ;

            int         nbr{0};
            std::string line;
            std::string mostRecentSection{""};

            while ( getline (this->iniFile, line) )
            {
                content.push_back({nbr, line});
                if (isSectionString(line))
                {
                    auto name = this->extractSectionName(line);
                    mostRecentSection = name;
                    this->sections[name] = Section{.name = name, .lineNbr = nbr};
                    this->sectionIndexTable[nbr] = &this->sections[name];
                }
                else if (isToken(line))
                {
                    auto name = this->extractTokenName(line);
                    auto value = this->extractTokenValue(line);
                    if (mostRecentSection != "")
                        this->sections[mostRecentSection]
                                .set(Token{.name = name, .value = value}, nbr);
                    else
                        this->globalTokens[name] = value;
                }
                else
                {
                    if (mostRecentSection == "")
                    {
                        auto sec = new Section;
                        sec->name = "#" + std::to_string(nbr);
                        sec->content = line;
                        sec->lineNbr = nbr;
                        this->sectionIndexTable[nbr] = sec;
                    }
                    else
                    {
                        auto tok = new Token;
                        tok->name = "#" + std::to_string(nbr);
                        tok->content = line;
                        tok->lineNbr = nbr;
                        this->sections[mostRecentSection].set(tok);
                    }
                }
                input += this->epur(line);
                nbr++;
            }
        }

        std::string     epur(std::string const &str) const
        {
            std::string cleanStr;

            for (auto const &letter: str)
            {
                bool    should{true};
                for (auto const &key: forbiddenCharacters)
                    if (letter == key)
                        should = false;
                if (should)
                    cleanStr.push_back(letter);
            }
            return cleanStr;
        }

        void    writeContentTo(std::string const &file) const
        {
            std::ofstream    outputFile;

            outputFile.open(file);
            if (outputFile.is_open())
            {
                LOUT("Saved INI " + this->filepath + " to " + file);
                for (auto const &sec: this->sectionIndexTable)
                {
                    if (sec.second->name != "")
                        outputFile << "[" + sec.second->name+ "]" << std::endl;
                    sec.second->writeContentTo(outputFile);
                }
            }
        }

        void        preLoad()
        {
            iniFile.open(this->filepath);
            if (iniFile.is_open())
                this->loadINI();
            else
            {
                iniFile.open(this->filepath, std::fstream::out);
                this->loadINI();
            }
        }

    public:
        class   INIProxy
        {
            std::unordered_map<std::string, Section> const &_sections;
            std::list<Line>                          const &_content;
        public:
            INIProxy(std::unordered_map<std::string, Section> const &sections,
                     std::list<Line> const &content):
                    _sections(sections),
                    _content(content)
            {
            
            }

            const Section   &operator [] (std::string const &name) const
            {
                return this->_sections.at(name);
            }
        };


        INI(std::string const &file): filepath(file)
        {
            if (file != "")
                this->preLoad();
        }

        ~INI()
        {
            this->iniFile.close();
        }

        void    save(std::string const &file = "")
        {
            if (file == "")
                this->writeContentTo(this->filepath);
            else
                this->writeContentTo(file);
        }

        void    print() const
        {
            for (auto const &line: this->content)
                line.print();
        }

        Section   &operator [] (std::string const &name)
        {
            if (this->sections.find(name) == this->sections.end())
            {
                auto line = this->sectionIndexTable.end()->first;
                this->sections[name].lineNbr = line;
                this->sections[name].name = name;
                this->sections[name].content = "";
                this->sectionIndexTable[line] = &this->sections[name];
            }
            return this->sections[name];
        }

        void    reset(std::string const &file)
        {
            this->sections.clear();
            this->content.clear();
            this->sectionIndexTable.clear();
            if (this->iniFile.is_open())
                this->iniFile.close();
            this->globalTokens.clear();
            this->input.clear();
            this->filepath = file;
            if (file != "")
                this->preLoad();
        }

        void    closeFile()
        {
            if (this->iniFile.is_open())
                this->iniFile.close();
        }

        INIProxy    *proxy()
        {
            return new INIProxy(this->sections, this->content);
        }


        std::string const &getFilePath() const { return this->filepath; }
        std::vector<std::string>    getScopeList() const
        {
            std::vector<std::string>    result;

            for (auto const &name: this->sectionIndexTable)
            {
                result.push_back(name.second->name);
            }
            return result;
        }
    };
}

#endif //FSON_FSON_HPP
