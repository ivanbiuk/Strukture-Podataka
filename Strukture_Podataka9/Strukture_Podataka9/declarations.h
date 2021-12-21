#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE (100)
#define MAX_NUMBER (89)
#define MIN_NUMBER (11)

struct _BinaryNode;
typedef struct _BinaryNode* Position;
typedef struct _BinaryNode {
	int number;
	Position left;
	Position right;
}BinaryNode;

struct _ListNode;
typedef struct _ListNode* ListPosition;
typedef struct _ListNode {
	int number;
	ListPosition next;
}ListNode;

Position Insert(Position current, Position newElement);
Position CreateNewElement(int value);
int Replace(Position current);
int UserEnteringInt();
ListPosition CreateNewListElement(int nodeNumber);
int InsertIntoList(ListPosition listHead, int newNumber);
int PrintIntoFile(ListPosition initialListHead, ListPosition replacedListHead);
int InsertTreeIntoList(Position root, ListPosition listHead);

#endif 