// Centrality Measures API implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"

NodeValues closenessCentrality(Graph g) {
	NodeValues nvs = {};
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = malloc(sizeof(double) * nvs.numNodes);
	for (int i = 0; i < nvs.numNodes; i++) {
		// for every node in the graph
		// find the reachable node
		// add them together 
		// then use the Wasserman and Faust formula to calculate 
		// the closeness of a node than place it into the NodeValues struct
		ShortestPaths paths = dijkstra(g, i);
		double reachable_node = 0;
		int sum_reachable_dist = 0;
		double closeness;
		for (int j = 0; j < nvs.numNodes; j++) {
			if (paths.dist[j] != INFINITY) {
				// if node is reachable
				reachable_node++;
				sum_reachable_dist += paths.dist[j];
			}
		}
		if (reachable_node <= 1) {
			// if isolated node
			closeness = 0.0;
			nvs.values[i] = closeness;
		} else {
			closeness = ((reachable_node - 1) / (nvs.numNodes - 1)) * ((reachable_node - 1) / sum_reachable_dist);
			nvs.values[i] = closeness;
		}	
		freeShortestPaths(paths);
	}
	return nvs;
}

// count number of node in a linked list
int count_link_list_node(PredNode *head, Vertex s, Vertex t, Vertex v) {
	int count = 0;
	if (s == t) {
		// for cases that s == t
		// return 1 to avoid samentation fault
		return 1;
	}
	if (head == NULL) {
		// if there is no shortest path, ie the first node in paths.pred is NULL
		return 1;
	}
	while (head != NULL) {
		// count how many shortest path it has
		count++;
		head = head->next;
	}	
	return count;
}

// count number of node that has target vertex in it in a linked list
double count_link_list_node_with_v(PredNode *head, Vertex target, ShortestPaths paths, Vertex s, Vertex t) {
	double count = 0;
	
	if (s == t) {
		// for cases that s == t == v
		// return 0 
		return count;
	}
	//printf("start vertex = %d, end vertex = %d, dist[t] = %d\n", s, t, paths.dist[t]);
	if (paths.dist[t] == INFINITY) {
		// if there is no shortest path, i.e dist for them is INFINITY
		return count;
	}
	PredNode *pred_head = paths.pred[t];
	while (head != NULL && pred_head != NULL) {
		// by following the end node predNote in the paths, we could find out the entire path
		// use that info to find count of target vertex in the list
		while (pred_head->v != s) {
			// go through the pred list to find if target vertex was in the paths from s to t
			Vertex vertex = pred_head->v;
			if (vertex == target) {
				// if there is the target vertex in the path, count++
				count++;
			}
			pred_head = paths.pred[vertex];
		}
		pred_head = pred_head->next;
		head = head->next;
	}
	return count;
}

NodeValues betweennessCentrality(Graph g) {
	NodeValues nvs = {};
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = malloc(sizeof(double) * nvs.numNodes);	
	ShortestPaths paths_array[nvs.numNodes];
	for (int i = 0; i < nvs.numNodes; i++) {
		paths_array[i] = dijkstra(g, i);
	}
	
	for (int i = 0; i < nvs.numNodes; i++) {
		nvs.values[i] = 0;
		// path from start node to end node:
		for (int start_node = 0; start_node < nvs.numNodes; start_node++) {
			ShortestPaths paths = paths_array[start_node];
			int total_num_shortest_path = 0;
			double num_shortest_path_v = 0;
			
			for (int end_node = 0; end_node < nvs.numNodes; end_node++) {
				PredNode *pred_head = paths.pred[end_node];
				double temp_betweenness = 0;
				// ingore all paths end with i and start node
				// so now if the reminding paths have vertex i included
				total_num_shortest_path = count_link_list_node(pred_head, start_node, end_node, i);
				num_shortest_path_v = count_link_list_node_with_v(pred_head, i, paths, start_node, end_node);
				temp_betweenness = num_shortest_path_v / total_num_shortest_path;
				nvs.values[i] += temp_betweenness;
			}	
		}
	}
	for (int i = 0; i < nvs.numNodes; i++) {
		freeShortestPaths(paths_array[i]);
	}
	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	NodeValues nvs = {};
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = malloc(sizeof(double) * nvs.numNodes);
	NodeValues centrality = betweennessCentrality(g);
	double normal_constant = 1/((nvs.numNodes - 1) * (double)(nvs.numNodes - 2));
	for (int i = 0; i < nvs.numNodes; i++) {
		nvs.values[i] = normal_constant * centrality.values[i];
	}
	freeNodeValues(centrality);
	return nvs;
}

void showNodeValues(NodeValues nvs) {

}

void freeNodeValues(NodeValues nvs) {
	free(nvs.values);
}

