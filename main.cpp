#include <iostream>
#include <string>
#include "student_registry.h"
#include "navigation.h"
#include "scheduler.h"
#include "network.h"

using namespace std;

int main() {
    StudentRegistry reg;
    Navigation nav;
    CourseScheduler sch;
    NetworkAnalyst net;

    string command;
    
    // Read the "Nametag" sent by Python
    if (cin >> command) {
        
        // 1. REGISTRY
        if (command == "ADD") {
            reg.addRecord();
        } 
        else if (command == "SEARCH") {
            reg.syncData(); 
            reg.smartSearch();
        }
        
        // 2. NAVIGATION
        else if (command == "NAV") {
            int src, dst;
            cin >> src >> dst;
            // Assuming nav class doesn't need to be initialized with map data first
            // If your navigation class requires setup, call it before this!
            nav.getShortestPath(src, dst);
        }
        
        // 3. SCHEDULER
        else if (command == "SCHED") {
            // Assuming your handleUserSchedule() reads the task count and data via cin
            sch.handleUserSchedule(); 
        }
        
        // 4. NETWORK
        else if (command == "NET") {
            // Assuming handleNetworkOptimization reads node/edge count via cin
            net.handleNetworkOptimization(nav.buildingNames); 
        }
        
        else {
            cout << "System Error: Command '" << command << "' not found." << endl;
        }
    }

    return 0; 
}