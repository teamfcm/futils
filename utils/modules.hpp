//
// Created by arroganz on 11/30/17.
//

#ifndef FENDER_MODULES_HPP
#define FENDER_MODULES_HPP

# include "types.hpp"

namespace futils
{
    class Modules
    {
        template <typename Key, typename Val>
        using container = std::unordered_map<Key, Val>;
        using key = std::string;
        using value = futils::Action;

        container<key, value> _modules;
        std::queue<key> _toRemove;
        void cleanup() {
            while (!_toRemove.empty()) {
                _modules.erase(_toRemove.front());
                _toRemove.pop();
            }
        }
    public:
        Modules() = default;
        void add(key k, value val) {
			_modules.insert(std::pair <key, value> (k, val));
        }

        void execute() {
            for (auto &pair: _modules) {
                auto &mod = pair.second;
                mod();
            }
            cleanup();
        }

        void remove(key k) {
            _toRemove.push(k);
        }
    };
}

#endif //FENDER_MODULES_HPP
