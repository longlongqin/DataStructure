#ifndef DSACPP_GRAPH_PFS_H_
#define DSACPP_GRAPH_PFS_H_

#include "Graph.h"

template<class Tv, class Te, typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
	reset(); int v = s;

	do 
	{
		if (Status(v) == DISCOVERED)
		{
			PFS(v, prioUpdater);
		}

	} while (s != (v = (v % n_)));
}

template<class Tv, class Te, typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater)
{
	priority(s) = 0; Status(s) = VISITED; parent(s) = -1;

	while (1)
	{
		for (int w = firstNbr(s); w > -1; w = nextNbr(s, w))
			prioUpdater(this, s, w);

		for (int shortest = INT_MAX, w = 0; w < n_; w++)
		{
			if(Status(w) == UNDISCOVERED)
				if (priority(w) < shortest)
				{
					shortest = priority(w);
					s = w;
				}
		}

		if (Status(s) == VISITED)
			break;

		Status(s) = VISITED; type(parent(s), s) = TREE;
	}
}

#endif
