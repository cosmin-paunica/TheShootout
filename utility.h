#pragma once

// Conform http://www.cplusplus.com/doc/oldtutorial/templates/, am scris implementarile functiilor template direct in header

template <class T>
T max(T a, T b) {
	return a > b ? a : b;
}

template <class T>
T min(T a, T b) {
	return a < b ? a : b;
}
