# Developers' Draft

## Design Principle

- Async
- APIs should be JavaScript-ify
- Use Pix, no exceptions

## Duty

- core binding:
  - tesseract ocr -> javascript
  - async

- JavaScript wrapper:
  - handle lifecycle, prevent tesseract from messing old and new data

## The Design of C++ Tesseract

- An image is re-usable for multiple calls to SetRectangle, ...

## APIs of binding

```js
const core = new PenteractCore()
```
