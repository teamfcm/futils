//
// Created by arroganz on 1/2/18.
//

#ifndef DEMO_NAMEDMAPS_HPP
#define DEMO_NAMEDMAPS_HPP

#include <unordered_map>
#include <vector>
#include <string>

template <typename Key, typename Val>
class NamedMap
{
    using Map = std::unordered_map<Key, Val>;
    std::string name;
    Map map;
public:
    NamedMap(std::string const &name): name(name)
    {

    }

    std::string const &getName() const
    {
        return name;
    }

    Map &get()
    {
        return map;
    }

    bool contains(Key k)
    {
        return map.find(k) != map.end();
    }

    void add(Key k, Val v)
    {
        map.insert(std::pair<Key, Val>(k, v));
    }

    Val &at(Key k)
    {
        return map.at(k);
    }
};

#endif //DEMO_NAMEDMAPS_HPP
