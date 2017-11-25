from queue import LifoQueue as Queue


def bfs(graph, starter_vertex):
    enqueued = [False for v in graph.vertices()]
    results = []
    q = Queue()
    q.put((starter_vertex, 0))
    results.append((starter_vertex, 0))
    enqueued[starter_vertex] = True
    while not q.is_empty():
        (u, pasos) = q.get()
        results.append((u, pasos))
        for w in graph.get_neighbours(u):
            if not enqueued[w]:
                q.put((w, pasos + 1))
                enqueued[w] = True
    return results


def path(graph, actor1, actor2):
    """"""
    # TODO


def actors_at_distance(graph, actor, distance):
    """"""
    # TODO


def popularity(graph, actor):
    """"""
    # TODO


def similar(graph, actor):
    """"""
    # TODO
