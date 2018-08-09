# markov-php

[Markov chain](https://github.com/hay/markov) PHP Markov chain text generator.

## Building Markov chain for PHP

```
$ cd markov-php
$ phpize
$ ./configure
$ make
$ sudo make install
```

edit your php.ini and add:

```
extension=markov.so
```

## Class synopsis

```php
markov {
    public __construct ( streing dic-text [, int nsize] )
    public streing generate ( streing start [, int width] )
}
```

## Table of Contents

[fastText::__construct](#__construct)
[fastText::generate](#generate)

-----

### <a name="__construct">markov::__construct()

Instantiates a markov object.

```php
$dic =
    "結果的に生き物を殺すにも拘わらず、嬉々として捕獲に励むチビッ子たち……。".
    "テレビ東京の人気番組緊急SOS池の水ぜんぶ抜く大作戦では、外来種=悪と決めつけ、生き物をバケツに放り込むシーンが度々、登場。".
    "まるで地獄絵図のような光景には、専門家も首を傾げるのである。";
$txtgen = new markov($dic, 4);
```

-----

### <a name="generate">streing markov::generate($start, $width)

Generate text.

```php
$txtgen->generate("作戦", 30);
```
```
作戦では、専門家も首を傾げるのである。
```
-----
