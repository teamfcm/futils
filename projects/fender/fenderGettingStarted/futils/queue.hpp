//
// Created by arroganz on 1/2/18.
//

#ifndef FENDER_QUEUE_HPP
#define FENDER_QUEUE_HPP

# include <vector>

namespace futils
{
    template <typename T>
    class Queue
    {
        std::vector<T> content;
    public:
        Queue() = default;

        T &front()
        {
            return content.front();
        }

        T &back()
        {
            return content.back();
        }

        void push(T const &val)
        {
            content.push_back(val);
        }

        bool empty()
        {
            return content.empty();
        }

        size_t size()
        {
            return content.size();
        }

        void pop()
        {
            std::vector<T> tmp;
            for (auto it = content.begin() + 1; it != content.end(); it++) {
                tmp.push_back(*it);
            }
            content = tmp;
        }

        bool find(T const &val)
        {
            for (auto &elem: content)
            {
                if (elem == val)
                    return true;
            }
            return false;
        }
    };
};

#endif //FENDER_QUEUE_HPP
