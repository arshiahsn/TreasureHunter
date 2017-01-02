#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include "make_maze.h"
#include "myNode.h"
#include "network.h"
#include "manhattanDistance.h"





void setF(network<myNode> & myNetwork, int start, int goal)
{

	for(int i = 0; i < myNetwork.info.size(); i++)
	{
		myNetwork.info[i].g = manhattanDistance(myNetwork.info[i].num,start);
		myNetwork.info[i].h = manhattanDistance(myNetwork.info[i].num,goal);
		myNetwork.info[i].f = myNetwork.info[i].g + myNetwork.info[i].h;
	}
}

void aStar(network<myNode> & myNetwork, int start, int goal, vector<int> & path)
{
	int current;
	int child;
	vector<myNode> info = myNetwork.all_data();

	vector<int> openList;
    vector<int> closedList;

	//
	unsigned int n = 0;

    // Add the start point to the openList
	openList.push_back(start);
    info[start].opened = true;

    while (n == 0 || (current != goal && n < 64))
    {
        // Look for the smallest F value in the openList and make it the current point
		for (int i = 0; i < openList.size(); ++ i)
        {
			if (i == 0 || info[openList[i]].f <= info[current].f )
            {
                current = openList[i];
            }
        }

        // Stop if we reached the end
        if (current == goal)
        {
            break;
        }

        // Remove the current point from the openList
		if(find(openList.begin(),openList.end(),current) != openList.end())
			openList.erase(find(openList.begin(),openList.end(),current));
        info[current].opened = false;

        // Add the current point to the closedList
        closedList.push_back(current);
        info[current].closed = true;

        // Get all current's adjacent walkable points
        vector<pair<myNode,int>>::const_iterator i;
		const vector<pair<myNode,int>> & neighbours = myNetwork.list_of_connected_nodes_of_node(myNetwork.info[current]);
		for(i = neighbours.begin(); i != neighbours.end(); ++i)
        {
            
                // Get this point
			child = i->first.num-1; 

                // If it's closed or not walkable then pass
			if (info[child].closed || info[child].state == myNode::Blocked)
                {
                    continue;
                }

  
                // If it's already in the openList
                if (info[child].opened)
                {
                    // If it has a wroste g score than the one that pass through the current point
                    // then its path is improved when it's parent is the current point
                    if (manhattanDistance(child,goal) > manhattanDistance(current,child))
                    {
                        // Change its parent and g score
						info[child].parent = &info[current] ;
						info[child].computeF(goal);
                    }
                }
                else
                {
                    // Add it to the openList with current point as parent
                    openList.push_back(child);
                    info[child].opened = true;

                    // Compute it's g, h and f score
					info[child].parent = &info[current];
                    info[child].computeF(goal);
                }
            
        }

        n ++;
    }

    // Reset
    for (int i = 0; i < openList.size(); ++ i)
    {
        info[openList[i]].opened = false;
    }
    for (int i = 0; i < closedList.size(); ++ i)
    {
        info[closedList[i]].closed = false;
    }

    // Resolve the path starting from the end point
	while (info[current].parent && current != start)
    {
        path.push_back(current);
		current = info[current].parent->num-1;
        n ++;
    }

    
}
	//


#endif