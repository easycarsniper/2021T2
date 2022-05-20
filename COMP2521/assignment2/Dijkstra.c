// Dijkstra API implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"


// if the new distance is smaller than the original dist
// free the existing nodes and change it then change pred
void new_dist(AdjList head, int v_out_w, ShortestPaths sps, Vertex src_vertex) {
	sps.dist[head->v] = v_out_w;
	PredNode *pred_head = sps.pred[head->v];
	while (pred_head != NULL) {
		// free all the previous pred if any
		PredNode *temp = pred_head;
		pred_head = pred_head->next;
		free(temp);
	}		
	PredNode *newNode = malloc(sizeof(struct PredNode));
	newNode->v = src_vertex;
	newNode->next = NULL;
	sps.pred[head->v] = newNode;
	return;
}

// if the new distance is equal than the original dist
// expend the list with the new source vertex
void expend_dist(AdjList head, ShortestPaths sps, Vertex src_vertex) {
	PredNode *pred_head = sps.pred[head->v];
	PredNode *pred_prev = NULL;
	while (pred_head != NULL) {
		// go to the end of the linked list
		pred_prev = pred_head;
		pred_head = pred_head->next;
	}				
	PredNode *newNode = malloc(sizeof(struct PredNode));
	newNode->v = src_vertex;
	newNode->next = NULL;
	pred_prev->next = newNode;
}

ShortestPaths dijkstra(Graph g, Vertex src) {
	ShortestPaths sps = {};
	sps.numNodes = GraphNumVertices(g);
	sps.src = src;
	int *dist = malloc(sizeof(int)*sps.numNodes);
	PredNode **pred = malloc(sizeof(int *)*sps.numNodes);
	sps.dist = dist;
	sps.pred = pred;
	AdjList adj_list_out[sps.numNodes];
	bool v_set[sps.numNodes];

	for (int i = 0; i < sps.numNodes; i++) {
		// initialize all distance as inf, pred as NULL, and adj_list in and out
		sps.dist[i] = INFINITY;
		sps.pred[i] = NULL;
		v_set[i] = false;
		adj_list_out[i] = GraphOutIncident(g, i);
	}

	sps.dist[src] = 0;
	PQ queue = PQNew();
	PQInsert(queue, src, 0);
	while (PQIsEmpty(queue) == false) {
		// while the queue is not empty
		// dequeue the first prioity one
		// based on the out vertex 
		// insert it into the queue
		Vertex src_vertex = PQDequeue(queue);
		AdjList head = adj_list_out[src_vertex];
		if (v_set[src_vertex] == false) {
			// if the node hasnt been visit
			v_set[src_vertex] = true;
			while (head != NULL) {
				// for every adj node
				// insert it into the queue
				// change dist and pred if needed
				PQInsert(queue, head->v, head->weight);
				int v_out_w = head->weight + dist[src_vertex];
				if (dist[head->v] > v_out_w) {
					// if the new distance is smaller than the original dist
					// free the existing node and change it then change pred
					new_dist(head, v_out_w, sps, src_vertex);			
				} else if (dist[head->v] == v_out_w) {
					// if the new distance is equal than the original dist
					// expend the list with the new source vertex
					expend_dist(head, sps, src_vertex);
				}
				head = head->next;
			}
		} else {
			// if the node dist reduced after new and shorter route being updated on other node
			// renew it
			while (head != NULL) {
				int v_out_w = head->weight + dist[src_vertex];
				if (dist[head->v] > v_out_w) { 
					new_dist(head, v_out_w, sps, src_vertex);
				} 
				head = head->next;
			}
		}
	}
	PQFree(queue);
	return sps;
}

void showShortestPaths(ShortestPaths sps) {
	int i = 0;
	printf("Num of vertex = %d, source vertex = %d", sps.numNodes, sps.src);
	while (i < sps.numNodes) {
		printf("Num %d, sps.dist[i] = %d\n", i, sps.dist[i]);
		i++;
	}
}

void freeShortestPaths(ShortestPaths sps) {
	free(sps.dist);
	for (int i = 0; i < sps.numNodes; i++) {
		// free all the node in sps.pred[i]
		PredNode *pred_head = sps.pred[i];
		while (pred_head != NULL) {
			// free all the previous pred if any
			PredNode *temp = pred_head;
			pred_head = pred_head->next;
			free(temp);
		}
	}
	free(sps.pred);
}

