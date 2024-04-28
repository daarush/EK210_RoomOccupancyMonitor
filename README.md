Introduction
--
This project was inspired by my [311 Project](https://github.com/HudsonReynolds2/ID-Finder)!

This project is for my engineering class where the "our goal is to develop a minimal-impact system that monitors classroom occupancy, prevents entry once maximum capacity is reached, and reduces the risk of overcrowding for students and teachers."

The basic idea was to use arduino code only, but since we want to make it unique and accessable, we decided to make it so the user is able to view the information displayed on their internet device. Utimately, we had a lot of fun creating this device, and me, who is the lead coder had most fun creating the connection between the arduino and the website.

Components
--
- **Arduino:** the brain.
- **Two IR Distance Sensors:** to measure the distance and report back the findings.
- **HC-05 Bluetooth Module:** to communicate between the arduino and the server.
- **DC Motor:** to control the physical movement for an appratus which blocks the doorway once the max occupancy is reached.

Testing
--
To get the whole project working and synced, first I tested every component on its own, hence the many folders in the directory and a lot of test files.

1. Testing the sensors and how they work, this also includes claribrating them since different models have different conversions
2. Next was the motor, since the DC motor we used for the project was not arduino compatible, we implemented a mosfet to allow the communcation between the motor and arduino
3. After getting the main components, then the bluetooth testing began
    1. Establishing a connection between a nodejs server and the ardiuno
    2. sending and reciveing information between the ardiuno and server
    3. updating the components on both ends

Although it sounds simple stuff, it took a lot of time and exploring since this topic was new. 

Code 
--
As mentioned before, there are folders representing each components and lots of tests.
The code in each folder should have some explanations. 

  
