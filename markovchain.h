#ifndef __CROCO_MARKOV_H__
#define __CROCO_MARKOV_H__

#ifdef __cplusplus

#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>

namespace croco {

class markovchain {
public:
	typedef std::unordered_map<std::string, std::vector<std::string>> table_t;

private:
    table_t _ngrams;
	int _nsize;
	int _width;

public:
	markovchain(const std::string str, const int nsize);
	std::string generate(const std::string start, const int width);
	bool has(const std::string key);
}; // class markovchain

} // namespace croco

#endif /* __cplusplus */

#endif // #ifndef __CROCO_MARKOV_H__
