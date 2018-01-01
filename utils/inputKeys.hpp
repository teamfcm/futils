//
// Created by arroganz on 1/1/18.
//

#ifndef FENDER_INPUTKEYS_HPP
#define FENDER_INPUTKEYS_HPP

namespace futils {
    enum class EventType
    {
        Closed, Resized,
        LostFocus, GainedFocus,
        TextEntered,
        KeyPressed, KeyReleased,
        MouseWheelMoved,
        MouseWheelScrolled, MouseButtonPressed, MouseButtonReleased,
        MouseMoved, MouseEntered, MouseLeft,
        JoystickButtonPressed, JoystickButtonReleased,
        JoystickMoved, JoystickConnected, JoystickDisconnected, TouchBegan,
        TouchMoved, TouchEnded,
        SensorChanged,
        Count
    };

    enum class InputState : int {
        Undefined,
        Up,
        Down,
        GoingUp,
        GoingDown,
    };

    enum class Input : int {
        Undefined = 0,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
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
}
#endif //FENDER_INPUTKEYS_HPP
