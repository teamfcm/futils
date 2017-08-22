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
            std::string name{""};
            std::string value{""};
            std::string content{""};
            int         lineNbr{-1};
            void    operator = (std::string const &val)
            {
                if (val[0] == '\"' && val[val.size() - 1] == '\"')
                    value = val;
                else
                    value = "\"" + val + "\"";
            }

            void    operator = (int nbr)
            {
                value = std::to_string(nbr);
            }

            operator std::string() { return this->value; }
        };

        friend std::ostream &operator << (std::ostream &os, Token const &tok)
        {
            os << tok.name << "=" << tok.value << std::endl;
            return os;
        }

        struct  Section
        {
            std::string         name;
            int                 lineNbr;
            std::string         content{""};
            std::unordered_map<std::string, Token>  tokens{};
            std::map<int, Token *>                  tokenLineIndex{};

            void                set(Token *ptr)
            {
                this->tokens[ptr->name] = *ptr;
                this->tokenLineIndex[ptr->lineNbr] = &this->tokens[ptr->name];
            }

            void                set(Token const &ref, int linenbr)
            {
                this->tokens[ref.name] = ref;
                this->tokenLineIndex[linenbr] = &this->tokens[ref.name];
            }

            Token   &operator [] (std::string const &name)
            {
                return this->tokens[name];
            }

            void                writeContentTo(std::ofstream &file) const
            {
                for (auto const &tok: this->tokenLineIndex)
                {
                    if (tok.second->name != "")
                        file << tok.second->name << "=" << tok.second->value << std::endl;
                    else
                        file << tok.second->content << std::endl;
                }
                if (content != "")
                    file << content << std::endl;
            }
        };

        std::vector<char>   forbiddenCharacters{' ', '\n'};
        std::list<Line>     content;
        std::string         input{""};
        std::string         filepath;
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
                        sec->name = "";
                        sec->content = line;
                        sec->lineNbr = nbr;
                        this->sectionIndexTable[nbr] = sec;
                    }
                    else
                    {
                        auto tok = new Token;
                        tok->name = "";
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
        INI(std::string const &file = ""): filepath(file)
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

        std::string const &getFilePath() const { return this->filepath; }
    };
}

#endif //FSON_FSON_HPP
