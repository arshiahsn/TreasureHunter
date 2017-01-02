#ifndef MAKE_MAZE_H
#define MAKE_MAZE_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <ctime>
#include "network.h"
#include "myNode.h"

using namespace std;

int myRandom (int i) { return rand()%i;}

struct sort_pred {
		bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }
};

void makeMaze (network<myNode> & myNetwork, int & tGoal, int & tStart)
{
	srand ( unsigned ( time(0) ) );
	vector<int> temp;
	for(int i = 0; i < 64; i++)
		temp.push_back(i);
	random_shuffle(temp.begin(), temp.end(),myRandom );
	int Start = temp.back();
	tStart = Start;
	temp.pop_back();
	int Goal = temp.back();
	tGoal = Goal;
	temp.pop_back();
	int Blocked[7];
	for(int i = 0; i < 7; i++)
	{
		Blocked[i] = temp.back();
		temp.pop_back();
	}
	
	for(int i = 1; i <= 64; i++)
		myNetwork.add_node(myNode(i));
	myNetwork.info[Start].state = myNode::Start;
	myNetwork.info[Goal].state = myNode::Goal;
	for(int i = 0; i < 7; i++)
		myNetwork.info[Blocked[i]].state = myNode::Blocked;
	for(int i = 1; i <= 64; i++)
	{
		int m = i / 8;				// i = m * 8 + n
		int z = i % 8;
		int n;
		if (z == 0)
			n = 8;
		else n = z;
		if(m == 0 || (m == 1 && n == 8))	//First Row
		{
			if(n == 1)	//1
			{
				myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);	//Top
				myNetwork.add_edge(myNode(i), myNode(i + 1), 2);			//Right
			}
			else
				if(n == 8)		//8
				{
					myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);	//Top
					myNetwork.add_edge(myNode(i), myNode(i - 1), 2);	//Left
				}
				else		//Others
				{
					myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);	//Top
					myNetwork.add_edge(myNode(i), myNode(i - 1), 2);	//Left	
					myNetwork.add_edge(myNode(i), myNode(i + 1), 3);	//Right
				}

		}
		else
		if(m == 7 || (m == 8 && n == 8))			//Last row	
		{	
			if(n == 1)								//57
			{
				myNetwork.add_edge(myNode(i), myNode(i + 1), 1);		//Left
				myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 2);	//Bottom
			}
			else	
				if(n == 8)							//64
				{
					myNetwork.add_edge(myNode(i), myNode(i - 1), 1);		//Right
					myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 2);	//Bottom
				}
				else								//Others
				{
					myNetwork.add_edge(myNode(i), myNode(i + 1), 1);		//Left
					myNetwork.add_edge(myNode(i), myNode(i - 1), 2);		//Right
					myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 3);		//Bottom
				}
					

		}
		else								//Other rows
		{
			if(m%2 == 0)
			{
				if(n == 8 || n == 1)				//Edge
				{
					myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);
					if(n == 8)
						myNetwork.add_edge(myNode(i), myNode(i - 1), 2);
					else
						myNetwork.add_edge(myNode(i), myNode(i + 1), 2);
					myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 3);
				}
				else
				{
					myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);
					myNetwork.add_edge(myNode(i), myNode(i - 1), 2);
					myNetwork.add_edge(myNode(i), myNode(i + 1), 3);
					myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 4);

				}

			}
			else
			{
				if(n == 1 || n == 8)				//Edge
				{
					myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);
					if(n == 1)
						myNetwork.add_edge(myNode(i), myNode(i - 1), 2);
					else
						myNetwork.add_edge(myNode(i), myNode(i + 1), 2);
					myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 3);
				}
				else
				{
					myNetwork.add_edge(myNode(i), myNode(i +(17-2*n)), 1);
					myNetwork.add_edge(myNode(i), myNode(i + 1), 2);
					myNetwork.add_edge(myNode(i), myNode(i - 1), 3);
					myNetwork.add_edge(myNode(i), myNode(i -(2*n-1)), 4);

				}


			}

		}
		
	}

	for(int i = 0; i < 64; i++)
		sort(myNetwork.adjacencyList[i].begin(),myNetwork.adjacencyList[i].end(), sort_pred());


}





#endif