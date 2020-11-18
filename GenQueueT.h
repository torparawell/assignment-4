#include <iostream>
using namespace std;

template <class myType>
class GenQueue{
public:
  int front; // aka head
  int rear; // aka tail
  int mSize;
  unsigned int numElements;

  myType *myQueue; // pointer to a char - array
  GenQueue(){
    myQueue = new myType[128];
    mSize = 128;
    front = 0;
    rear = 0;
    numElements = 0;
  }
  
  GenQueue(int maxSize){
    myQueue = new myType[maxSize];
    mSize = maxSize;
    front = 0;
    rear = 0;
    numElements = 0;
  }

  ~GenQueue(){
    delete myQueue;
  }

  void insert(myType d){
    //check if full before proceding
    if(isFull()){
      throw("ERROR: Queue is full");
    }

    //myQueue[++rear] = d;
    myQueue[rear++] = d;
    rear = (rear) % mSize;
    numElements++;
  }
  myType atPos(int pos){
    return myQueue[pos];
  }
  myType remove(){
    if(isEmpty()){
      throw("ERROR: Queue is empty");
    }

    myType c;
    c = myQueue[front++];
    front = (front) % mSize;
    --numElements;
    return c;
  }

  myType peek(){
    return myQueue[front];
  }

  bool isFull(){
    return (numElements == mSize);
  }

  bool isEmpty(){
    return (numElements == 0);
  }

  unsigned int getSize(){
    return numElements;
  }
};
