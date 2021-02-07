const express = require('express')
const bodyParser = require("body-parser");
const app = express();
const port = 3000;
const path = require('path');
const addon = require('./build/Release/getusersaddon.node');

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})

console.log('=====>', addon);
console.log(addon.getUsers());

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname,'/form.html'))
})

app.post('/form', (req, res) => {
  console.log(req.body)
  res.send(req.body.fname) 
})

module.exports=addon;
