#ifndef MYNODE_H
#define MYNODE_H


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "manhattanDistance.h"




struct myNode {

	enum states {Start,Goal,Blocked,Normal};
	states state;
	int num;
	myNode* parent;
	bool opened;
	bool closed;
	int g,h,f;
	bool operator < (const myNode & n2) const {
		return num < n2.num;
	}
	bool operator == (const myNode & n2) const {
		return num == n2.num;
	}

	void computeF(int Goal)
	{
			g = parent->g;
			h = manhattanDistance(num,Goal);
			f = g + h;
	}
	myNode(int number)
	{
			num = number;
			state = Normal;
			parent = NULL;
			opened = false;
			closed = false;
	}
	myNode() {}

	};

#endif