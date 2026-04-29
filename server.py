from flask import Flask, request, jsonify
from flask_cors import CORS  # Fixes the browser block
import subprocess

app = Flask(__name__)

# This configuration is specific for when you use Live Server (port 5500)
# It allows the browser to talk to this Python server (port 5000)
CORS(app, resources={r"/*": {"origins": "*"}})

def run_exe(path, input_data):
    try:
        # Runs the .exe and passes the input_data to it via stdin
        result = subprocess.run(
            [path],
            input=input_data,
            text=True,
            capture_output=True,
            timeout=15  # Safety timeout for campus algorithms
        )
        return result.stdout.strip()
    except Exception as e:
        return f"Error running backend: {str(e)}"

# --- REGISTRY MODULE ---

@app.route("/add", methods=["POST"])
def add_student():
    data = request.json
    # Matches the ADD format expected by your C++ logic
    inp = f"ADD {data['id']} {data['name']}\n"
    out = run_exe("./a.exe", inp)
    return jsonify({"output": out if out else "Student Added Successfully"})

@app.route("/registry", methods=["POST"])
def registry():
    data = request.json
    search_id = data.get("search", "")
    inp = f"SEARCH {search_id}\n"
    out = run_exe("./a.exe", inp)
    return jsonify({"output": out})

# --- NAVIGATION MODULE ---
# --- NAVIGATION MODULE ---
@app.route("/navigation", methods=["POST"])
def navigation():
    data = request.json
    locations = ["MainGate", "CS_Block", "Library", "Hostel", "Cafeteria"]

    # Translates words to numbers
    src_int = locations.index(data['src'])
    dst_int = locations.index(data['dst'])

    # Sends the NUMBERS to C++
    inp = f"NAV {src_int} {dst_int}\n"
    out = run_exe("./a.exe", inp)
    return jsonify({"output": out})

# --- SCHEDULER MODULE ---
@app.route("/scheduler", methods=["POST"])
def scheduler():
    data = request.json
    tasks = data.get("tasks", [])
    
    # FIX: Added the "SCHED" nametag before the task count
    inp = f"SCHED {len(tasks)}\n"
    
    for t in tasks:
        inp += f"{t['name']} {t['start']} {t['end']}\n"
        
    out = run_exe("./a.exe", inp)
    return jsonify({"output": out})
# --- NETWORK MODULE ---
# --- NETWORK MODULE ---
@app.route("/network", methods=["POST"])
def network():
    data = request.json
    edges = data.get("edges", [])
    n = 5 # 5 buildings on campus
    
    # Send NAMETAG, NODE COUNT, and EDGE COUNT
    inp = f"NET {n} {len(edges)}\n"
    
    for e in edges:
        try:
            # Safely convert the input to integers
            u_int = int(e['u'])
            v_int = int(e['v'])
            inp += f"{u_int} {v_int} {e['w']}\n"
        except ValueError:
            return jsonify({"output": "Error: Please enter only numbers for Node U and Node V."})
            
    out = run_exe("./a.exe", inp)
    return jsonify({"output": out})
if __name__ == "__main__":
    app.run(debug=True, port=5000)