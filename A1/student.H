#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

// Structure to hold individual student records
struct StudentResult {
    std::string studentId;
    std::string name;
    std::string courseCode;
    char grade;
    double marks; // Using double to handle decimals

    void display() const {
        std::cout << "ID: " << studentId 
                  << " | Name: " << name 
                  << " | Course: " << courseCode 
                  << " | Grade: " << grade 
                  << " | Marks: " << marks << "\n";
    }
};

// Dynamic Array template class with capacity doubling (Task A1)
template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    // Constructor
    DynamicArray(int cap = 2) {
        capacity = cap;
        size = 0;
        data = new T[capacity];
    }

    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Copy Constructor (Deep Copy)
    DynamicArray(const DynamicArray& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Copy Assignment Operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    void push_back(const T& item) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = item;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Sort records by marks from highest to lowest (can be adapted for sorting tasks)
    void sortByMarksDescending() {
        if (size <= 1) return;
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (data[j].marks < data[j + 1].marks) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    // Search by ID
    int searchById(const std::string& targetId) const {
        for (int i = 0; i < size; ++i) {
            if (data[i].studentId == targetId) {
                return i;
            }
        }
        return -1;
    }

    // Display statistics
    void displayStatistics() const {
        if (size == 0) {
            std::cout << "No records available for statistics.\n";
            return;
        }

        double totalMarks = 0;
        double highestMarks = data[0].marks;
        double lowestMarks = data[0].marks;
        std::string topStudent = data[0].name;
        std::string lowestStudent = data[0].name;

        for (int i = 0; i < size; ++i) {
            totalMarks += data[i].marks;
            if (data[i].marks > highestMarks) {
                highestMarks = data[i].marks;
                topStudent = data[i].name;
            }
            if (data[i].marks < lowestMarks) {
                lowestMarks = data[i].marks;
                lowestStudent = data[i].name;
            }
        }

        double averageMarks = totalMarks / size;

        std::cout << "\n--- Class Statistics ---\n";
        std::cout << "Total Students: " << size << "\n";
        std::cout << "Class Average Marks: " << averageMarks << "\n";
        std::cout << "Highest Marks: " << highestMarks << " (" << topStudent << ")\n";
        std::cout << "Lowest Marks: " << lowestMarks << " (" << lowestStudent << ")\n";
    }

    // Load records from text file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for reading: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string idStr, name, courseCode, gradeStr, marksStr;

            if (std::getline(ss, idStr, ',') &&
                std::getline(ss, name, ',') &&
                std::getline(ss, courseCode, ',') &&
                std::getline(ss, gradeStr, ',') &&
                std::getline(ss, marksStr, ',')) {
                
                StudentResult student;
                student.studentId = idStr;
                student.name = name;
                student.courseCode = courseCode;
                student.grade = gradeStr.empty() ? 'F' : gradeStr[0];
                student.marks = std::stod(marksStr); // Handles decimal values safely
                
                push_back(student);
            }
        }
        file.close();
    }

    // Save records to text file
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing: " + filename);
        }

        for (int i = 0; i < size; ++i) {
            file << data[i].studentId << ","
                 << data[i].name << ","
                 << data[i].courseCode << ","
                 << data[i].grade << ","
                 << data[i].marks << "\n";
        }
        file.close();
    }
};

#endif