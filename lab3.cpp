//Denies Wong A22EC0047

#include <iostream>
using namespace std;

const int size = 100;
class stack
{
    private:
        int top;
        char data[size];
    
    public:
        void createStack();
        void push(char);
        char pop();
        char stackTop();
        bool isFull();
        bool isEmpty();
};

void stack::createStack()
{
    top = -1;
}

void stack::push(char newitem)
{
    if(isFull())
    {
        cout << "Sorry, cannot push item. Stack is now full!" << endl;
    }
    else
    {
        top = top + 1;
        data[top] = newitem;
    }
}

char stack::pop()
{
    char item;
    if(isEmpty())
    {
        cout << "Sorry, cannot pop item. Stack is empty!" << endl;
    }
    else
    {
        item = data[top];
        top = top - 1;
        return item;
    }
}

char stack::stackTop()
{
    if(isEmpty())
    {
        cout << "Sorry, stack is empty!" << endl;
    }
    else
    {
        return data[top];
    }
}

bool stack::isFull()
{
    return (top == size-1);
}

bool stack::isEmpty()
{
    return (top == -1);
}

bool isOperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return true;
    }
    else
    {
       return false;
    }
}

bool isOperand(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
    {
        return false;
    }
    else
    {
       return true;
    }
}

int precedence(char o)
{
    if(o == '*' || o == '/')
    {
        return 1;
    }
    else if(o == '+' || o == '-')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int main()
{
    stack s;
    s.createStack();
    s.push('#');
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    for(int i = 0; i < infix.length(); i ++)
    {
        if(isOperand(infix[i]))
        {
            cout << infix[i];
        }
        else if(infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if(infix[i] == ')') 
        {
            while(s.stackTop() != '(')
                cout << s.pop();
            s.pop();
        }
        else if(isOperator(infix[i]))
        {
            while(!s.isEmpty() && (precedence(s.stackTop()) >= precedence(infix[i])))
            {
                cout << s.pop();
            }
            s.push(infix[i]);
        }
    }

    while(s.stackTop() != '#')
    {
        cout << s.pop();
    }

    system("pause");
    return 0;
}