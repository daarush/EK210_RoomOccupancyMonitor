const express = require('express');
const app = express();
const path = require('path');
const {SerialPort} = require('serialport');

const port =  new SerialPort({path: 'COM3', baudRate: 9600});

const staticDir = path.join(__dirname, 'public');
app.use(express.static(staticDir));

app.get('/sensor', (req, res) => {
    port.on('readable', function () {
      const data = port.read().toString();
      res.send(data);
      console.log(data);
    });
  });
  
  app.listen(4000, () => {
    console.log('Server is running on port 3000');
  });