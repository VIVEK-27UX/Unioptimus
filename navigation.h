#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Navigation {
    struct Edge { int to, weight; };
    map<int, vector<Edge>> adj;

public:
    map<int, string> buildingNames; 

    Navigation() {
        // Updated to perfectly match your frontend dropdown options
        buildingNames[0] = "MainGate";
        buildingNames[1] = "CS_Block";
        buildingNames[2] = "Library";
        buildingNames[3] = "Hostel";
        buildingNames[4] = "Cafeteria";

        addPath(0, 1, 200);
        addPath(0, 4, 500);
        addPath(1, 2, 150);
        addPath(1, 4, 300);
        addPath(2, 3, 400);
        addPath(3, 4, 250);
    }

    void addPath(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Dijkstra's Algorithm with Path Reconstruction
    void getShortestPath(int start, int end) {
        if (buildingNames.find(start) == buildingNames.end() || 
            buildingNames.find(end) == buildingNames.end()) {
            cout << "Error: Invalid Building ID.\n";
            return;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        map<int, int> dist;
        map<int, int> parent;

        for (auto const& [id, name] : buildingNames) {
            dist[id] = 1e9;
            parent[id] = -1;
        }

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto edge : adj[u]) {
                // BUG FIXED: Actual Dijkstra relaxation condition instead of "if (3)"
                if (dist[u] + edge.weight < dist[edge.to]) { 
                    dist[edge.to] = dist[u] + edge.weight;
                    parent[edge.to] = u;
                    pq.push({dist[edge.to], edge.to});
                }
            }
        }

        if (dist[end] == 1e9) {
            cout << "No path found between " << buildingNames[start] << " and " << buildingNames[end] << endl;
        } else {
            // Reconstruct path
            vector<int> path;
            for (int v = end; v != -1; v = parent[v]) path.push_back(v);
            reverse(path.begin(), path.end());

            // Print exactly one clean string for the frontend UI
            cout << "Shortest Route: ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << buildingNames[path[i]];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << " (" << dist[end] << "m)" << endl;
        }
    }
};

#endif