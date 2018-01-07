//
// Created by arroganz on 1/1/18.
//

#include <SFML/Window/Event.hpp>
#include "Input.hpp"
#include "inputKeys.hpp"

namespace
{
    std::unordered_map<sf::Keyboard::Key, futils::Keys> sfToFutilsKeys = {
            {sf::Keyboard::Key::A, futils::Keys::A},
            {sf::Keyboard::Key::B, futils::Keys::B},
            {sf::Keyboard::Key::C, futils::Keys::C},
            {sf::Keyboard::Key::D, futils::Keys::D},
            {sf::Keyboard::Key::E, futils::Keys::E},
            {sf::Keyboard::Key::F, futils::Keys::F},
            {sf::Keyboard::Key::G, futils::Keys::G},
            {sf::Keyboard::Key::H, futils::Keys::H},
            {sf::Keyboard::Key::I, futils::Keys::I},
            {sf::Keyboard::Key::J, futils::Keys::J},
            {sf::Keyboard::Key::K, futils::Keys::K},
            {sf::Keyboard::Key::L, futils::Keys::L},
            {sf::Keyboard::Key::M, futils::Keys::M},
            {sf::Keyboard::Key::N, futils::Keys::N},
            {sf::Keyboard::Key::O, futils::Keys::O},
            {sf::Keyboard::Key::P, futils::Keys::P},
            {sf::Keyboard::Key::Q, futils::Keys::Q},
            {sf::Keyboard::Key::R, futils::Keys::R},
            {sf::Keyboard::Key::S, futils::Keys::S},
            {sf::Keyboard::Key::T, futils::Keys::T},
            {sf::Keyboard::Key::U, futils::Keys::U},
            {sf::Keyboard::Key::V, futils::Keys::V},
            {sf::Keyboard::Key::W, futils::Keys::W},
            {sf::Keyboard::Key::X, futils::Keys::X},
            {sf::Keyboard::Key::Y, futils::Keys::Y},
            {sf::Keyboard::Key::Z, futils::Keys::Z},
            {sf::Keyboard::Key::F1, futils::Keys::F1},
            {sf::Keyboard::Key::F2, futils::Keys::F2},
            {sf::Keyboard::Key::F3, futils::Keys::F3},
            {sf::Keyboard::Key::F4, futils::Keys::F4},
            {sf::Keyboard::Key::F5, futils::Keys::F5},
            {sf::Keyboard::Key::F6, futils::Keys::F6},
            {sf::Keyboard::Key::F7, futils::Keys::F7},
            {sf::Keyboard::Key::F8, futils::Keys::F8},
            {sf::Keyboard::Key::F9, futils::Keys::F9},
            {sf::Keyboard::Key::F10, futils::Keys::F10},
            {sf::Keyboard::Key::F11, futils::Keys::F11},
            {sf::Keyboard::Key::F12, futils::Keys::F12},
            {sf::Keyboard::Key::Up, futils::Keys::ArrowUp},
            {sf::Keyboard::Key::Down, futils::Keys::ArrowDown},
            {sf::Keyboard::Key::Left, futils::Keys::ArrowLeft},
            {sf::Keyboard::Key::Right, futils::Keys::ArrowRight},
            {sf::Keyboard::Key::Return, futils::Keys::Return},
            {sf::Keyboard::Key::BackSpace, futils::Keys::Backspace},
            {sf::Keyboard::Key::Space, futils::Keys::Space},
            {sf::Keyboard::Key::Escape, futils::Keys::Escape},
            {sf::Keyboard::Key::Delete, futils::Keys::Delete},
            {sf::Keyboard::Key::Tab, futils::Keys::Tab},
            {sf::Keyboard::Key::LControl, futils::Keys::LCtrl},
            {sf::Keyboard::Key::RControl, futils::Keys::RCtrl},
            {sf::Keyboard::Key::LShift, futils::Keys::LShift},
            {sf::Keyboard::Key::RShift, futils::Keys::RShift},
            {sf::Keyboard::Key::LAlt, futils::Keys::Alt},
            {sf::Keyboard::Key::Num1, futils::Keys::Num1},
            {sf::Keyboard::Key::Num2, futils::Keys::Num2},
            {sf::Keyboard::Key::Num3, futils::Keys::Num3},
            {sf::Keyboard::Key::Num4, futils::Keys::Num4},
            {sf::Keyboard::Key::Num5, futils::Keys::Num5},
            {sf::Keyboard::Key::Num6, futils::Keys::Num6},
            {sf::Keyboard::Key::Num7, futils::Keys::Num7},
            {sf::Keyboard::Key::Num8, futils::Keys::Num8},
            {sf::Keyboard::Key::Num9, futils::Keys::Num9},
            {sf::Keyboard::Key::Num0, futils::Keys::Num0},
            // {sf::Keyboard::Key::C, futils::Keys::Capslock},
            {sf::Keyboard::Key::PageUp, futils::Keys::PageUp},
            {sf::Keyboard::Key::PageDown, futils::Keys::PageDown},
            // {sf::Keyboard::Key::Ampersand, futils::Keys::Ampersand},
            // {sf::Keyboard::Key::Hashtag, futils::Keys::Hashtag},
            {sf::Keyboard::Key::Quote, futils::Keys::Quote},
            // {sf::Keyboard::Key::DoubleQuote, futils::Keys::DoubleQuote},
            {sf::Keyboard::Key::Dash, futils::Keys::Dash},
            // {sf::Keyboard::Key::Underscore, futils::Keys::Underscore},
            // {sf::Keyboard::Key::LParenthesis, futils::Keys::LParenthesis},
            // {sf::Keyboard::Key::RParenthesis, futils::Keys::RParenthesis},
            {sf::Keyboard::Key::LBracket, futils::Keys::LBracket},
            {sf::Keyboard::Key::RBracket, futils::Keys::RBracket},
            // {sf::Keyboard::Key::LSquareBracket, futils::Keys::LSquareBracket},
            // {sf::Keyboard::Key::RSquareBracket, futils::Keys::RSquareBracket},
            // {sf::Keyboard::Key::Colon, futils::Keys::Colon},
            {sf::Keyboard::Key::SemiColon, futils::Keys::SemiColon},
            // {sf::Keyboard::Key::QuestionMark, futils::Keys::QuestionMark},
            // {sf::Keyboard::Key::ExclamationMark, futils::Keys::ExclamationMark},
            {sf::Keyboard::Key::Comma, futils::Keys::Comma},
            // {sf::Keyboard::Key::Dot, futils::Keys::Dot},
            // {sf::Keyboard::Key::Percent, futils::Keys::Percent},
            // {sf::Keyboard::Key::Asterisk, futils::Keys::Asterisk},
            {sf::Keyboard::Key::Slash, futils::Keys::Slash},
            {sf::Keyboard::Key::BackSlash, futils::Keys::BackSlash},
    };

