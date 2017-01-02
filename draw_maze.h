#ifndef DRAW_MAZE_H
#define DRAW_MAZE_H

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <iomanip>
#include "make_maze.h"
#include "myNode.h"
#include "network.h"

void sleepcp(int milliseconds);

void sleepcp(int milliseconds) 
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

void drawMaze(network<myNode> & myNetwork, vector<int> path,int cnt)
{
	int tmpcnt = cnt;
	vector<int> temp = path;
	sort(temp.begin(),temp.end());
	for(int i = 0 ;i < 10; i++)
	{
		cout<<setw(30);
		for(int j = 0;j < 10; j++)
		{
			if(i == 0 || i == 9)
				cout<<"# ";
			else
				if(j == 0 || j == 9)
					cout<<"# ";
				else
					if(i%2 == 0)
					{
						if(myNetwork.info[8*(8-i)+j-1].state == myNode::Goal)
							cout<<"G ";
						else
						if(myNetwork.info[8*(8-i)+j-1].state == myNode::Start)
							cout<<"S ";
						else
						if(myNetwork.info[8*(8-i)+j-1].state == myNode::Blocked)
							cout<<"# ";
						else
						if(binary_search(temp.begin(),temp.end(),myNetwork.info[8*(8-i)+j-1].num-1))
							{
								if(cnt)
								{
									if((find(path.begin(),path.end(),myNetwork.info[8*(8-i)+j-1].num-1) - path.begin()) <= tmpcnt)
									{
										cout<<"* ";
										cnt--;
									}
									else
										cout<<"  ";

								}
								else
									cout<<"  ";
							}
						else
							cout<<"  ";
					}
					else
					{
						
						if(myNetwork.info[8*(8-i)+(8-j)].state == myNode::Goal)
							cout<<"G ";
						else
						if(myNetwork.info[8*(8-i)+(8-j)].state == myNode::Start)
							cout<<"S ";
						else
						if(myNetwork.info[8*(8-i)+(8-j)].state == myNode::Blocked)
							cout<<"# ";
						else
						if(binary_search(temp.begin(),temp.end(),myNetwork.info[8*(8-i)+(8-j)].num-1))
							{
								if(cnt)
								{
									if((find(path.begin(),path.end(),myNetwork.info[8*(8-i)+(8-j)].num-1) - path.begin()) <= tmpcnt)									{
										cout<<"* ";
										cnt--;
									}
									else
										cout<<"  ";
								}
								else
									cout<<"  ";
							}
						else
							cout<<"  ";

					}



		}
		cout<<endl;

	}



}

void drawPath(network<myNode> & myNetwork, vector<int> path)
{
	
	for(int i = 1;i <= path.size(); i++)
	{
		drawMaze(myNetwork,path,i);
		sleepcp(300);
		if(i != path.size())
			system("cls");
	}
}

#endif