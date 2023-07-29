#ifndef _BOOST_BOOST_INCLUDE_GUARD_END_HPP
#define _BOOST_BOOST_INCLUDE_GUARD_END_HPP

#ifndef _BOOST_BOOST_INCLUDE_GUARD_START_HPP
    // Guard to remember to add the start before adding an include
    #error Closing unopened BoostIncludeGuard
#endif 

#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif


// removing include guards o that can be included multiple times if needed
#undef _BOOST_BOOST_INCLUDE_GUARD_START_HPP
#undef _BOOST_BOOST_INCLUDE_GUARD_END_HPP

#endif // _BOOST_BOOST_INCLUDE_GUARD_END_HPP
