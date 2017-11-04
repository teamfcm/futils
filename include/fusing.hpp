//
// Created by ganz on 04/11/17.
//

#ifndef FUTILS_FUSING_HPP_HPP
#define FUTILS_FUSING_HPP_HPP

# include <functional>

namespace futils {
    using voidFunc = std::function<void(void)>;
    using voidStringFunc = std::function<void(std::string const &)>;
    template        <typename __Key, typename __ValueType>
    using umap = std::unordered_map<__Key, __ValueType>;
}

#endif //FUTILS_FUSING_HPP_HPP
