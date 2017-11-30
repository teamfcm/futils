//
// Created by arroganz on 11/29/17.
//

# include "extras.hpp"

fender::Background::Background(std::string const &image)
{
    auto &Transform = attach<components::Transform>();
    auto &Img= attach<components::Image>(image);
    Img.color = fender::Color::WHITE;
    Transform.h = 1;
    Transform.w = 1;
    Transform.x = 0;
    Transform.y = 0;
}
