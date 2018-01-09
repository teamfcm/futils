//
// Created by arroganz on 11/28/17.
//

#ifndef DEMO_MEDIATOR_HPP
#define DEMO_MEDIATOR_HPP

# include <functional>
# include <utility>
# include "datapacket.hpp"
#include "ini.hpp"

namespace futils
{
    class Mediator
    {
        using reaction = std::function<void(futils::IMediatorPacket &)>;
        struct IdentifiedAction {
            IdentifiedAction(void *callee, reaction func):
                    owner(callee), action(func)
            {

            }

            void *owner;
            reaction action;
            // TODO: Use multimap erase instead..
            bool up{true};
        };
        std::unordered_multimap<futils::type_index, IdentifiedAction> _requests;
    public:
        template <typename T>
        static inline const T &rebuild(IMediatorPacket &pkg) {
            auto ptr = dynamic_cast<AMediatorPacket<T> *>(&pkg);
            if (!ptr)
                throw std::logic_error("Failed to rebuild type from MediatorPacket");
            return ptr->get();
        }

        Mediator() = default;

        template <typename T>
        void send(T &&data = T()) {
            auto range = _requests.equal_range(futils::type<T>::index);
            auto packet = futils::AMediatorPacket<T>(std::forward<T>(data));

            for (auto it = range.first; it != range.second; it++) {
                auto &identifiedAction = it->second;
                if (identifiedAction.up) {
                    identifiedAction.action(packet);
                }
            }
        }

        template <typename T>
        void send (T const &data) {
            auto range = _requests.equal_range(futils::type<T>::index);
            auto packet = futils::AMediatorPacket<T>(data);

            for (auto it = range.first; it != range.second; it++) {
                auto &identifiedAction = it->second;
                if (identifiedAction.up) {
                    identifiedAction.action(packet);
                }
            }
        }

        template <typename T>
        void require(void *callee, std::function<void(futils::IMediatorPacket &)> onReceive) {
            _requests.insert(std::pair<futils::type_index, IdentifiedAction>
				(futils::type<T>::index, IdentifiedAction(callee, onReceive)));
        }

        template <typename T>
        void forget(void *callee) {
            auto range = _requests.equal_range(futils::type<T>::index);
            for (auto it = range.first;
                 it != range.second;
                 it++) {
                *it.up = false;
            }
        }

        void erase(void *callee)
        {
            std::vector<std::unordered_multimap<futils::type_index, IdentifiedAction>::iterator> toDelete;

            for (auto it = _requests.begin(); it != _requests.end(); it++) {
                auto &action = (it)->second;
                if (action.owner == callee)
                    toDelete.push_back(it);
            }
            for (auto &elem : toDelete)
                _requests.erase(elem);
        }
    };
}

#endif //DEMO_MEDIATOR_HPP
