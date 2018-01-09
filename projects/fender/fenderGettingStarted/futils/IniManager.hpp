//
// Created by Dowwind on 28/11/2017.
//

#ifndef RUTILS_INIMANAGER_HPP
#define RUTILS_INIMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <experimental/filesystem>
#ifdef _WIN32
# include <filesystem>
#endif
#include <fstream>
#include <iostream>

#include "RutilsException.hpp"
#include "RutilsParsingTools.hpp"

namespace rutils
{
    class IniManager;

    // TODO: il faut maintenant return cette classe quand on demande get Value
    class IniValue
    {
        std::string &_refValue;
    public:
        explicit IniValue(std::string &ref) : _refValue(ref) {}
        ~IniValue() = default;

        IniValue &operator=(int value) { _refValue = std::to_string(value); return *this; }
        IniValue &operator=(long value) { _refValue = std::to_string(value); return *this; }
        IniValue &operator=(double value) { _refValue = std::to_string(value); return *this; }
        IniValue &operator=(const std::string &value) { _refValue = value; return *this; }
        IniValue &operator=(bool value) { value ? _refValue = "true": _refValue = "false"; return *this; }

        operator int() const { return std::stoi(_refValue); }
        operator long() const { return std::stol(_refValue); }
        operator double() const { return std::stod(_refValue); }
        operator std::string() const { return _refValue; };
        operator bool() const
        {
            if (_refValue == "true")
                return true;
            else if (_refValue == "false")
                return false;
            throw std::logic_error("Not a boolean");
        }

        bool operator==(const std::string &cmp) { return _refValue == cmp; }
        bool operator==(long cmp) { return std::stol(_refValue) == cmp; }
        bool operator==(double cmp) { return std::stod(_refValue) == cmp; }
        bool operator==(bool cmp)
        {
            auto val = _refValue == "true" ? true : _refValue == "false" ? false : throw std::logic_error(_refValue + " is not a boolean.");
            return val == cmp;
        }

        bool operator<(long cmp) { return std::stol(_refValue) < cmp; }
        bool operator<=(long cmp) { return std::stol(_refValue) <= cmp; }
        bool operator>(long cmp) { return std::stol(_refValue) >= cmp; }
        bool operator>=(long cmp) { return std::stol(_refValue) >= cmp; }
        bool operator<(int cmp) { return std::stoi(_refValue) < cmp; }
        bool operator<=(int cmp) { return std::stoi(_refValue) <= cmp; }
        bool operator>(int cmp) { return std::stoi(_refValue) >= cmp; }
        bool operator>=(int cmp) { return std::stoi(_refValue) >= cmp; }
        bool operator<(double cmp) { return std::stod(_refValue) < cmp; }
        bool operator<=(double cmp) { return std::stod(_refValue) <= cmp; }
        bool operator>(double cmp) { return std::stod(_refValue) >= cmp; }
        bool operator>=(double cmp) { return std::stod(_refValue) >= cmp; }
    };

    class IniScope
    {
    private:
        std::unordered_map<std::string, std::string> _values;
    public:
        IniScope() = default;
        ~IniScope() = default;

        void add(std::string const &key, std::string const &value)
        {
            if (_values.find(key) != _values.end())
                throw rutils::SyntaxError("[INI] Key {" + key + "} already exists.");
            _values[key] = value;
        }

        bool exist(const std::string &key) const { return _values.find(key) != _values.end(); }

        std::string &at(const std::string &key) { return _values.at(key); }
        IniValue operator[](const std::string &key)
        {
            return IniValue(_values[key]);
        }

        //template <typename T,
        //        typename = std::enable_if<std::is_arithmetic<T>::value>>
        //T getValueAs(const std::string &key)
        //{
        //    if constexpr (std::is_floating_point<T>::value)
        //        return std::stod(at(key));
        //    else if constexpr (std::is_unsigned<T>::value)
        //        return std::stoul(at(key));
        //    else if constexpr (std::is_signed<T>::value)
        //        return std::stol(at(key));
        //    else
        //        static_assert(!std::is_floating_point<T>::value && std::is_unsigned<T>::value && std::is_signed<T>::value, "Only string, boolean or scalar types are accepted");
        //    return T();
        //}
    };

