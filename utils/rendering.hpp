//
// Created by arroganz on 12/17/17.
//

#ifndef FENDER_RENDERING_HPP
#define FENDER_RENDERING_HPP

// This header file is a list of abstract types representing various rendering elements

# include <stddef.h>
# include <iostream>
# include "math.hpp"

namespace futils
{
    enum class WStyle
    {
        None       = 0,
        Titlebar   = 1 << 0,
        Resize     = 1 << 1,
        Close      = 1 << 2,
        Fullscreen = 1 << 3,
        Default = Titlebar | Resize | Close
    };

    struct Color
    {
        union {
            unsigned int full;
            unsigned char rgba[4];
        };
        Color(uint32_t full): full(full) {}
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xff)
        {
            rgba[0] = r;
            rgba[1] = g;
            rgba[2] = b;
            rgba[3] = a;
        }
    };
    enum { // See http://cloford.com/resources/colours/500col.htm for details
        Crimson = 0xffdc143c,
        Lightpink = 0xffffb6c1,
        Pink = 0xffffc0cb,
        Palevioletred = 0xffdb7093,
        Hotpink = 0xffff69b4,
        Raspberry = 0xff872657,
        Mediumvioletred = 0xffc71585,
        Violetred = 0xffd02090,
        Orchid = 0xffda70d6,
        Thistle = 0xffd8bfd8,
        Plum = 0xffdda0dd,
        Violet = 0xffee82ee,
        Purple = 0xff800080,
        Mediumorchid = 0xffba55d3,
        Darkviolet = 0xff9400d3,
        Darkorchid = 0xff9932cc,
        Indigo = 0xff4b0082,
        Blueviolet = 0xff8a2be2,
        Mediumpurple = 0xff9370db,
        Darkslateblue = 0xff483d8b,
        Lightslateblue = 0xff8470ff,
        Mediumslateblue = 0xff7b68ee,
        Slateblue = 0xff6a5acd,
        Ghostwhite = 0xfff8f8ff,
        Lavender = 0xffe6e6fa,
        Blue = 0xff0000ff,
        Navy = 0xff000080,
        Midnightblue = 0xff191970,
        Cobalt = 0xff3d59ab,
        Royalblue = 0xff4169e1,
        Cornflowerblue = 0xff6495ed,
        Lightsteelblue = 0xffb0c4de,
        Lightslategray = 0xff778899,
        Slategray = 0xff708090,
        Aliceblue = 0xfff0f8ff,
        Steelblue = 0xff4682b4,
        Lightskyblue = 0xff87cefa,
        Skyblue = 0xff87ceeb,
        Peacock = 0xff33a1c9,
        Lightblue = 0xffadd8e6,
        Powderblue = 0xffb0e0e6,
        Cadetblue = 0xff5f9ea0,
        Darkturquoise = 0xff00ced1,
        Darkslategray = 0xff2f4f4f,
        Teal = 0xff008080,
        Mediumturquoise = 0xff48d1cc,
        Lightseagreen = 0xff20b2aa,
        Manganeseblue = 0xff03a89e,
        Turquoise = 0xff40e0d0,
        Coldgrey = 0xff808a87,
        Turquoiseblue = 0xff00c78c,
        Mediumspringgreen = 0xff00fa9a,
        Mintcream = 0xfff5fffa,
        Springgreen = 0xff00ff7f,
        Mediumseagreen = 0xff3cb371,
        Emeraldgreen = 0xff00c957,
        Mint = 0xffbdfcc9,
        Cobaltgreen = 0xff3d9140,
        Darkseagreen = 0xff8fbc8f,
        Palegreen = 0xff98fb98,
        Limegreen = 0xff32cd32,
        Forestgreen = 0xff228b22,
        Green = 0xff008000,
        Darkgreen = 0xff006400,
        Sapgreen = 0xff308014,
        Lawngreen = 0xff7cfc00,
        Greenyellow = 0xffadff2f,
        Darkolivegreen = 0xff556b2f,
        Olivedrab = 0xff6b8e23,
        Beige = 0xfff5f5dc,
        Lightgoldenrodyellow = 0xfffafad2,
        Warmgrey = 0xff808069,
        Olive = 0xff808000,
        Darkkhaki = 0xffbdb76b,
        Khaki = 0xfff0e68c,
        Palegoldenrod = 0xffeee8aa,
        Banana = 0xffe3cf57,
        Goldenrod = 0xffdaa520,
        Darkgoldenrod = 0xffb8860b,
        Floralwhite = 0xfffffaf0,
        Oldlace = 0xfffdf5e6,
        Wheat = 0xfff5deb3,
        Moccasin = 0xffffe4b5,
        Papayawhip = 0xffffefd5,
        Blanchedalmond = 0xffffebcd,
        Eggshell = 0xfffce6c9,
        Tan = 0xffd2b48c,
        Brick = 0xff9c661f,
        Cadmiumyellow = 0xffff9912,
        Antiquewhite = 0xfffaebd7,
        Burlywood = 0xffdeb887,
        Melon = 0xffe3a869,
        Carrot = 0xffed9121,
        Darkorange = 0xffff8c00,
        Orange = 0xffff8000,
        Linen = 0xfffaf0e6,
        Sandybrown = 0xfff4a460,
        Rawsienna = 0xffc76114,
        Chocolate = 0xffd2691e,
        Ivoryblack = 0xff292421,
        Flesh = 0xffff7d40,
        Cadmiumorange = 0xffff6103,
        Burntsienna = 0xff8a360f,
        Sienna = 0xffa0522d,
        Coral = 0xffff7f50,
        Sepia = 0xff5e2612,
        Darksalmon = 0xffe9967a,
        Burntumber = 0xff8a3324,
        Salmon = 0xfffa8072,
        Rosybrown = 0xffbc8f8f,
        Lightcoral = 0xfff08080,
        Indianred = 0xffcd5c5c,
        Brown = 0xffa52a2a,
        Firebrick = 0xffb22222,
        Maroon = 0xff800000,
        White = 0xffffffff,
        Gainsboro = 0xffdcdcdc,
        Lightgrey = 0xffd3d3d3,
        Silver = 0xffc0c0c0,
        Darkgray = 0xffa9a9a9,
        Gray = 0xff808080,
        Granite = 0xff1a1a1a,
        Black = 0xff000000
    };

    inline std::ostream &operator << (std::ostream &os, Color const &color)
    {
        os << "[r:" << +color.rgba[2] << "]"
           << "[g:" << +color.rgba[1] << "]"
           << "[b:" << +color.rgba[0] << "]"
           << "[a:" << +color.rgba[3] << "]" << std::endl;
        return os;
    }
}

#endif //FENDER_RENDERING_HPP