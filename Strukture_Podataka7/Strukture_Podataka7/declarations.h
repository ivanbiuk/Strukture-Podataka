#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_SIZE (120)

struct _Directory;
typedef struct _Directory* Position;
typedef struct _Directory {
	char name[MAX_SIZE];
	Position sibling;
	Position child;
}Directory;

struct _StackElement;
typedef struct _StackElement* StackPosition;
typedef struct _StackElement {
	Position directory;
	StackPosition next;
}StackElement;


Position Insert(Position current, Position newElement);
Position CreateNewDirectory(char name[]);
StackPosition CreateStackElement(Position directory);
int Push(StackPosition head, StackPosition newStackElement);
Position Pop(StackPosition head, Position current);
int PrintAllSubdirectories(Position current);
Position MoveToSubdirectory(Position current, char* destinationName, StackPosition stack);
int FreeMemory(Position root);
int UserEnteringInt();

#endif
