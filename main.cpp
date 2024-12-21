// Nada Amin Fawzy Mohamed
// 20230440
// Problem 1 - Label generator
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

// A base class that declares the basic attributes and methods that will inherit later
class labelGenerator {
protected:
    string prefix;
    int sequenceNum;
public:
    // A parametrized constructor to assign the prefix and the starting index
    labelGenerator(string prefix, int sequenceNum)
            :prefix(std::move(prefix)), sequenceNum(sequenceNum){}
    // A function to return the prefix and the index incremented by 1 every call
    virtual string nextLabel(){
        return prefix + " " + to_string(sequenceNum++);
    }
};

// A derived class that inherits the constructor and nextLabel function form labelGenerator class
class FileLabelGenerator : public labelGenerator{
private:
    ifstream file;
public:
    // Inherits the base class constructor and assign the file name
    FileLabelGenerator(string prefix, int sequenceNum, const string& filename):labelGenerator(std::move(prefix), sequenceNum){
        // Open a file when creating an object
        file.open(filename);
    }
    // Closing file in the destructor
    ~FileLabelGenerator() {
        if (file.is_open()) {
            file.close();
        }
    }
    // Override nextLabel function in the base class as they have the same target to return the content needed
    string nextLabel() override{
        string text;
        while(getline(file, text)){
            // Save the return of nextLabel function in a variable to reuse it in the return
            string baseReturn = labelGenerator::nextLabel() + " ";
            // Add the text in the file to the prefix and its index
            return baseReturn + text;
        }
        return "";
    }
    // Return 0 when we reach the end of the file to execute
    bool hasLines(){
        return !file.eof();
    }

};

// A class of all validations needed in the program
class Validation {
public:
    // A function to validate any integer input
    static int getInput(){
        int number;
        bool validInput = false;

        // Stops taking inputs till the user enter the suitable integer input
        while (!validInput){
            try {
                if (!(cin >> number)) {
                    // Clear unwanted inputs
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Invalid input - please enter a number");
                }

                validInput = true;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
        return number;
    }
    // Function to make sure the user enter an existed file name
    static string CheckFileName(){
        string fileName;
        ifstream file;

        while (true){
            getline(cin, fileName);
            file.open(fileName);
            try{
                if(file.fail()){
                    throw runtime_error("Invalid file name - please enter an existed file");
                }
                return fileName;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                file.close();
            }
        }
    }
};

int main() {
    cout << "---------------------------------------\nWelcome to the label generator program\n"
            "---------------------------------------\n";
    // Starting menu
    while (true){
        int choice;
        cout << "Do you want to:\n1- Use the program\n2- Exit\n";
        choice = Validation::getInput();
        if(choice == 1){
            string prefix, filename;
            int startIndex;
            cout << "Enter the prefix you need:";
            cin >> prefix;
            cout << "Enter the starting index:";
            // Use a function in Validation class to take and validate an integer input
            startIndex = Validation::getInput();
            cout << "Enter the file name:";
            // Use a function in Validation class to take and validate the file name
            filename = Validation::CheckFileName();
            FileLabelGenerator Label(prefix, startIndex, filename);
            // Print the content of the file till it ends
            while(Label.hasLines()){
                cout << Label.nextLabel() << endl;
            }
            cout << "---------------------------------------\n";
        }else if(choice == 2){
            cout << "Thank you for choosing our program.";
            break;
        }else{
            cerr << "There is no number " << choice << " in the list!\n";
            continue;
        }
    }
    return 0;
}
