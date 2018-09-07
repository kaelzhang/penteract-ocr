## APIs of JavaScript Bindings

ref: [https://github.com/tesseract-ocr/tesseract/blob/master/api/baseapi.h](https://github.com/tesseract-ocr/tesseract/blob/master/api/baseapi.h)

```js
const tess = new TessBaseAPI()

tess.Version()

tess.SetVariable(name, value)

// success: 0
// failure: -1
tess.Init()

tess.SetImage(buffer)

tess.SetRectangle(x, y, w, h)

tess.Recognize()

tess.GetUTF8Text()

tess.Clear()

tess.End()
```
