// Keep track of connected clients
const clients = [];

// Function to send color command to the server
function sendNewOccupancy(occupancy) {
    fetch('/changeOccupancy', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ occupancy }),
    })
        .then(response => {
            if (response.ok) {
                console.log(`Successfully sent ${occupancy} command.`);
            } else {
                console.error(`Error sending ${occupancy} command.`);
            }
        })
        .catch(error => console.error(`Error: ${error}`));
}

// Add event listeners to buttons
document.getElementById('setOccupancy').addEventListener('click', () => {
    const occupancy = document.getElementById('occupancy').value;
    sendNewOccupancy(occupancy);

    const max = document.querySelector('.max');
    max.innerHTML = occupancy;
});


// Connect to WebSocket server
const ws = new WebSocket('ws://10.239.156.6:8080'); // Replace YOUR_SERVER_IP with your server's external IP address

ws.onopen = function () {
    console.log('WebSocket connection established.');
};

ws.onmessage = function (event) {
    const parsedData = JSON.parse(event.data);
    console.log('Received data from WebSocket:', parsedData);
    console.log('Updating UI with data:', parsedData);
    updateUI(parsedData);
};

function updateUI(data) {
    console.log('Updating UI with data:', data);
    let occupancy = parseInt(data);
    let maxOccupancy = parseInt(document.querySelector('.max').innerText);

    if (occupancy / maxOccupancy > 0.8) {
        document.getElementById('status').style.backgroundColor = 'red';
    } else if (occupancy / maxOccupancy > 0.6) {
        document.getElementById('status').style.backgroundColor = 'orange';
    } else {
        document.getElementById('status').style.backgroundColor = 'green';
    }

    const occupancyText = document.getElementById('currentOccupancy');
    occupancyText.innerText = data;
}

// WebSocket connection established
ws.onopen = function () {
    console.log('WebSocket connection established.');

    // Add this client to the list of clients
    clients.push(ws);
};

// Handle errors
ws.onerror = function (error) {
    console.error('WebSocket error:', error);
};

// Handle closed connections
ws.onclose = function () {
    console.log('WebSocket connection closed.');
};

// Broadcast function to send message to all clients
function broadcast(data) {
    clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });
}