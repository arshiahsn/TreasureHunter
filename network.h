#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

template <class T>
class network {
public:

	vector<vector<pair<int,int>> > adjacencyList;               //list of nodes adjacent to a node
	vector<T> info;
	map<T, int> forwardIndex;
	int fiSize;
	size_t size() {
		return info.size();
	}
	network(){fiSize = -1;};

	vector<T> & all_data() {
		return info;
		
	}
	
	void add_edge(const T & u, const T & v, double w) {
		if (! have_node(u))
			add_node(u);
		if (! have_node(v))
			add_node(v);
		
		int indexOfU = get_index_of_node(u);
		int indexOfV = get_index_of_node(v);
		if(!have_edge(u,v))
			adjacencyList[indexOfU].push_back(make_pair(indexOfV, w));
		//if(!have_edge(v,u))
		//	adjacencyList[indexOfV].push_back(make_pair(indexOfU, w));
		
	}
	
	void delete_edge(const T & u, const T & v) {
		// make sure edge exists first, if edge doesn't exist, functionlaity is unkown
		int indexOfU = get_index_of_node(u);
		int indexOfV = get_index_of_node(v);
		
		adjacencyList[indexOfU].erase(find(adjacencyList[indexOfU].begin(), adjacencyList[indexOfU].end(), indexOfV));
		adjacencyList[indexOfV].erase(find(adjacencyList[indexOfV].begin(), adjacencyList[indexOfV].end(), indexOfU));
	}
	
	
	vector<pair<T,int>> list_of_connected_nodes_of_node (const T & u) {
		vector<pair<T,int>> connectedNodes;
		int indexOfU = get_index_of_node(u);
		for (int i = 0; i < adjacencyList[indexOfU].size(); i++)
			connectedNodes.push_back(make_pair(get_data_of_index(adjacencyList[indexOfU][i].first),adjacencyList[indexOfU][i].second));
		return connectedNodes;
	}


	int return_recent (const T & u) {
		int indexOfU = get_index_of_node(u);
		return adjacencyList[indexOfU].back().second;
	}
	

	int get_index_of_node (const T & u) {
		return forwardIndex[u];
	}
	
	T & get_data_of_index (const int u) {
		return info[u];
	}
	
	bool have_node (const T & u) const{
		return forwardIndex.find(u) != forwardIndex.end();
	}

	bool have_edge (const T & u, const T & v) {	//Have edge in first node's database
		int indexOfU = get_index_of_node(u);
		int indexOfV = get_index_of_node(v);
		/*vector<pair<int,int>> tempList = adjacencyList[indexOfU];
		sort(tempList.begin(),tempList.end());*/
		vector<int> tempList;
		vector<pair<int,int>>::iterator it;
		for (it = adjacencyList[indexOfU].begin();it != adjacencyList[indexOfU].end(); it++)
			tempList.push_back(it->first);
		sort(tempList.begin() , tempList.end());
		return (binary_search(tempList.begin() , tempList.end() , indexOfV));
		
	}
	
	void add_node (const T & u) {
	if(!have_node(u))
	if (forwardIndex.insert(make_pair(u, forwardIndex.size()  )).second)
	{
		adjacencyList.resize(adjacencyList.size() + 1);
		info.push_back(u);
	}
	}

	
};



#endif