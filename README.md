[![Build Status](https://travis-ci.org/kaelzhang/napi-penteract.svg?branch=master)](https://travis-ci.org/kaelzhang/napi-penteract)
[![Coverage](https://codecov.io/gh/kaelzhang/napi-penteract/branch/master/graph/badge.svg)](https://codecov.io/gh/kaelzhang/napi-penteract)
<!-- optional appveyor tst
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kaelzhang/napi-penteract?branch=master&svg=true)](https://ci.appveyor.com/project/kaelzhang/napi-penteract)
-->
<!-- optional npm version
[![NPM version](https://badge.fury.io/js/napi-penteract.svg)](http://badge.fury.io/js/napi-penteract)
-->
<!-- optional npm downloads
[![npm module downloads per month](http://img.shields.io/npm/dm/napi-penteract.svg)](https://www.npmjs.org/package/napi-penteract)
-->
<!-- optional dependency status
[![Dependency Status](https://david-dm.org/kaelzhang/napi-penteract.svg)](https://david-dm.org/kaelzhang/napi-penteract)
-->

# penteract

The node.js wrapper of Tesseract OCR using N-API.

ATTENSION that this package is still Working In Progress, and

- only support node.js >= 8.3.0 (for the api changes of N-API)
- only support Mac OS X for now. 

## Install

1. Before install node.js penteract, the following dependencies should be installed

```sh
brew install pkg-config tesseract
```

2. Then npm install

```sh
$ npm install penteract
```

## Usage

```js
import penteract from 'penteract'
```

## License

MIT
