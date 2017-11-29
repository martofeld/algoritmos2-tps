class FifoQueue:
    def __init__(self):
        self.lista = []

    def get(self):
        if not self.empty():
            return self.lista.pop(0)

    def empty(self):
        return len(self.lista) == 0

    def put(self, dato):
        self.lista.append(dato)
        return

def make_path(parents, start, end):
    v = start
    parent = parents[v]
    final_path = []
    while v != end:
        final_path.append((parent, v))
        v = parent
        parent = parents[v]
    return final_path


def path(graph, start, end):
    if start not in graph or end not in graph:
        return []

    visited = {}
    visited[end] = True
    parents = {}
    parents[end] = None
    process = FifoQueue()
    process.put(end)
    v = None
    while not process.empty():
        v = process.get()
        if v == start:
            break

        for w in graph.get_neighbours(v):
            if w not in visited:
                visited[w] = True
                parents[w] = v
                process.put(w)

    if v != start:
        return []

    return make_path(parents, start, end)

def actors_at_distance(graph, actor, distance):
    """"""
    list = n_steps(graph, actor, distance)
    list.sort()
    return list


def popularity(graph, actor):
    """"""
    if not actor in graph:
        return -1

    actors = actors_at_distance(graph, actor, 2)
    movies_counted = set()
    movies_count = 0
    for actor in actors:
        for edge in graph.get_edges_of_vertex(actor):
            for movie in edge.get_information():
                if not movie in movies_counted:
                    movies_count += 1
                    movies_counted.add(movie)

    return len(actors) * movies_count


def n_steps(graph, vertex, n):
    if vertex not in graph:
        return False

    visited = {}
    level = {}
    process = FifoQueue()

    process.put(vertex)
    visited[vertex] = True
    level[vertex] = 0
    at_n_steps = []
    while not process.empty():
        v = process.get()
        for w in graph.get_neighbours(v):
            if w in visited:
                continue

            if level[v] == n-1 and not w in at_n_steps:
                at_n_steps.append(w)
            else:
                level[w] = level[v] + 1
                process.put(w)
            visited[w] = True
    return at_n_steps


def similar(graph, vertex, n):
    if vertex not in graph:
        return False
    neighbours = graph.get_neighbours(vertex)
    actors = {}
    for v in graph.get_vertexes():
        number = compare_neighbours(graph, v, neighbours)
        actors[number] = v
    list_actors = list(actors.keys())
    list_actors.sort()
    n_similars = []
    for i in range(n):
        similar = actors[list_actors.pop()]
        n_similars.append(similar)
    return n_similars


def compare_neighbours(graph, vertex, list_):
    count = 0
    for w in graph.get_neighbours(vertex):
        if w in list_:
            count += 1
    return count
