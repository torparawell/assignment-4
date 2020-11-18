#include "assignment-4.h"
#include<iomanip>

//default Constructor
FileIO::FileIO(Windows *windows, Simulate *simulate, Calculate *calculate){
  this->windows = windows;
  this->simulate = simulate;
  this->calculate = calculate;
}

//default destructor
FileIO::~FileIO(){
 //cout << "bye FileIO" << endl;
}

void FileIO::ReadFile(string filename){
  fstream inputFile;
  inputFile.open(filename);
  if(inputFile.is_open()){
    int lineCount = 1;
    string currentLine;
    int timeStudentArrives;
    int numberOfStudentsArriving;
    int nextArrivalTime = 2;
    int studentsTimeAtWindow;

    while(getline(inputFile, currentLine)){
      if(lineCount == 1){
        windows->SetTotalWindows(stoi(currentLine));
      }
      else if (lineCount == nextArrivalTime){
        timeStudentArrives = stoi(currentLine);
        simulate->AddStudentArrivalTime(timeStudentArrives);
      }
      else if(lineCount == nextArrivalTime+1){
        numberOfStudentsArriving = stoi(currentLine);
        simulate->AddNumberOfStudentsArriving(numberOfStudentsArriving);
        nextArrivalTime = lineCount+numberOfStudentsArriving+1;
      }
      else if(lineCount != nextArrivalTime){
        studentsTimeAtWindow = stoi(currentLine);
        Student* student = new Student();
        student->SetTimeAtWindow(studentsTimeAtWindow);
        simulate->AddStudentToQueue(student);
        calculate->AddStudent(student);
      }
      lineCount++;
    }
  }
  else{
    cout << "Error: file not found" << endl;
  }
}
void FileIO::OutFile(string filename) {
  ofstream outFile;
  outFile.open(filename);
  outFile << left << setw(40) << "Mean student wait time: " << setw(5) << calculate->GetMean() << endl;
  outFile << setw(40) << "Median student wait time: " << setw(5) << calculate->GetMedian() << endl;
  outFile << setw(40) << "Longest student wait time: " << setw(5) << calculate->GetMaxWaitTime() << endl;
  outFile << setw(40) << "Students waiting over 10 minutes: " << setw(5) << calculate->GetStudentsWaitingOverTenMinutes() << endl;
  outFile << setw(40) << "Mean window idle time: " << setw(5) << calculate->GetMeanWindowIdleTime() << endl;
  outFile << setw(40) << "Longest window idle time: " << setw(5) << calculate->GetMaxWindowIdleTime() << endl;
  outFile << setw(40) << "Windows idle for over 5 minutes: " << setw(5) << calculate->GetNumberOfIdleWindowsOverFiveMinutes() << endl;
  outFile.close();
}
