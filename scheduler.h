#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Task {
    string name;
    int start, end;
};

class CourseScheduler {
public:
    // API Mode Interface
    void handleUserSchedule() {
        vector<Task> userTasks;
        int taskCount;

        // 1. Read the total number of tasks Python is sending
        if (cin >> taskCount) {
            // 2. Loop exactly that many times to grab the data
            for (int i = 0; i < taskCount; i++) {
                string name;
                int s, e;
                cin >> name >> s >> e;
                
                // Only add valid tasks
                if (s < e) {
                    userTasks.push_back({name, s, e});
                }
            }
            // 3. Run the Activity Selection Algorithm
            planDay(userTasks);
        } else {
            cout << "Error: Could not read task data from server.\n";
        }
    }

private:
    void planDay(vector<Task>& tasks) const {
        if (tasks.empty()) {
            cout << "No valid tasks to schedule.\n";
            return;
        }

        // Greedy Algorithm: Sort by earliest finish time
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.end < b.end;
        });

        int lastFinish = -1;
        int count = 0;

        // Print exactly what should appear in the black box on the website
        cout << "Optimized Schedule:\n";
        for (const auto& t : tasks) {
            if (t.start >= lastFinish) {
                cout << t.name << " (" << t.start << ":00 to " << t.end << ":00)\n";
                lastFinish = t.end;
                count++;
            }
        }
        cout << "Max Tasks Scheduled: " << count << endl;
    }
};

#endif