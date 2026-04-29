#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

struct NetworkEdge { 
    int u, v, weight; 
};

class NetworkAnalyst {
    map<int, int> parent;

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); 
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }

public:
    void handleNetworkOptimization(map<int, string>& navBuildingNames) {
        vector<NetworkEdge> potentialLinks;
        int numNodes, numEdges;

        // API Mode: Read counts from Python
        if (cin >> numNodes >> numEdges) {
            
            // Build the map locally if it's empty (failsafe)
            map<int, string> buildingNames = navBuildingNames;
            if (buildingNames.empty()) {
                buildingNames[0] = "MainGate";
                buildingNames[1] = "CS_Block";
                buildingNames[2] = "Library";
                buildingNames[3] = "Hostel";
                buildingNames[4] = "Cafeteria";
            }

            // Read exact number of edges sent
            for (int i = 0; i < numEdges; i++) {
                int u, v, cost;
                cin >> u >> v >> cost;
                potentialLinks.push_back({u, v, cost});
            }

            if (!potentialLinks.empty()) {
                optimizeInfrastructure(potentialLinks, buildingNames);
            } else {
                cout << "Error: No valid routes entered.\n";
            }
        } else {
            cout << "Error: Failed to read network data from server.\n";
        }
    }

private:
    void optimizeInfrastructure(vector<NetworkEdge>& edges, map<int, string>& names) {
        for (auto const& [id, name] : names) {
            parent[id] = id;
        }

        sort(edges.begin(), edges.end(), [](const NetworkEdge& a, const NetworkEdge& b) {
            return a.weight < b.weight;
        });

        int totalCost = 0;
        int linksBuilt = 0;

        cout << "--- OPTIMIZED MST PLAN ---\n";

        for (const auto& e : edges) {
            if (find(e.u) != find(e.v)) {
                unite(e.u, e.v);
                cout << "[Link] " << names[e.u] << " <---> " << names[e.v] << " | Cost: $" << e.weight << "k\n";
                totalCost += e.weight;
                linksBuilt++;
            }
        }

        cout << "--------------------------\n";
        cout << "Minimum Investment: $" << totalCost << "k\n";

        if (linksBuilt < (int)names.size() - 1) {
            cout << "[Note: Network is incomplete. More edges needed.]\n";
        }
    }
};

#endif