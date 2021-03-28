
#ifndef _MYCXX_UTILS_HPP
#define _MYCXX_UTILS_HPP

#ifdef _WIN32
	#define WILL_NOT_COMPILE(__DEAD_CODE__) {/* __DEAD_CODE__ */}
#else
	#define WILL_NOT_COMPILE(__DEAD_CODE__...) {/* __DEAD_CODE__ */}
#endif

#define EQUALS_STRING(__VALUE1__, __VALUE2__) ((__VALUE1__ == __VALUE2__)? "==": "!=")

#endif // _MYCXX_UTILS_HPP
