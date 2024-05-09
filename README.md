Introduction
--
This project was inspired by my [311 Project](https://github.com/HudsonReynolds2/ID-Finder)!

This project is for my engineering class where the "our goal is to develop a minimal-impact system that monitors classroom occupancy, prevents entry once maximum capacity is reached, and reduces the risk of overcrowding for students and teachers."

The basic idea was to use Arduino code only, but since we want to make it unique and accessible, we decided to make it, so the user can view the information displayed on their internet device. We had a lot of fun creating this device, and me, who is the lead coder had most fun creating the connection between the Arduino and the website.

Components
--
- **Arduino:** the brain.
- **Two IR Distance Sensors:** to measure the distance and report back the findings.
- **HC-05 Bluetooth Module:** to communicate between the Arduino and the server.
- **DC Motor:** to control the physical movement for an apparatus which blocks the doorway once the max occupancy is reached.

Testing
--
To get the whole project working and synchronized, first I tested every component on its own, hence the many folders and files in the directory.
1. Testing the sensors and how they work, this also includes calibrating them since different models have different conversions
2. Next was the motor, since the DC motor we used for the project was not Arduino compatible, we implemented a MOSFET to allow the communication between the motor and Arduino
3. After getting the main components, then the Bluetooth testing began
    1. Establishing a connection between a NodeJS server and the Arduino
    2. sending and receiving information between the Arduino and server
    3. updating the components on both ends
Although it sounds simple stuff, it took a lot of time and exploring since this topic was new. 

Basic Testing
--
Website used as a reference: [Bluetooth, Node and Arduino](https://www.hackster.io/leevinentwilson/bluetooth-node-and-arduino-de822e) <br />
Check out other test codes as well!

For basic testing purposes, I made a circuit to see if I can change a color of a RGB LED using a website. Instructions on how I did it:
An example ciruit: 

**Note**: you may have a different model, and therefore may not have the exact circuit.
![image](https://github.com/daarush/EK210_RoomOccupancyMonitor/assets/30423986/ba3c8d16-f996-490d-a630-b6168531646c)

Using the circuit, I then implemented the following code found in [LED_withBluetoothTest.ino](TestCodes/LED_withBluetoothTest/LED_withBluetoothTest.ino) on the physical side:
For the website side, although a rudimentary design, it sends the commands to the Arduino; the code is in [ledTest.js](Server/tests/ledTest.js). Now you got a simple website that can change the color of the Arduino. 

<br />

**To open the Website:**
- If you want to open up the website on the device you are hosting the server, type in "localhost:3000/". Replace 3000 with the PORT number if you changed it. For example in the ledTest.js, line 7: `const PORT = 3000;`, 3000 is the port that is being used.
- If you want to open it up on another device
    1. Find the IP address the server is hosted in. If you are hosting through a Windows computer: go to the command prompt and type in `ipconfig`. IPv4 is the IP address.
    2. Make sure to connect to the **same wifi** of the server being hosted in.
    3. In the URL bar type in: "IPv4:3000", replacing IPv4 with the IP address, and 3000 with the correct PORT number.

<br />

**Possible Issues:**
- Imperfect pairing of Arduino and server
    - May need to disconnect other bluetooth devices
- RGB LED not hooked up correctly
- RX and TX pins have different functionality for each model
    - I use an Arduino UNO R3, meaning that it has limited capability of RX and TX pins. To elaborate, the UNO R3 can only manage one communication and is usually plugged into a computer which is the RX and TX communication lies. To make a work around, you treat the communication wires as a digital input, so it does not interfere and cause issues when you have your computer plugged into the Arduino. Simply put, by marking the HC-05 Bluetooth module into the digital pins, you have both the computer connection as well as the Bluetooth connection.



Updated as of 05/09/2024
  
