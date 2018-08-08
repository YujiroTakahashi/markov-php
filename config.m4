dnl $Id$
dnl config.m4 for extension markov

PHP_ARG_ENABLE(markov, whether to enable markov support,
  [  --enable-markov           Enable markov support])

if test "$PHP_MARKOV" != "no"; then
  PHP_REQUIRE_CXX()

  PHP_SUBST(MARKOV_SHARED_LIBADD)
  PHP_ADD_LIBRARY(stdc++, 1, MARKOV_SHARED_LIBADD)
  CXXFLAGS="-std=c++11"

  PHP_NEW_EXTENSION(markov, mbstring.cc markovchain.cc markov_api.cc markov.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
