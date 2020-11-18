#include "assignment-4.h"
Student::Student(){
  // Initializers
  totalQueueTime = 0;
  SetTimeAtWindow(-1);
  IsAtWindow = false;
}

Student::Student(int studentsTimeAtWindow){ // Students time at a window
  totalQueueTime = 0;
  SetTimeAtWindow(studentsTimeAtWindow);
  IsAtWindow = false;
}

int Student::GetTimeAtWindow(){ // Gets the time at window
  return timeAtWindow;
}

int Student::GetTotalQueueTime(){ // Gets the total time in the queue.
  return totalQueueTime;
}

void Student::SetTimeAtWindow(int studentsTimeAtWindow){ // Sets the student's time at a window.
  timeAtWindow = studentsTimeAtWindow;
}
void Student::IncrementQueueTime(){ // Increments the queue time.
  totalQueueTime++;
}
