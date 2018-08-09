#include "mbstring.h"

namespace croco {

/**
 * コンストラクタ
 *
 * @access public
 * @param  const std::string str
 */
mbstring::mbstring(const std::string str)
{
	_str.clear();
	_apeend(_str, str);
}

/**
 * デストラクタ
 *
 * @access public
 */
mbstring::~mbstring()
{
	_str.clear();
}

/**
 * 文字数の取得
 *
 * @access public
 * @return int
 */
int mbstring::size()
{
	std::size_t size = _str.size();
	return static_cast<int>(size);
}

/**
 * 文字数の取得
 *
 * @access public
 * @return int
 */
int mbstring::length()
{
	std::size_t size = _str.size();
	return static_cast<int>(size);
}

/**
 * 指定範囲の文字取得
 *
 * @access public
 * @param  const int start
 * @param  const int length
 * @return std::string
 */
std::string mbstring::substr(const int start, const int length)
{
	std::string result("");
	int idx = start;
	int max = start + length;
	std::size_t size = _str.size();
	int len = static_cast<int>(size);

	max = (len < max)? len : max;
	idx = (len < idx)? len : idx;

	max = (max < 0)? 0 : max;
	idx = (idx < 0)? 0 : idx;

	for (; idx < max; idx++) {
		result.append(_str.at(idx));
	}

	return result;
}

/**
 * 指定範囲の文字取得
 *
 * @access public
 * @param  const std::string str
 * @return void
 */
void mbstring::append(const std::string str)
{
	_apeend(_str, str);
}

/**
 * 文字列に変換
 *
 * @access public
 * @return std::string
 */
std::string mbstring::toString()
{
	return substr(0, _str.size());
}

/**
 * 文字列分割
 *
 * @access private
 * @param  mbstring::strs_t &words
 * @param  const std::string str
 * @return strs_t
 */
void mbstring::_apeend(mbstring::strs_t &words, const std::string str)
{
    std::size_t sz = str.size();
    for (std::size_t idx = 0; idx < sz;) {
        uint8_t c_hex = static_cast<uint8_t>(str[idx]);
        if ('\n' == str[idx] || ' ' == str[idx]) {
			words.push_back(str.substr(idx, 1));
            idx += 1;
        } else if (c_hex < 0x80) {
			words.push_back(str.substr(idx, 1));
            idx += 1;
        } else if (c_hex < 0xE0) {
			words.push_back(str.substr(idx, 2));
            idx += 2;
        } else if (c_hex < 0xF0) {
			words.push_back(str.substr(idx, 3));
            idx += 3;
        } else {
			words.push_back(str.substr(idx, 4));
            idx += 4;
        }
    }
}

} // namespace croco
