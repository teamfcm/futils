//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_COMPONENTS_HPP
#define FENDER_COMPONENTS_HPP

# include "fender.hpp"

namespace fender::components {
    // Need to move all that data into components
    enum class  State : int
    {
        Undefined,
        Up,
        Down,
        GoingUp,
        GoingDown,
    };
    enum class  Input : int
    {
        Undefined = 0,
        A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
        Return, Backspace, Space, Escape, Delete, Tab,
        LCtrl, RCtrl, LShift, RShift, Alt,
        Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,
        Capslock, PageUp, PageDown,
        Ampersand, Hashtag, Quote, DoubleQuote, Dash, Underscore,
        LParenthesis, RParenthesis, LBracket, RBracket, LSquareBracket, RSquareBracket,
        Colon, SemiColon, QuestionMark, ExclamationMark, Comma, Dot, Percent, Asterisk,
        Slash, BackSlash,
        LButton, RButton, MouseWheelUp, MouseWheelDown, MouseWheelButton,
        NBR_SUPPORTED_KEYS
    };
    union color {
        int full;
        unsigned char rgba[4];
    };
    enum class Color : unsigned long
    {
        WHITE = 0xffffffff,
        RED = 0xff000000,
        GREEN = 0x00ff0000,
        BLUE = 0x0000ff00,
    };
    struct      Command
    {
        Input   key{Input::Undefined};
        State   state{State::GoingDown};
        bool    operator == (Command const &other)
        {
            return other.key == this->key && other.state == this->state;
        }
    };
    struct      Border
    {
        int             width{0};
        fender::Color   color{fender::Color::WHITE};
    };
    enum class  WindowStyle
    {
        BORDERLESS,
        NORMAL,
        FULLSCREEN
    };
    enum class  Align
    {
        LEFT,
        CENTER,
        RIGHT,
        TOP,
        BOTTOM
    };
}

#endif //FENDER_COMPONENTS_HPP
