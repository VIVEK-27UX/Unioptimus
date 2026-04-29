#ifndef STUDENT_REGISTRY_H
#define STUDENT_REGISTRY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

struct Student {
    int id;
    char name[50];
};

class StudentRegistry {
    unordered_map<int, Student> studentHash;
    vector<Student> sortedRecords;
    const int THRESHOLD = 5; 

public:
    
    void merge(vector<Student>& arr, int l, int m, int r) {
        int n1 = m - l + 1, n2 = r - m;
        vector<Student> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i].id <= R[j].id) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    void mergeSort(vector<Student>& arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    void syncData() {
        ifstream fin("records.dat", ios::binary);
        if (!fin) return; // Failsafe if file doesn't exist yet

        sortedRecords.clear();
        studentHash.clear();
        Student s;
        while(fin.read((char*)&s, sizeof(s))) {
            sortedRecords.push_back(s);
            studentHash[s.id] = s;
        }
        fin.close();
        if(!sortedRecords.empty()) mergeSort(sortedRecords, 0, sortedRecords.size() - 1);
    }

    
    int binarySearch(int target) {
        int l = 0, r = sortedRecords.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (sortedRecords[mid].id == target) return mid;
            if (sortedRecords[mid].id < target) l = mid + 1;
            else r = mid - 1;
        }
        return -1;
    }

    void smartSearch() {
        if(sortedRecords.empty()) { cout << "No records found in database.\n"; return; }
        
        int target;
        // API MODE: Read directly from Python stream, no prompts
        if (cin >> target) {
            if (sortedRecords.size() < THRESHOLD) {
                int res = binarySearch(target);
                if(res != -1) cout << "[Binary Search] Found: " << sortedRecords[res].name << " (ID: " << target << ")" << endl;
                else cout << "[Binary Search] Not Found.\n";
            } 
            else {
                if (studentHash.count(target)) cout << "[Hash Map] Found: " << studentHash[target].name << " (ID: " << target << ")" << endl;
                else cout << "[Hash Map] Not Found.\n";
            }
        }
    }

    void addRecord() {
        ofstream fout("records.dat", ios::app | ios::binary);
        Student s;
        
        // API MODE: Read directly from Python stream
        if (cin >> s.id) {
            cin.ignore(); // Clear the space between ID and Name
            cin.getline(s.name, 50); // Read the full name including spaces

            fout.write((char*)&s, sizeof(s));
            fout.close();
            
            // Output a single clean string for the frontend website
            cout << "Success: " << s.name << " (ID: " << s.id << ") saved to binary records.\n";
            cout<<"!";
        }
    }
};

#endif