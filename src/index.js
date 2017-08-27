import bindings from '../build/Release/penteract'


const DEFAULT_LANG = 'eng'
const LANG_DELIMITER = '+'

const handleOptions = ({
  lang = DEFAULT_LANG
} = {}) => {

  if (Array.isArray(lang)) {
    lang = lang.join(LANG_DELIMITER)
  }

  return {
    lang
  }
}

export function fromFile (filepath, options) {
  options = handleOptions(options)

  return bindings.fromFile(filepath, options.lang)
}


export function recognize (buffer, options) {
  options = handleOptions(options)

  try {
    const result = bindings.recognize(buffer, options.lang)
    return Promise.resolve(result)
  } catch (e) {
    return Promise.reject(e)
  }
}
