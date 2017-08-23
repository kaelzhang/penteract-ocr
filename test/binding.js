import test from 'ava'
import penteract from '..'

test('basic', async t => {
  t.is(penteract.hello(), 'world')
})
