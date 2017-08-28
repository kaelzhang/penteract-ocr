import test from 'ava'
import {
  fromFile,
  recognize
} from '../src'
import path from 'path'
import fs from 'fs-extra'


const fixtures = file => path.join(__dirname, 'fixtures', file)

test('fromFile', async t => {
  const result = await fromFile(fixtures('penteract.jpg'))
  t.is(result, 'penteract')
})


test('recognize', async t => {
  const buffer = await fs.readFile(fixtures('penteract.jpg'))
  const result = await recognize(buffer)
  t.is(result, 'penteract')
})
