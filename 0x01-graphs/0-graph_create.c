#include "graphs.h"

/**
 * graph_create - Allocates new graph
 * Return: a new graph, NULL on failure
*/
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(*graph));
	if (!graph)
		return (NULL);
    graph->vertices = NULL;
	graph->nb_vertices = 0;
	return (graph);
}
