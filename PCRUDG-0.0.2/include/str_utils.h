#ifndef STR_UTILS_H
	#define STR_UTILS_H
/*
 *  Standard Libraries
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>

/*
 *  3rd Party Libraries
*/


/*
 *  Local Libraries
*/


/*
    MACRO
*/

// http://stackoverflow.com/questions/7276826/c-format-number-with-commas
template <class T>
std::string formatNumber(T value)	{
	std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

#endif