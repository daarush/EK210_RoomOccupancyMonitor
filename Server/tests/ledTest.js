const express = require('express');
const path = require('path');
const bluetoothSerial = require('bluetooth-serial-port'); // Include Bluetooth serial library
const btSerial = new bluetoothSerial.BluetoothSerialPort();

const app = express();
const PORT = 3000;
const btModuleName = 'HC-05'; // Replace with the name of your Bluetooth module

// Serve static files (HTML, JavaScript, CSS)
app.use(express.static('public'));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/LEDindex.html');
});

// Function to send data over Bluetooth
function sendBluetoothData(color) {
    const data = Buffer.from(`${color}\n`);
    btSerial.write(data, (err) => {
        if (err) {
            console.error(`Error sending ${color}:`, err);
        } else {
            console.log(`Sent ${color} successfully.`);
        }
    });
}

// Route to handle color commands from the buttons
app.post('/send-color', express.json(), (req, res) => {
    const { color } = req.body;
    if (color === 'red' || color === 'green' || color === 'blue') {
        sendBluetoothData(color);
        res.status(200).send(`Sent ${color}`);
    } else {
        res.status(400).send('Invalid color');
    }
});

// Callback function to handle data received from the Bluetooth device
btSerial.on('data', (bufferData) => {
    const dataString = Buffer.from(bufferData).toString();
    console.log('Received data from Bluetooth device:', dataString);
    // Handle the received data as needed
});

// Function to connect to the Bluetooth device
function connectToBluetoothDevice() {
    // Scan for Bluetooth devices and find the desired device
    btSerial.on('found', (address, name) => {
        if (name.toLowerCase().includes(btModuleName.toLowerCase())) {
            btSerial.findSerialPortChannel(address, (channel) => {
                // Connect to the Bluetooth device
                btSerial.connect(address, channel, () => {
                    console.log('Connected to Bluetooth device:', name);
                }, (err) => {
                    console.error('Failed to connect:', err);
                });
            }, (err) => {
                console.error('Error finding channel:', err);
            });
        } else {
            console.log('Found device:', name, 'but not connecting.');
        }
    });

    // Start scanning for devices
    btSerial.inquire();
}

// Connect to the Bluetooth device when the server starts
connectToBluetoothDevice();

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
