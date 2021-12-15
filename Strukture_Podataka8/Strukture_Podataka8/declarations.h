#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_SIZE (80)

struct _BinaryNode;
typedef struct _BinaryNode* Position;
typedef struct _BinaryNode {
	int number;
	Position left;
	Position right;
}BinaryNode;

struct _QueueElement;
typedef struct _QueueElement* QPosition;
typedef struct _QueueElement {
	Position treeNode;
	QPosition next;
}QueueElement;

Position Insert(Position current, Position newElement);
Position CreateNewElement(int number);
int InorderPrint(Position current);
int PreorderPrint(Position current);
int PostorderPrint(Position current);
int LevelorderPrint(QPosition qHead, Position current);
int UserEnteringInt();
Position SearchTree(Position current, int number);
Position FindMaxInLeft(Position current);
Position DeleteElement(Position current, int searchedNum);
QPosition CreateQueueElement(Position node);
int Push(QPosition head, QPosition newQElement);
Position Pop(QPosition head);
QPosition FindPenultimateQElement(QPosition head);

#endif 
