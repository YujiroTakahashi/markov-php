#include <string>

#include "markov_api.h"

using namespace croco;

/**
 * get markov version
 *
 * @access public
 * @return int
 */
int MarkovVersion()
{
    return MARKOV_VERSION;
}

/**
 * create a Markov handle
 *
 * @access public
 * @param  const std::string str
 * @param  const int nsize
 * @return MarkovHandle
 */
MarkovHandle MarkovCreate(const char *str, const int nsize)
{
    MarkovHandle handle = new markovchain(std::string(str), nsize);
    return handle;
}

/**
 * free a Markov handle
 *
 * @access public
 * @param  MarkovHandle handle
 * @return void
 */
void MarkovFree(MarkovHandle handle)
{
    delete static_cast<markovchain*>(handle);
}

/**
 * free a char handle
 *
 * @access public
 * @param  char *text
 * @return void
 */
void MarkovFreeText(char *text)
{
    delete[] text;
}

/**
 * fgenerate the text
 *
 * @access public
 * @param  MarkovHandle handle
 * @return char *
 */
char *MarkovGenerate(MarkovHandle handle, const char *start, const int width)
{
    markovchain *textgen = static_cast<markovchain*>(handle);

    std::string result = textgen->generate(std::string(start), width);

    char *text = new char[result.size() + 1];
    strcpy(text, result.c_str());

    return text;
}

/**
 * find key
 *
 * @access public
 * @param  MarkovHandle handle
 * @return char *
 */
int MarkovHas(MarkovHandle handle, const char *key)
{
    markovchain *textgen = static_cast<markovchain*>(handle);

    if (false == textgen->has(std::string(key))) {
        return 0;
    }
    return 1;
}
