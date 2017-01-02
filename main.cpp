#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include "make_maze.h"
#include "draw_maze.h"
#include "myNode.h"
#include "network.h"
#include "DFS.h"
#include "Astar.h"
#include "onlineDFS.h"


using namespace std;

int main()
{
	cout<<"Welcome to the pathfinding agent programm!\n";
	network<myNode> net;
	vector<int> path0;
	vector<int> path;
	vector<int> path2;
	vector<int> path3;
	int goal,start;
	int input;

	makeMaze(net, goal, start);
	cout<<"This is the randomly generated maze:\n\n";
	drawMaze(net,path0,0);
start:
	cout<<endl;
	cout<<"Inorder to find the goal using DFS algorithm press 1\n";
	cout<<"Inorder to find the goal using A* algorithm press 2\n";
	cout<<"Inorder to find the goal using online DFS algorithm press 3\n";
	cout<<"Press 4 to exit\n";

	cin>>input;
	if(input == 1)
		goto dfs;
	if(input == 2)
		goto astar;
	if(input == 3)
		goto online;
	if(input == 4)
		goto exit;

dfs:

	DFS(net, start, path);
	drawPath(net,path);
	cout<<"Path is : "<<endl;
	for(int i = 0; i < path.size(); i++)
		cout<<path[i]+1<<" -> ";
	if(path.back() == goal)
		cout<<"Agent has rached Goal in "<<path.size()<<" steps using DFS algorithm.\n";
	else
		cout<<"Agent could not reach the goal.\n";
	goto start;

astar:
	
	aStar(net,start,goal,path2);
	reverse(path2.begin(),path2.end());
	drawPath(net,path2);
	for(int i = 0; i < path2.size(); i++)
		cout<<path2[i]+1<<" -> ";
	if(path2.back() == goal)
		cout<<"Agent has rached Goal in "<<path2.size()<<" steps using A* algorithm.\n";
	else
		cout<<"Agent could not reach the goal.\n";
	goto start;

online:

	onlineDFS(net, start, path3);
	drawPath(net,path3);
	cout<<"Path is : "<<endl;
	for(int i = 0; i < path3.size(); i++)
		cout<<path3[i]+1<<" -> ";
	if(path3.back() == goal)
		cout<<"Agent has rached Goal in "<<path3.size()<<" steps using online DFS algorithm.\n";
	else
		cout<<"Agent could not reach the goal.\n";
	goto start;

	
	exit:

	return 0;
}