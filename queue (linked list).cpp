#include <iostream>
using namespace std;

struct nodeQ
{
    char item;
    nodeQ *next;
};

class Queue
{
    public:
        nodeQ *backPtr, *frontPtr;
        void createQueue();
        void destroyQueue();
        bool isEmpty();
        void enQueue(char);
        void deQueue();
        char getFront();
        char getRear();
};

void Queue::createQueue()
{
    backPtr = NULL;
    frontPtr = NULL;
}

void Queue::destroyQueue()
{ 
    nodeQ *temp = frontPtr;
    while (temp)
    {
        frontPtr = temp->next;
        delete temp; temp=frontPtr;
    }
}

bool Queue::isEmpty()
{ return bool (backPtr == NULL && frontPtr == NULL); }

void Queue::enQueue(char node)
{
    nodeQ *newPtr = new nodeQ;
    newPtr->item = node;
    newPtr->next = NULL;
    if(isEmpty())
    {   
        frontPtr = backPtr = newPtr;
    }
    else
    {
        backPtr->next = newPtr;
        backPtr = newPtr;
    }
}

void Queue::deQueue()
{
   if(frontPtr)
   {
        nodeQ *tempPtr = frontPtr;
        frontPtr = frontPtr->next;
        if(!frontPtr) // If the queue is now empty
        {
            backPtr = NULL; // Set backPtr to NULL
        }
        tempPtr->next = NULL;
        delete tempPtr;
   }
}

char Queue:: getFront()
{ return frontPtr->item; }

char Queue::getRear()
{ return backPtr->item; }
