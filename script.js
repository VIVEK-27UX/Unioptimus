// --- BASE SERVER URL ---
// Make sure this exactly matches your Python terminal port
const SERVER_URL = "http://127.0.0.1:5000";

// --- UI NAVIGATION ---
function showSection(sectionId) {
    // Hide all cards
    document.querySelectorAll('.card').forEach(card => {
        card.style.display = 'none';
    });
    // Show the requested card
    document.getElementById(sectionId).style.display = 'block';
}

// --- 1. REGISTRY MODULE ---

async function addStudent() {
    const id = document.getElementById("studentId").value;
    const name = document.getElementById("studentName").value;
    const outBox = document.getElementById("registryOutput");

    if (!id || !name) {
        alert("Please enter both ID and Name");
        return;
    }

    outBox.innerText = "Adding student...";

    try {
        const response = await fetch(`${SERVER_URL}/add`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ id: parseInt(id), name: name })
        });
        const data = await response.json();
        outBox.innerText = data.output;
    } catch (error) {
        outBox.innerText = "Error: Could not connect to Python server.";
        console.error("Add Error:", error);
    }
}

async function searchStudent() {
    const searchId = document.getElementById("searchId").value;
    const outBox = document.getElementById("registryOutput");

    if (!searchId) {
        alert("Please enter an ID to search");
        return;
    }

    outBox.innerText = "Searching database...";

    try {
        const response = await fetch(`${SERVER_URL}/registry`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ search: searchId })
        });
        const data = await response.json();
        outBox.innerText = data.output;
    } catch (error) {
        outBox.innerText = "Error: Could not connect to Python server.";
        console.error("Search Error:", error);
    }
}

// --- 2. NAVIGATION MODULE ---

// Pre-fill the dropdowns when the page loads
window.onload = function() {
    showSection('registry');
    const locations = ["Library", "Hostel", "MainGate", "Cafeteria", "CS_Block"];
    const srcSelect = document.getElementById("src");
    const dstSelect = document.getElementById("dst");

    locations.forEach(loc => {
        srcSelect.add(new Option(loc, loc));
        dstSelect.add(new Option(loc, loc));
    });
};

async function findPath() {
    const src = document.getElementById("src").value;
    const dst = document.getElementById("dst").value;
    const outBox = document.getElementById("navOutput");

    if (src === dst) {
        outBox.innerText = "You are already at your destination!";
        return;
    }

    outBox.innerText = "Calculating shortest path (Dijkstra)...";

    try {
        const response = await fetch(`${SERVER_URL}/navigation`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ src: src, dst: dst })
        });
        const data = await response.json();
        outBox.innerText = data.output;
    } catch (error) {
        outBox.innerText = "Error calculating path.";
        console.error("Nav Error:", error);
    }
}

// --- 3. SCHEDULER MODULE ---

let taskQueue = [];

function addTask() {
    const name = document.getElementById("taskName").value;
    const start = document.getElementById("startTime").value;
    const end = document.getElementById("endTime").value;
    const outBox = document.getElementById("scheduleOutput");

    if (!name || !start || !end) {
        alert("Fill all task fields.");
        return;
    }

    taskQueue.push({ name: name, start: parseInt(start), end: parseInt(end) });
    outBox.innerText = `Task Added. Total pending: ${taskQueue.length}`;
    
    // Clear inputs
    document.getElementById("taskName").value = "";
    document.getElementById("startTime").value = "";
    document.getElementById("endTime").value = "";
}

async function optimizeSchedule() {
    const outBox = document.getElementById("scheduleOutput");

    if (taskQueue.length === 0) {
        outBox.innerText = "No tasks to optimize. Add tasks first.";
        return;
    }

    outBox.innerText = "Optimizing schedule...";

    try {
        const response = await fetch(`${SERVER_URL}/scheduler`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ tasks: taskQueue })
        });
        const data = await response.json();
        outBox.innerText = data.output;
        taskQueue = []; // Clear queue after processing
    } catch (error) {
        outBox.innerText = "Error optimizing schedule.";
        console.error("Schedule Error:", error);
    }
}

// --- 4. NETWORK MODULE ---

let networkEdges = [];

function addEdge() {
    const u = document.getElementById("node1").value;
    const v = document.getElementById("node2").value;
    const w = document.getElementById("cost").value;
    const outBox = document.getElementById("networkOutput");

    if (!u || !v || !w) {
        alert("Fill all edge fields.");
        return;
    }

    networkEdges.push({ u: parseInt(u), v: parseInt(v), w: parseInt(w) });
    outBox.innerText = `Edge Added. Total edges: ${networkEdges.length}`;
    
    // Clear inputs
    document.getElementById("node1").value = "";
    document.getElementById("node2").value = "";
    document.getElementById("cost").value = "";
}

async function runKruskal() {
    const outBox = document.getElementById("networkOutput");

    if (networkEdges.length === 0) {
        outBox.innerText = "No edges to analyze. Add edges first.";
        return;
    }

    outBox.innerText = "Finding Minimum Spanning Tree...";

    // Assuming a 5-node campus for the example, adjust if needed
    try {
        const response = await fetch(`${SERVER_URL}/network`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ edges: networkEdges, nodes: 5 })
        });
        const data = await response.json();
        outBox.innerText = data.output;
        networkEdges = []; // Clear after running
    } catch (error) {
        outBox.innerText = "Error running network analysis.";
        console.error("Network Error:", error);
    }
}