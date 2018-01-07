//
// Created by arroganz on 1/1/18.
//

#pragma once

# include <vector>
# include <string>
# include <sstream>
# include "math.hpp"

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

    enum class Keys : int {
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

    struct InputAction
    {
        Keys key;
        InputState state;
        InputAction() = default;
        InputAction(Keys key, InputState state): key(key), state(state) {}
        bool operator==(const InputAction &other) const
        {
            return key == other.key && state == other.state;
        }
    };

    struct InputSequence
    {
        std::vector<InputAction> actions;

        bool operator==(const InputSequence &other) const
        {
            if (actions.size() != other.actions.size())
                return true;
            std::size_t index{0};
            for (;index < actions.size();index++)
            {
                auto &k1 = actions[index];
                auto &k2 = other.actions[index];
                if (k1.key != k2.key || k1.state != k2.state)
                    return false;
            }
            return true;
        }
    };
}

namespace std {
    template <>
    struct hash<futils::InputSequence>
    {
        using Key = futils::InputSequence;
        std::size_t operator()(const Key& k) const
        {
            std::string tmp;
            for (auto &a : k.actions)
            {
                tmp += std::to_string(futils::pairingFunction((int)a.key, (int)a.state));
            }
            std::stringstream sstream(tmp);
            std::size_t result;
            sstream >> result;
            return result;
        }
    };

    template <>
    struct hash<futils::InputAction>
    {
        using Key = futils::InputAction;
        std::size_t operator()(const Key& k) const {
            return (size_t)futils::pairingFunction((int)k.key, (int)k.state);
        }
    };
}
