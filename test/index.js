import test from 'ava'
import {
  fromFile,
  recognize
} from '../src'
import path from 'path'
import fs from 'fs-extra'


const fixtures = file => path.join(__dirname, 'fixtures', file)

const penteract_jpg = fixtures('penteract.jpg')
const non_existing = fixtures('non-existing.jpg')

const test_read_error = (t, e, fn) => {
  t.is(e.code, 'ERR_READ_IMAGE', 'error code not match')
  t.is(e.message, 'Fails to read image.', 'error message not match')
}

test('fromFile', async t => {
  const result = await fromFile(penteract_jpg)
  t.is(result, 'penteract')
})

test('fromFile: fails to load image', async t => {
  try {
    await fromFile(non_existing)
  } catch (e) {
    test_read_error(t, e)
    return
  }

  t.fail()
})


test('recognize', async t => {
  const buffer = await fs.readFile(penteract_jpg)
  const result = await recognize(buffer)
  t.is(result, 'penteract')
})


test('recognize, multiple languages', async t => {
  const buffer = await fs.readFile(penteract_jpg)
  const result = await recognize(buffer, {
    lang: [
      'eng',
      'chi_sim'
    ]
  })
  t.is(result, 'penteract')
})
