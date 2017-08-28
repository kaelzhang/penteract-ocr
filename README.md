[![Build Status](https://travis-ci.org/kaelzhang/node-penteract.svg?branch=master)](https://travis-ci.org/kaelzhang/node-penteract)
[![Coverage](https://codecov.io/gh/kaelzhang/node-penteract/branch/master/graph/badge.svg)](https://codecov.io/gh/kaelzhang/node-penteract)
<!-- optional appveyor tst
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kaelzhang/node-penteract?branch=master&svg=true)](https://ci.appveyor.com/project/kaelzhang/node-penteract)
-->
<!-- optional npm version
[![NPM version](https://badge.fury.io/js/node-penteract.svg)](http://badge.fury.io/js/node-penteract)
-->
<!-- optional npm downloads
[![npm module downloads per month](http://img.shields.io/npm/dm/node-penteract.svg)](https://www.npmjs.org/package/node-penteract)
-->
<!-- optional dependency status
[![Dependency Status](https://david-dm.org/kaelzhang/node-penteract.svg)](https://david-dm.org/kaelzhang/node-penteract)
-->

# penteract

The native Node.js bindings to the [Tesseract OCR](https://github.com/tesseract-ocr/tesseract) project.

ATTENSION that this package is still Working In Progress, and only support Mac OS X for now.

Contributions are welcome.

## Install

First of all, a g++ 4.9 compiler is required.

Before install `penteract`, the following dependencies should be installed

```sh
$ brew install pkg-config tesseract # mac os
```

Then npm install

```sh
$ npm install penteract
```

### To use with Electron

Due to the limitation of node native modules, if you want to use `penteract` with electron, add a `.npmrc` file to the root of your electron project, before `npm install`:

```ini
runtime = electron
; The version of the local electron,
; use `npm ls electron` to figure it out
target = 1.7.5
target_arch = x64
disturl = https://atom.io/download/atom-shell
```

<!--

### The N-API version of `penteract`

The N-API version of `penteract` (penteract@n-api) is and will be remaining experimental before the feature of N-API stabilized in Node.js 8.0 and ported to older Node.js LTS lines ([via](https://medium.com/the-node-js-collection/n-api-next-generation-node-js-apis-for-native-modules-169af5235b06)).

For now, it is recommended to use `penteract@latest`

-->

## Usage

### Recognize an Image Buffer

```js
import {
  recognize
} from 'penteract'

import fs from 'fs-extra'

const filepath = path.join(__dirname, 'test', 'fixtures', 'penteract.jpg')

fs.readFile(filepath).then(recognize).then(console.log) // 'penteract'
```

### Recognize a Local Image File

```js
import {
  fromFile
} from 'penteract'

fromFile(filepath, {lang: 'eng'}).then(console.log)     // 'penteract'
```

## recognize(image [, options])

- **image** `Buffer` the content buffer of the image file.
- **options** `PenteractOptions=` optional

Returns `Promise.<String>` the recognized text if succeeded.

## fromFile(filepath [, options])

- **filepath** `Path` the file path of the image file.
- **options** `PenteractOptions=`

Returns `Promise.<String>`

### `PenteractOptions` `Object`


```js
{
  // @type `(String|Array.<String>)=eng`,
  //
  // Specifies language(s) used for OCR.
  //   Run `tesseract --list-langs` in command line for all supported languages.
  //   Defaults to `'eng'`.
  //
  // To specify multiple languages, use an array.
  //   English and Simplified Chinese, for example:
  // ```
  // lang: ['eng', 'chi_sim']
  // ```
  lang: 'eng'
}
```

## `Promise.reject(error)`

- **error** `Error` The JavaScript `Error` instance
  - **code** `String` Error code.
  - **message** `String` Error message.
  - other properties of `Error`.

### code: `ERR_READ_IMAGE`

Rejects if it fails to read image data from file or buffer.

### code: `ERR_INIT_TESSER`

Rejects if tesseract fails to initialize

## Example of Using with Electron

```js
// For details of `mainWindow: BrowserWindow`, see
// https://github.com/electron/electron/blob/master/docs/api/browser-window.md
mainWindow.capturePage({
  x: 10,
  y: 10,
  width: 100,
  height: 10

}, (data) => {
  recognize(data.toPNG()).then(console.log)
})
```

## Compiling Troubles

- For Mac OS users, if you are experiencing trouble when compiling, run the following command:

```sh
$ xcode-select --install
```

will resolve most problems.

- Warnings:

```
xcode-select: error: tool 'xcodebuild' requires Xcode, but active developer directory '/Library/Developer/CommandLineTools' is a command line tools instance
```

resolver:

```sh
$ sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
```

## License

MIT
