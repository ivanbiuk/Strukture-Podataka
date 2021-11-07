#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#define MAX_LINE (1024) 

struct _Polynom;
typedef struct _Polynom* Position;
typedef struct _Polynom {
	int coefficient;
	int exponent;
	Position next;
}Polynom;

int ReadFromFile(Position head1, Position head2);
int SortedInsert(Position head, int coefficient, int exponent);
Position CreateNewElement(int coefficient, int exponent);
int InsertAfter(Position position, Position newElement);
Position FindPrevious(Position head, Position position);
int DeleteElement(Position head, Position position);
int AppendPoly(Position head, Position newElement);
int AdditionPoly(Position poly1, Position poly2, Position additionResult);
int MultiplicationPoly(Position poly1, Position poly2, Position multiplicationResult);
int PrintPoly(Position first, char* polyName);
int FreeMemory(Position head);

#endif