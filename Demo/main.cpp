#include <iostream>
#include "SFMLRender.hpp"

int main() {
    try
    {
        auto renderer = new futils::SFMLRender("./config.json");

        auto container = renderer->createContainer();
        auto button = renderer->createButton("Quit");
        button->onClick([renderer]{
            renderer->close();
        });
        container->add(*button);

        while (!renderer->shouldClose())
        {
            renderer->draw();
            button->doAction();
        }
    }
    catch (std::exception const &error)
    {
        std::cerr << "Except:" << error.what() << std::endl;
    }
    return 0;
}