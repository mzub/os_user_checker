const express = require('express')
const bodyParser = require("body-parser");
const app = express();
const port = 3000;
const path = require('path');
const addon = require('./build/Release/getusersaddon.node');

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname,'/html/form.html'))
})

app.post('/form', (req, res) => {
  if (addon.getUsers().find((userName)=> userName == req.body.username)) {
    res.sendFile(path.join(__dirname,'/html/searchsuccess.html'))
  } else {
    res.sendFile(path.join(__dirname,'/html/usernotfound.html'))
  } 
})

module.exports=addon;
