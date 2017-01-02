#ifndef ONLINEDFS_H
#define ONLINEDFS_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include "make_maze.h"
#include "myNode.h"
#include "network.h"

bool onlineDFSUtil(network<myNode> & myNetwork, int v, bool visited[], vector<int> & path)
{
    visited[v] = true;	
	path.push_back(v);
	if(myNetwork.info[v].state == myNode::Goal)
		return true;
    vector<pair<myNode,int>>::const_iterator i;
	const vector<pair<myNode,int>> & neighbours = myNetwork.list_of_connected_nodes_of_node(myNetwork.info[v]);
    for(i = neighbours.begin(); i != neighbours.end(); ++i)
		if(!visited[i->first.num-1] && i->first.state != myNode::Blocked)
				if(onlineDFSUtil(myNetwork,i->first.num-1, visited,path))
				return true;
	return false;

}

void onlineDFS(network<myNode> & myNetwork, int v, vector<int> & path)
{
 bool visited[64];
    for(int i = 0; i < 64; i++)
        visited[i] = false;
    onlineDFSUtil(myNetwork, v, visited , path);

}


#endif