#include <iostream>
#include "GenQueueT.h"
#include "DoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Student{
public:
  Student(); // Creates a default constructor
  Student(int studentsTimeAtWindow); // Overloaded constructor
  ~Student(); // Deconstructor
 
  int GetTimeAtWindow(); // Gets the time at a window
  void IncrementQueueTime(); // Increments the time in live queue.
  void SetTimeAtWindow(int studentsTimeAtWindow); // Sets the time the student has at a window
  int GetTotalQueueTime(); // Grabs the total queue time.
private:
  int timeAtWindow; 
  int totalQueueTime;
  bool IsAtWindow;
};

class Window{
public:
  Window(); // default constructor
  ~Window(); // deconstructor

  bool IsOpen(); // See's if the current window has a student
  void GiveStudent(Student* student); // Gives the student to a window
  void IncrementIdleTime(); // Increments the idle window time
  int GetWaitTime(); // Gets the idle wait time
private:
  bool hasStudent; 
  int idleTime;
  int timeLeftWithStudent;

  void SetTimeWithStudent(int waitTime); // Set's the windows time with a student.
  void checkTimeLeftWithStudent(); // Checks how much time the window has left with a student.
};

class Windows{
public:
  Windows(); // Default constructor
  ~Windows(); // Deconstructor
  void SetTotalWindows(int windowCount); // Sets the total amount of windows
  Window* GetWindow(int windowNumber); // Gets a window for the student
  bool CheckForOpenWindow(); // Checks for an open window
  int GetOpenWindowPosition(); // Gets the open window position
  int GetTotalWindows(); // Gets the total number of windows
  bool AreAllWindowsOpen(); // If all windows are open then it returns true.
  void IncrementWindowTime(); // Increments time in the window
  int getMaxIdleTime(); // Gets the maximum idle time.
  int getNumberOfIdleWindowsOverFiveMinutes(); // If the window has more than five minutes of idle time it returns the number.
  double getMeanWindowIdleTime(); // Get's the mean idle time.

private:
  int totalWindows;
  DoublyLinkedList<Window*> *windowList = new DoublyLinkedList<Window*>;
};
class Calculate{
public:
    Calculate(Windows *windows); // Creates a default constructor
    ~Calculate(); // Deconstructor
 
    void RunCalculations(); // Runs all the calculations
    void AddStudent(Student* student); // Adds students to a list of all students
 
    // Getters
    double GetMean();
    double GetMedian();
    int GetMaxWaitTime();
    int GetStudentsWaitingOverTenMinutes();
    double GetMeanWindowIdleTime();
    int GetMaxWindowIdleTime();
    int GetNumberOfIdleWindowsOverFiveMinutes();

private:
    Windows *windows; 
    double meanWaitTime;
    double medianWaitTime;
    double meanWindowIdleTime;
    int maxWaitTime;
    int studentsWaitingOverTenMinutes;
    int maxWindowIdleTime;
    int numberOfIdleWindowsOverFiveMinutes;
    int totalStudents;
    int totalStudentsWaiting;

    double calculateMeanWaitTime(); // Calculates the mean wait time
    double calculateMedianWaitTime(); // Calculates the median wait time
    double calculateMeanWindowIdleTime(); // Calculates the mean window idle time
    int calculateMaxWaitTime(); // Calculates the max wait time
    int calculateStudentsWaitingOverTenMinutes(); // Calculates the student's waiting over ten minutes.
    int calculateMaxWindowIdleTime(); // Calculates the max window idle time
    int calculateNumberOfIdleWindowsOverFiveMinutes(); // Number of idle windows over five minutes.
    GenQueue<Student*> *allStudents = new GenQueue<Student*>; // Creates a queue of all students.
};

class Simulate{
public:
  Simulate(Windows *windows, Calculate *calculate); // Creates a default constructor
  ~Simulate(); // Deconstructor

  void RunSimulation(); // Runs the simulation in the simulation class
  void AddStudentArrivalTime(int studentArrivalTime); // Adds students arrival time to a queue
  void AddNumberOfStudentsArriving(int numberOfStudentsArriving); // Adds the number of students arriving to a queue.
  void AddStudentToQueue(Student* student); // Adds a student to a queue.
  int GetCurrentTime(); // Gets the current time in the simulation.
private:
  Windows *windows;
  Calculate *calculate;
  int time;
  bool windowsAreEmpty;
  bool liveQueueIsEmpty;
  bool noNewArrivalTimes;
  int timeOfStudentsArrival;
  GenQueue<int> *timesStudentsArrive = new GenQueue<int>;
  GenQueue<int> *numberOfStudentsThatArrive = new GenQueue<int>;
  GenQueue<Student*> *waitingQueue = new GenQueue<Student*>;
  GenQueue<Student*> *liveQueue = new GenQueue<Student*>;

  bool canSimulationStop(); // Checks to see if the simulation can stop
  void updateBooleans(); // Updates all booleans for canSimulationStop function
  void checkWindows(); // Checks for a window
  void checkLiveQueue(); // Checks for a live queue
  void checkArrivalTimes(); // Checks for an arrival time
  void incrementTime(); // Increments the time in simulation.
};


class FileIO{
public:
    FileIO(Windows *windows, Simulate *simulate, Calculate *calculate); // Overloaded constructor.
    ~FileIO(); // FileIO deconstructor.

    void ReadFile(string filename); // Reads from a file and gathers information.
    void OutFile(string filename); // Outputs to a file with all information.

  private:
    Windows *windows;
    Simulate *simulate;
    Calculate *calculate;
};
