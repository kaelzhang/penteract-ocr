import test from 'ava'
import penteract from '../src/binding'
import path from 'path'
import fs from 'fs-extra'


const fixtures = file => path.join(__dirname, 'fixtures', file)
const removes_ending = string => string.replace(/\n+$/, '')

test('fromFile', async t => {
  const result = penteract.fromFile(fixtures('penteract.jpg'), 'eng')
  t.is(removes_ending(result), 'penteract')
})


test('recognize', async t => {
  const buffer = await fs.readFile(fixtures('penteract.jpg'))
  const result = penteract.recognize(buffer, 'eng')
  t.is(removes_ending(result), 'penteract')
})
