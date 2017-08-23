//
// Created by ganz on 23/08/17.
//

# include "fender.h"
# include "futils.hpp"
# include "flog.hpp"

void    fender::IRender::SmartModeInit(futils::INI::INIProxy const &proxyConf,
                                       std::string const &confScope)
{
    this->configFunctions["WindowName"] = [this](std::string const &value)
    {
        this->_windowName = value;
    };
    this->configFunctions["WindowStyle"] = [this](std::string const &value)
    {
        if (value == "Borderless")
            this->_windowStyle = fender::IRender::WindowStyle::BORDERLESS;
        else if (value == "Normal")
            this->_windowStyle = fender::IRender::WindowStyle::NORMAL;
        else if (value == "Fullscreen")
            this->_windowStyle = fender::IRender::WindowStyle::FULLSCREEN;
        else
            throw std::runtime_error("Invalid WindowStyle Parameter:\t" + value);
    };
    this->configFunctions["AllowWindowResize"] = [this](std::string const &value)
    {
        if (value == "true" || value == "false")
            this->_resizable = value == "true";
        else
            throw std::runtime_error("Invalid AllowWindowResize Parameter");
    };
    this->configFunctions["WindowWidth"] = [this](std::string const &value)
    {
        if (futils::string::isNumber(value))
            this->_windowSize.X = std::stoi(value);
    };
    this->configFunctions["WindowHeight"] = [this](std::string const &value)
    {
        if (futils::string::isNumber(value))
            this->_windowSize.Y = std::stoi(value);
    };
    this->configFunctions["WindowHorizontalAlign"] = [this](std::string const &value)
    {
        if (value == "Center")
            this->_windowAlign.X = fender::IRender::Align::CENTER;
        else if (value == "Left")
            this->_windowAlign.X = fender::IRender::Align::LEFT;
        else if (value == "Right")
            this->_windowAlign.X = fender::IRender::Align::RIGHT;
        else
            throw std::runtime_error("Invalid Argument :\t" + value);
    };
    this->configFunctions["WindowVerticalAlign"] = [this](std::string const &value)
    {
        if (value == "Center")
            this->_windowAlign.Y = fender::IRender::Align::CENTER;
        else if (value == "Top")
            this->_windowAlign.Y = fender::IRender::Align::TOP;
        else if (value == "Bottom")
            this->_windowAlign.Y = fender::IRender::Align::BOTTOM;
        else
            throw std::runtime_error("Invalid Argument :\t" + value);    };

    LOUT("SmartMode detected. Running auto conf...");
    LOUT("Checking if scope " + confScope + " exists...");
    auto conf = (proxyConf[confScope]);
    LOUT("Found ! Starting configuration...");
    for (auto func: this->configFunctions)
    {
        LOUT("Setting " + func.first + " to " + conf[func.first].value);
        func.second(conf[func.first]);
    }
}
