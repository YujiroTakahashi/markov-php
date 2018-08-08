#ifdef __cplusplus
#include <iostream>
#include "mbstring.h"
#include "markovchain.h"

namespace croco {

/**
 * コンストラクタ
 *
 * @access public
 * @param  const std::string str
 * @param  int nsize
 */
markovchain::markovchain(const std::string str, int nsize)
{
	std::string ngram;
	croco::mbstring mbstr(str);

	_nsize = nsize;
	for (int idx = 0; idx < (mbstr.size() - _nsize - 1); idx++) {
		ngram = mbstr.substr(idx, _nsize);
		_ngrams[ngram].push_back(mbstr.substr(idx + _nsize, 1));
	}
	_width = mbstr.size();
}

/**
 * 文字列分割
 *
 * @access public
 * @param  const std::string start
 * @param  const int width
 * @return std::string
 */
std::string markovchain::generate(const std::string start, const int width)
{
	srand(time(NULL));

	croco::mbstring mbstr(start);
	std::string 	currentNgram = mbstr.substr(0, _nsize);
	croco::mbstring result(currentNgram);
	int max = (_width < width) ? _width : width;

	for (int idx = 0; idx < max; idx++) {
		std::vector<std::string> poss = _ngrams[currentNgram];

		if (poss.size() == 0) {
			poss.push_back("");
		}

		int randNum = (rand() % (poss.size()));
		result.append(poss[randNum]);
		currentNgram = result.substr(result.size() - _nsize, _nsize);
	}

	return result.toString();
}

/**
 * キーが存在するか確認
 *
 * @access public
 * @param  const std::string key
 * @param  const int width
 * @return boolean
 */
bool markovchain::has(const std::string key)
{
	croco::mbstring mbstr(key);
	std::string 	target = mbstr.substr(0, _nsize);


	return (_ngrams.find(target) != _ngrams.end());
}

} // namespace croco

#endif /* __cplusplus */
