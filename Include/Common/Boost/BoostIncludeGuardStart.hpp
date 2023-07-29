#ifndef _BOOST_BOOST_INCLUDE_GUARD_START_HPP
#define _BOOST_BOOST_INCLUDE_GUARD_START_HPP

// Compiler dependent option. there is no need to add unsupported compiler since they will presumably fail.
#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    #pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
    #pragma GCC diagnostic ignored "-Wuseless-cast"
    #pragma GCC diagnostic ignored "-Wsuggest-override"
    #pragma GCC diagnostic ignored "-Wold-style-cast" // boost::url use them
    #pragma GCC diagnostic ignored "-Wpedantic"       // boost::url has some issue
#endif

#endif // _BOOST_BOOST_INCLUDE_GUARD_START_HPP