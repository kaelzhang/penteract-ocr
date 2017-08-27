import bindings from './binding'


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

export function fromFileSync (filepath, options) {
  options = handleOptions(options)

  return bindings.fromFileSync(filepath, options.lang)
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
