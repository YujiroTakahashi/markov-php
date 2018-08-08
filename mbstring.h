#ifndef __CROCO_MBSTRING_H__
#define __CROCO_MBSTRING_H__

#include <stdint.h>

#ifdef __cplusplus

#include <string>
#include <vector>

namespace croco {

class mbstring {
public:
	typedef std::vector<std::string> strs_t;

private:
    strs_t _str;

public:
	mbstring(const std::string str);
    ~mbstring();
    int size();
	int length();
	std::string substr(const int start, const int length);
	void append(const std::string str);
	std::string toString();

private:
	void _apeend(strs_t &words, const std::string str);
}; // class mbstring

} // namespace croco

#endif /* __cplusplus */

#endif // #ifndef __CROCO_MBSTRING_H__
