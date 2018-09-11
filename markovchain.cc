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
	croco::mbstring mbstr(str);

	_nsize = nsize;
	for (int idx = 0; idx < (mbstr.size() - _nsize - 1); idx++) {
		std::string ngram  = mbstr.substr(idx, _nsize);
		std::string target = mbstr.substr(idx + _nsize, 1);

		if (_ngrams[ngram].find(target) != _ngrams[ngram].end()) {
			_ngrams[ngram][target]++;
		} else {
			_ngrams[ngram][target] = 1;
		}
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

	std::string currentNgram;

	if (has(start)) {
		croco::mbstring mbstr(start);
		currentNgram = mbstr.substr(0, _nsize);
	} else {
		currentNgram = _firstPick();
	}
	croco::mbstring result(currentNgram);
	int max = (_width < width) ? _width : width;

	for (int idx = 0; idx < max; idx++) {
		std::string pickup = _weightedPick(_ngrams[currentNgram]);
		result.append(pickup);
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

/**
 * 重み付けによる文字列取得
 *
 * @access prviate
 * @param  const markovchain::weights_t weights
 * @return std::string
 */
std::string markovchain::_weightedPick(const markovchain::weights_t weights)
{
	int total = 0;
	for (auto &weight : weights) {
		total += weight.second;
	}

	std::string pickup("");
	int rnd = rand() % total;

	for (auto &weight : weights) {
		if (rnd < weight.second) {
			pickup = weight.first;
			break;
		}
		rnd -= weight.second;
	}

	return pickup;
}

/**
 * 初期文字の取得
 *
 * @access prviate
 * @return std::string
 */
std::string markovchain::_firstPick()
{
	int total = 0;
	for (auto &weight : _ngrams) {
		total += weight.second.size();
	}

	std::string pickup("なんもねー");
	int rnd = rand() % total;

	for (auto &weight : _ngrams) {
		if (rnd < weight.second.size()) {
			pickup = weight.first;
			break;
		}
		rnd -= weight.second.size();
	}

	return pickup;
}


} // namespace croco