    class IniData
    {
    private:
        std::unordered_map<std::string, IniScope> _scopes{};
        std::experimental::filesystem::path _path;
        std::ifstream _in;

        void findValue(std::string const &line, std::string const &scopeName)
        {
            std::string key;
            std::string value;
            size_t equal;

            if ((equal = line.find('=')) == std::string::npos)
                throw rutils::SyntaxError("[INI] {=} not found.");
            key = line.substr(0, equal - 1);
            value = line.substr(equal + 1);
            if (value.find('\"') != std::string::npos)
                value = rutils::getStringBetweenDelimiter(value, '\"');
            _scopes[scopeName].add(rutils::trim(key), rutils::trim(value));
        }

        void parseIniFile()
        {
            std::string line;
            std::string scopeName;

            while (std::getline(_in, line))
            {
                line = rutils::removeAfterDelimiter(line, ';');
                if (line.empty())
                    continue;
                if (line.find('[') != std::string::npos)
                    scopeName = rutils::getStringBetweenDelimiter(line, '[', ']');
                else if (!scopeName.empty())
                    findValue(line, scopeName);
                else
                    throw rutils::SyntaxError("[INI] could not get value outside a scope.");
            }
        }

        std::string &getValue(const std::string &scope, const std::string &key) { return _scopes.at(scope).at(key); }

    public:
        explicit IniData(std::string const &path)
                : _path(path), _in(path)
        {
            if (!std::experimental::filesystem::exists(_path))
                throw rutils::FileNotFound(path + " does not exist.");
            if (!std::experimental::filesystem::is_regular_file(_path))
                throw rutils::InvalidTypeFile(path + " does not refer to a regular file.");
            parseIniFile();
        }

        bool exist(const std::string &scope, const std::string &key) const
        {
            if (key.empty())
                return _scopes.find(scope) != _scopes.end();
            return (_scopes.at(scope).exist(key));
        }

        IniScope &getScope(const std::string &scope) { return _scopes[scope]; }
    };

    class IniManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<IniData>> _iniFiles;
        IniManager() = default;

    public:
        IniManager(IniManager const &) = delete;
        IniManager &operator=(IniManager const &) = delete;

        static IniManager *instance() {
            static auto instance = static_cast<IniManager *>(nullptr);

            if (instance == nullptr)
                instance = new IniManager();
            return instance;
        }

        std::shared_ptr<IniData> getOrCreateIniData(std::string const &path)
        {
            if (_iniFiles.find(path) == _iniFiles.end())
                _iniFiles[path] = std::make_shared<IniData>(path);
            return _iniFiles.at(path);
        }
    };

    class IniFile
    {
    private:
        IniManager *_manager;
        std::shared_ptr<IniData> _iniData{};

    public:
        explicit IniFile(std::string const &path)
        {
            _manager = IniManager::instance();
            _iniData = _manager->getOrCreateIniData(path);
        }
        ~IniFile() = default;

        bool exist(const std::string &scope, const std::string &key = "") const { return _iniData->exist(scope, key); }

        IniScope &operator[](const std::string &scope) const {return _iniData->getScope(scope); }
    };

};

//template<>
//std::string rutils::IniScope::getValueAs<std::string>(std::string const &key)
//{
//    return at(key);
//}
//
//template<>
//bool rutils::IniScope::getValueAs<bool>(std::string const &key)
//{
//    std::string &tmp = at(key);
//
//    if (tmp == "true")
//        return true;
//    else if (tmp == "false")
//        return false;
//    else
//        throw rutils::SyntaxError("[INI] value is neither true or false.");
//    return false;
//}

//std::ostream &operator<<(std::ostream &os, const rutils::IniValue &toPrint)
//{
//    os << static_cast<std::string>(toPrint);
//    return os;
//}

#endif //RUTILS_INIMANAGER_HPP
