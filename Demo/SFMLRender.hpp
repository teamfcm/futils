//
// Created by ganz on 22/07/17.
//

#ifndef DEMO_SFMLRENDER_HPP
#define DEMO_SFMLRENDER_HPP

# include <string>
# include <functional>
# include <unordered_map>

namespace futils
{
    class AButton
    {
        std::function<void(void)>   clickAction;
        std::string                 name;
    public:
        AButton(std::string const &name): name(name) {};
        ~AButton() = default;

        void    onClick(std::function<void(void)> action) { this->clickAction = action; };
        void    doAction() { this->clickAction(); };
        std::string const &getName() { return this->name; }
    };

    class AContainer
    {
        std::unordered_map<std::string, AButton *>  buttons;
    public:
        AContainer() = default;
        ~AContainer() = default;
        void    add(AButton &b) { this->buttons[b.getName()] = &b; };
    };

    class IRender
    {
        bool    stopRequested;
    public:
        virtual ~IRender() {}

        AContainer      *createContainer() { return new AContainer; };
        AButton         *createButton(std::string const &name) { return new AButton(name); };
        bool            shouldClose() const noexcept { return this->stopRequested; };
        void            close() noexcept { this->stopRequested = true; };
        void            draw() { std::cout << __FUNCTION__ << std::endl; };
    };


    class SFMLRender : public IRender
    {
    public:
        SFMLRender(std::string const &configFile) { std::cout << configFile << std::endl; };
        ~SFMLRender() = default;


    };
}

#endif //DEMO_SFMLRENDER_HPP
