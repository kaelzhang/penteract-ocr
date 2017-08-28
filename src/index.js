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


const makePromise = (method) => {
  return (arg, options) => new Promise((resolve, reject) => {
    options = handleOptions(options)

    bindings[method](arg, options.lang, (err, text) => {
      if (err) {
        const error = new Error(text)
        error.code = err
        return reject(error)
      }

      resolve(text.trim())
    })
  })
}

export const fromFile = makePromise('fromFile')
export const recognize = makePromise('recognize')
