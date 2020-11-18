#include "assignment-4.h"
using namespace std;

int main(int argc, char** argv){
  Windows *windows = new Windows();
  Calculate *calculate = new Calculate(windows);
  Simulate *simulate = new Simulate(windows, calculate);

  FileIO *fileio = new FileIO(windows, simulate, calculate);
  string filename;
  cout << "Enter a file: ";
  cin >> filename;

  fileio->ReadFile(filename);

  simulate->RunSimulation();

  calculate->RunCalculations();
  cout << "Enter outfile name: " << endl;
  cin >> filename;
  fileio->OutFile(filename);

  delete fileio;
  delete calculate;
  delete simulate;
  delete windows;
}