    std::unordered_map<sf::Event::EventType, futils::InputState> sfToFutilsState =
            {
                    {sf::Event::EventType::KeyPressed, futils::InputState::Down},
                    {sf::Event::EventType::KeyReleased, futils::InputState::GoingUp},
                    {sf::Event::EventType::JoystickButtonPressed, futils::InputState::Down},
                    {sf::Event::EventType::JoystickButtonReleased, futils::InputState::GoingUp},
                    {sf::Event::EventType::MouseButtonPressed, futils::InputState::Down},
                    {sf::Event::EventType::MouseButtonReleased, futils::InputState::GoingUp},
            };
}

namespace fender::systems::SFMLSystems
{
    void Input::init()
    {
        __init();
        addReaction<sf::Event>([this](futils::IMediatorPacket &pkg){
            auto &event = futils::Mediator::rebuild<sf::Event>(pkg);
            process(event);
        });
        phase = Run;
    }

    void Input::process(sf::Event const &event)
    {
        if (event.type == sf::Event::KeyPressed)
            events->send<futils::Keys>(sfToFutilsKeys[event.key.code]);
        if (event.type != sf::Event::KeyPressed && event.type != sf::Event::KeyReleased)
            return ;
        // First let's check simple keys, with different states

        auto key = sfToFutilsKeys.at(event.key.code);
        auto state = sfToFutilsState.at(event.type);
        // frameInputs[futils::InputAction(key, state)] = true;
        for (auto &input: entityManager->get<fender::components::Input>())
        {
            if (input->activated)
            {
                for (auto &pair: input->map)
                {
                    auto &sequence = pair.first;
                    auto &func = pair.second;
                    std::size_t count{0};
                    auto size = sequence.actions.size();
                    if (size == 0)
                        continue;
                    for (auto &action: sequence.actions)
                    {
                        if (action.key == key && action.state == state)
                            count++;
                    }
                    if (count == size)
                        func();
                }
            } else
            {

            }
        }
    }

    void Input::checkInputs() {
    }

    void Input::reset()
    {

    }

    void Input::run(float) {
        switch (phase)
        {
            case Init : return init();
            // Run could be something like update all inputs ?
            case Run : return reset();
        }
    }
}