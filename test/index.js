import test from 'ava'
import {
  fromFile,
  recognize
} from '../src'
import path from 'path'
import fs from 'fs-extra'


const fixtures = file => path.join(__dirname, 'fixtures', file)
const removes_ending = string => string.replace(/\n+$/, '')

test('fromFile', async t => {
  const result = await fromFile(fixtures('penteract.jpg'))
  t.is(removes_ending(result), 'penteract')
})


test('recognize', async t => {
  const buffer = await fs.readFile(fixtures('penteract.jpg'))
  const result = await recognize(buffer)
  t.is(removes_ending(result), 'penteract')
})
