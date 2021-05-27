#include "graphs.h"

/**
 * vertex_getter - get vertex with the given @content
 * @graph: a graph
 * @s1: content
 * @s2: content
 * @v1: vertex
 * @v2: vertex
 * Return:1 on success
*/
int vertex_getter(graph_t *graph, const char *s1,
	       const char *s2, vertex_t **v1, vertex_t **v2)
{
	vertex_t *vertex;

	if (!graph || !s1 || !s2)
		return (0);

	vertex = graph->vertices;
	while (vertex)
	{
		if (!strcmp(vertex->content, s1))
			*v1 = vertex;
		if (!strcmp(vertex->content, s2))
			*v2 = vertex;
		vertex = vertex->next;
	}
	if (!*v1 || !*v2)
		return (0);
	return (1);
}
/**
 * add_edge - add an edge
 * @src: source vertex
 * @dest: destination vertex
 * Return: 1 on success
 */
int add_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *edge, *new;

	if (!src || !dest)
		return (0);
	edge = src->edges;
	while (edge && edge->next)
		edge = edge->next;
	new = malloc(sizeof(*new));
	if (!new)
		return (0);
	new->next = NULL;
	new->dest = dest;
	if (!edge)
		src->edges = new;
	else
		edge->next = new;
	src->nb_edges += 1;
	return (1);
}

/**
 * delete_last_edge - delete last edge
 * @vertex: a vertex
 * Return: 0
*/
int delete_last_edge(vertex_t *vertex)
{
	edge_t *edge = NULL, *prev = NULL;

	if (!vertex)
		return (0);
	edge = vertex->edges;
	while (edge && edge->next)
		prev = edge, edge = edge->next;
	if (edge)
	{
		if (prev)
			prev->next = NULL;
		free(edge);
	}
	if (vertex->nb_edges > 0)
		vertex->nb_edges -= 1;
	return (1);
}

/**
 * graph_add_edge - add an edge
 * @graph: a graph
 * @src: source vertex
 * @dest: destination vertex
 * @type: enum
 * Return: 1 on success, or 0 on failure. On failure, no edge will be created
*/
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
	vertex_t *vertex1 = NULL, *vertex2 = NULL;

	if (!graph || !src || !dest ||
	    (type != UNIDIRECTIONAL && type != BIDIRECTIONAL))
		return (0);

	if (!vertex_getter(graph, src, dest, &vertex1, &vertex2))
		return (0);
	if (!add_edge(vertex1, vertex2))
		return (0);
	if (type == BIDIRECTIONAL && strcmp(src, dest))
		if (!add_edge(vertex2, vertex1))
		{
			delete_last_edge(vertex1);
			return (0);
		}

	return (1);
}
