{
  'variables': {
    'platform%': '<!(node ./install/os.js platform)'
  },
  'targets': [
    {
      'target_name': 'penteract',
      'sources': [
        'cc/penteract.cc',
        'cc/ocr.cc',
        'cc/fromFile.cc',
        'cc/recognize.cc'
      ],
      'conditions': [
        ['platform=="darwin"', {
          'include_dirs': [
            '<!(node -e "require(\'nan\')")',
            '<!@(pkg-config tesseract --cflags-only-I | sed s/-I//g)'
          ],
          'libraries': [
            '<!@(pkg-config tesseract --libs)'
          ]
        }, {
          'include_dirs': [
            '<!(node -e "require(\'nan\')")',
            '<!(echo $PENTERACT_TESSERACT_PATH)',
            '<!(echo $PENTERACT_TESSERACT_PATH)'
          ],
          'libraries': [
            '<!@(pkg-config tesseract --libs)'
          ]
        }]
      ],
      'dependencies': [],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      }
    }
  ]
}
