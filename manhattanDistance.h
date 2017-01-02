#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include "make_maze.h"
#include "myNode.h"
#include "network.h"




int manhattanDistance(int u, int v)				
{
	int m1 = u / 8;
	int m2 = v / 8;
	int n1 = u % 8;
	int n2 = u % 8;
	if(n1 == 0)
	{
		n1 == 8;
		m1--;
	}
	if(n2 == 0)
	{
		n2 == 8;
		m2--;
	}
	if((m1 % 2) && (m2 % 2) || !(m1 % 2) && !(m2 % 2))
		return abs(m1-m2)+abs(n1-n2);
	else
		return abs(m1-m2)+abs((9-n1)-n2);
	
}

#endif