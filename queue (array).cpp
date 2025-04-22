#include <iostream>
using namespace std;

class Queue
{
    private:
        int front;
        int back;
        int items;

    public:
        bool isEmpty();
        bool isFull();
        void enQueue(char);
        void deQueue();
        char getFront();
        char getRear();
};

Queue::Queue()
{
    front = 0;
    back = -1;
}

Queue::~Queue()
{ delete [] items; }

bool Queue::isEmpty()
{ return bool(back < front); }

bool Queue::isFull()
{ return bool(back == size - 1);}

void Queue::enQueue(char insertItem)
{
    if(isFull())
    {
        cout << "\nCannot Insert. Queue is full!" ;
    }
    else
    {
        back ++;
        items[back] = insertItem;
    }
}

void Queue::deQueue()
{
    if(isEmpty())
    {
        cout << "\nCannot remove item. Empty Queue!";
    }
    else
    {
        deletedItem = items[front];
        front ++;
    }
}

char Queue:: getFront()
{ return items[front]; }

char Queue::getRear()
{ return items[back]; }
