#include "assignment-4.h"

//default Constructor
Calculate::Calculate(Windows *windows){
  // Initializers
  this->windows = windows; 
  totalStudents = 0;
  meanWaitTime = -1;
  medianWaitTime = -1;
  meanWindowIdleTime = -1;
  maxWaitTime = -1;
  studentsWaitingOverTenMinutes = -1;
  maxWindowIdleTime = -1;
  numberOfIdleWindowsOverFiveMinutes = -1;
}

Calculate::~Calculate(){} // Deconstructor

void Calculate::RunCalculations(){ 
  meanWindowIdleTime = calculateMeanWindowIdleTime(); 
  maxWindowIdleTime = calculateMaxWindowIdleTime();
  numberOfIdleWindowsOverFiveMinutes = calculateNumberOfIdleWindowsOverFiveMinutes();
  meanWaitTime = calculateMeanWaitTime();
  medianWaitTime = calculateMedianWaitTime();
  maxWaitTime = calculateMaxWaitTime();
  studentsWaitingOverTenMinutes = calculateStudentsWaitingOverTenMinutes();
}
//Getters
double Calculate::GetMean() {
  return meanWaitTime;
}
double Calculate::GetMedian() {
  return medianWaitTime;
}
int Calculate::GetMaxWaitTime() {
  return maxWaitTime;
}
int Calculate::GetStudentsWaitingOverTenMinutes() {
  return studentsWaitingOverTenMinutes;
}
double Calculate::GetMeanWindowIdleTime() {
  return meanWindowIdleTime;
}
int Calculate::GetMaxWindowIdleTime() {
  return maxWindowIdleTime;
}
int Calculate::GetNumberOfIdleWindowsOverFiveMinutes() {
  return numberOfIdleWindowsOverFiveMinutes;
}

// Adds students to the allstudents queuue.
void Calculate::AddStudent(Student* student){
  allStudents->insert(student);
  totalStudents++;
}

double Calculate::calculateMeanWaitTime(){
  double totalWaitingTime = 0;
  for(int i = 0; i < totalStudents; i++){ // Iterates though every student, getting their wait time.
    Student *currentStudent = allStudents->atPos(i);
    totalWaitingTime += (double)currentStudent->GetTotalQueueTime();
    if(currentStudent->GetTotalQueueTime() != 0)
      totalStudentsWaiting++; // Adds total number of student.
  }
  if(totalWaitingTime == 0)
    return 0;
  return totalWaitingTime/totalStudentsWaiting; // Calculates simple average.
}

double Calculate::calculateMedianWaitTime(){ 
  int medianWaitTimeArr[totalStudentsWaiting]; // Creates an array on students of side of the waiting students.
  int currentQueueTime; // Creates queuetime as a temporary variable
  // Initializes the array
  for(int i = 0; i < totalStudents; i++){ // Iterates through all students that waited in a queue.
    Student *currentStudent = allStudents->atPos(i);
    currentQueueTime = currentStudent->GetTotalQueueTime();
    if(currentQueueTime > 0) { // Adds their queue time if it's greater than 0
      medianWaitTimeArr[i] = currentQueueTime; 
    }
  }
  int n = sizeof(medianWaitTimeArr) /sizeof(medianWaitTimeArr[0]); // Calculates "n" which is simply the size of the array
  sort(medianWaitTimeArr, medianWaitTimeArr+n); // Sorts the array
  if (n % 2 == 0) { // If it's an even size
    medianWaitTime = (medianWaitTimeArr[n/2] + medianWaitTimeArr[(n/2)-1] /2);
  }
  if (n % 2 == 1) { // If it's an odd size
    medianWaitTime = medianWaitTimeArr[n/2];
  }
  return medianWaitTime;

}

double Calculate::calculateMeanWindowIdleTime(){
  return windows->getMeanWindowIdleTime(); // Calculates the mean window idle time from the windows class. 
}

int Calculate::calculateMaxWaitTime(){
  int longestWaitTime = 0; 
  for(int i = 0; i < totalStudents; i++){ // Simply gets the largest time that a student had to wait.
    Student *currentStudent = allStudents->atPos(i);
    if(currentStudent->GetTotalQueueTime() > longestWaitTime)
      longestWaitTime = currentStudent->GetTotalQueueTime();
  }
  return longestWaitTime; 
}

int Calculate::calculateStudentsWaitingOverTenMinutes(){
  int count = 0;
  for(int i = 0; i < totalStudents; i++){ // If a student has been waiting for over ten minutes then it adds to count.
    Student *currentStudent = allStudents->atPos(i);
    if(currentStudent->GetTotalQueueTime() >= 10)
      count++;
  }
  return count;
}

int Calculate::calculateMaxWindowIdleTime(){
  return windows->getMaxIdleTime();
}

int Calculate::calculateNumberOfIdleWindowsOverFiveMinutes(){
  return windows->getNumberOfIdleWindowsOverFiveMinutes();
}
