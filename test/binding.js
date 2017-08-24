import test from 'ava'
import penteract from '..'
import path from 'path'


const fixtures = file => path.join(__dirname, 'fixtures', file)
const removes_ending = string => string.replace(/\n+$/, '')

test('basic', async t => {
  const result = penteract.fromFile(fixtures('penteract.jpg'), 'eng')
  t.is(removes_ending(result), 'penteract')
})
