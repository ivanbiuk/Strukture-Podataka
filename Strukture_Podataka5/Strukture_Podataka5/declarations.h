#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#define MAX_LENGTH (50) 

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement {
	double number;
	Position next;
}StackElement;

Position CreateStackElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* destination, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixFile(double* destination, char* fileName);
int InputFileName(char* fileName);

#endif 