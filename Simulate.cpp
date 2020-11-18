#include "assignment-4.h"

//default Constructor
Simulate::Simulate(Windows *windows, Calculate *calculate){
  // Initializes variables
  this->windows = windows; 
  this->calculate = calculate;
  time = 0;
  windowsAreEmpty = true;
  liveQueueIsEmpty = true;
  noNewArrivalTimes = false;
}

Simulate::~Simulate() {}

void Simulate::RunSimulation(){ // Runs the simulation.
  int numberOfStudentsArriving;
  int openWindowPosition;
  int studentCount;

  while (!canSimulationStop()) {
    if (time == 0)
      timeOfStudentsArrival = timesStudentsArrive->remove(); // When time first begins, a student is removed from time of student arrival queue. 
      // to let the system know when a student will arrive.

    if (time == timeOfStudentsArrival) { // When time reaches the time a student should arrive...
      studentCount = 0;
      numberOfStudentsArriving = numberOfStudentsThatArrive->remove(); // Removes the number of students that arrive from a seperate queue.
      
      while(studentCount != numberOfStudentsArriving){
        liveQueue->insert(waitingQueue->remove()); // Inserts the number of students into a live queue (very smart Patrick).
        studentCount++; // Increases the count of students. 
      }
      if(!timesStudentsArrive->isEmpty()) // If it's not empty
        timeOfStudentsArrival = timesStudentsArrive->remove(); // Remove another student from the list
    }

    while(!liveQueue->isEmpty() && windows->CheckForOpenWindow()) { // If live queue is empty and there is an open window
      openWindowPosition = windows->GetOpenWindowPosition(); // Gets an open window position
      Window* window = windows->GetWindow(openWindowPosition); // Gets an open window
      Student* student = liveQueue->remove(); // Assigns a student to the window.
      window->GiveStudent(student);
    }
    incrementTime(); // Increments the time.
  }
}

void Simulate::AddStudentArrivalTime(int studentArrivalTime){ // Adds the arrival time of a student.
  timesStudentsArrive->insert(studentArrivalTime); // Inserts a student
}
void Simulate::AddNumberOfStudentsArriving(int numberOfStudentsArriving){ // Number of students that are arriving.
  numberOfStudentsThatArrive->insert(numberOfStudentsArriving);
}

void Simulate::AddStudentToQueue(Student* student){ // Adds a student to the queuue.
  waitingQueue->insert(student);
}

int Simulate::GetCurrentTime(){ // Gets the current time in a simulation
  return time;
}

void Simulate::incrementTime(){ // increments time
  time++;
  windows->IncrementWindowTime();
  Student* student;
  for(int i = 0; i < liveQueue->getSize(); ++i){ // For each in the live queue.
    student = liveQueue->atPos(i);
    student->IncrementQueueTime();
  }
}

bool Simulate::canSimulationStop(){ // Checks conditions to see if the simulation can stop.
  updateBooleans();
  if(windowsAreEmpty && liveQueueIsEmpty && noNewArrivalTimes)
    return true;
  return false;
}

void Simulate::updateBooleans(){
  if(windows->AreAllWindowsOpen())
    windowsAreEmpty = true;
  else
    windowsAreEmpty = false;
  if(liveQueue->isEmpty())
    liveQueueIsEmpty = true;
  else
    liveQueueIsEmpty = false;
  if(timesStudentsArrive->isEmpty() && timeOfStudentsArrival < time)
    noNewArrivalTimes = true;
  else
    noNewArrivalTimes = false;
}

