🚀 UniOptimus | Smart Campus Engine
UniOptimus is a full-stack algorithmic optimization framework designed to simulate and solve real-world campus management problems. By bridging a lightning-fast C++ computational engine with a modern web interface via a Python Flask API, this project demonstrates the practical application of advanced Data Structures and Algorithms (DSA) in a full-stack environment.

🧠 Core Architecture
The project utilizes a 3-tier architecture to separate the user interface, the API routing, and the heavy computational logic:

Frontend (UI): Vanilla HTML5, CSS3, and JavaScript using the fetch API for asynchronous, non-blocking requests.

Backend (Bridge): Python 3 with Flask and CORS. Acts as a lightweight microservice that captures web traffic and pipes it into the compiled C++ executable using the subprocess module.

Computational Engine: Modular C++17. Handles all heavy lifting, memory management, file I/O, and graph traversal.

⚙️ Modules & Algorithms Implemented
1. 📘 Student Registry (Dynamic Search & Sort)
A persistent database system utilizing binary file handling (records.dat).

Algorithms: Custom Merge Sort, Binary Search, Hash Mapping.

Logic: Dynamically switches between Binary Search (O(logn)) for smaller datasets and Hash Maps (O(1)) for larger datasets based on a calculated threshold.

2. 🗺️ Campus Navigation (Shortest Path)
A routing system to find the quickest path between campus buildings.

Data Structure: Adjacency List (Weighted Graph).

Algorithm: Dijkstra’s Algorithm using a Min-Priority Queue.

Logic: Calculates the lowest-cost path and reconstructs the route array backwards using a parent-tracking map.

3. 📅 Task Scheduler (Activity Selection)
A productivity engine to maximize the number of non-overlapping tasks a student or administrator can complete in a day.

Algorithm: Greedy Algorithm (Activity Selection).

Logic: Sorts tasks by earliest finish time and greedily selects the maximum number of compatible activities.

4. 🌐 Infrastructure Optimization (Network Backbone)
A cost-calculation tool to lay down the cheapest possible fiber-optic or electrical network connecting all campus buildings.

Algorithm: Kruskal's Algorithm (Minimum Spanning Tree).

Data Structure: Disjoint Set Union (DSU) with Path Compression.

Logic: Sorts all potential cabling routes by cost and unites isolated network nodes while detecting and rejecting redundant cycles.

💻 Tech Stack
C++ (Core Engine, g++ compiler)

Python 3 (Flask, Flask-CORS)

HTML/CSS/JS (Frontend UI)

🚀 Installation & Setup
Prerequisites
C++ Compiler (MinGW / GCC)

Python 3.x

VS Code with the "Live Server" extension (recommended)

Step 1: Install Python Dependencies
Open your terminal and install the required Flask libraries:

Bash
pip install flask flask-cors
Step 2: Compile the Engine
Compile the modular C++ files into a single executable. In your project directory, run:

Bash
g++ main.cpp -o a.exe
Step 3: Start the Backend Bridge
Launch the Python Flask server to listen for frontend requests:

Bash
python server.py
(Leave this terminal running!)

Step 4: Launch the Frontend
Open index.html in your browser. If using VS Code, click "Go Live" to start the Live Server on port 5500.

👨‍💻 Author
Vivek Mainali
B.Tech Computer Science and Engineering
Graphic Era Deemed to be University
