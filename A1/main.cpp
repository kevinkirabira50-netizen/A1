#include <iostream>
#include "student.H"

int main() {
    try {
        DynamicArray<StudentResult> studentArray;

        // Load records from file
        std::string filename = "records.txt";
        studentArray.loadFromFile(filename);
        std::cout << "Successfully loaded " << studentArray.getSize() << " student records.\n";

        // Display all loaded records
        std::cout << "\n--- All Student Records ---\n";
        for (int i = 0; i < studentArray.getSize(); ++i) {
            studentArray[i].display();
        }

        // Display calculated statistics
        studentArray.displayStatistics();

        // Sort records by marks descending
        studentArray.sortByMarksDescending();
        std::cout << "\n--- Records Sorted by Marks (Highest to Lowest) ---\n";
        for (int i = 0; i < studentArray.getSize(); ++i) {
            studentArray[i].display();
        }

        // Test searching by student ID
        std::string searchId = "VU-001";
        int index = studentArray.searchById(searchId);
        std::cout << "\n--- Search Result for ID: " << searchId << " ---\n";
        if (index != -1) {
            studentArray[index].display();
        } else {
            std::cout << "Student with ID " << searchId << " not found.\n";
        }

        // Save back to file to fulfill task requirements
        studentArray.saveToFile("output_records.txt");
        std::cout << "\nSuccessfully saved records to output_records.txt\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}