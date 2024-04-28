// Website used: https://www.hackster.io/leevinentwilson/bluetooth-node-and-arduino-de822e

const express = require('express');
const path = require('path');
const bluetoothSerial = require('bluetooth-serial-port'); // Include Bluetooth serial library
const btSerial = new bluetoothSerial.BluetoothSerialPort();
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8080 });

const app = express();
const PORT = 3000;
const btModuleName = 'HC-05'; 

app.use(express.static(path.join(__dirname, 'public'))); 

// Function to send data over Bluetooth
function sendBluetoothData(d) {
    const data = Buffer.from(`${d}\n`);
    btSerial.write(data, (err) => {
        if (err) {
            console.error(`Error sending ${d}:`, err);
        } else {
            console.log(`Sent ${d} successfully.`);
        }
    });
}

// Route to handle color commands from the buttons
app.post('/changeOccupancy', express.json(), (req, res) => {
    const { occupancy } = req.body;
    sendBluetoothData(occupancy);
    res.status(200).send(`Sent ${occupancy}`);
});

// Callback function to handle data received from the Bluetooth device
btSerial.on('data', (bufferData) => {
    const dataString = Buffer.from(bufferData).toString();
    console.log('Received data from Bluetooth device:', dataString);

    try {
        const data = JSON.parse(dataString);
        wss.clients.forEach((client) => {
            if (client.readyState === WebSocket.OPEN) {
                console.log('Sending data to WebSocket clients:', data);
                client.send(JSON.stringify(data));
            }
        });
    } catch (err) {
        console.error('Error parsing data:', err);
    }
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
