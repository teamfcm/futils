//
// Created by arroganz on 12/3/17.
//

#ifndef FENDER_CUSTOMTRAITS_HPP
#define FENDER_CUSTOMTRAITS_HPP

namespace futils
{
    template <typename T>
    struct _has_no_fields_ {
        struct helper_ : T { int x; };
        static bool const value = sizeof(helper_) == sizeof(int);
    };
}

#endif //FENDER_CUSTOMTRAITS_HPP
