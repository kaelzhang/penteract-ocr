const os = require('os')
const command = process.argv[2]

if (command === 'platform') {
  console.log(os.platform())
  process.exit()
}
