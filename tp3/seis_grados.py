import random
import heapq
from graph import Graph


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


def create_graph(file):
    """"""
    movies_dict = {}
    actors_dict = {}
    movies_name_holder = {}  # Saves strings for single usage

    with open(file, 'r', newline='', encoding="utf-8") as file:
        for line in file:
            line = line.strip().split(',')
            actor = line[0]
            movies = line[1:]

            actors_dict[actor] = set()
            for movie in movies:
                if movie not in movies_dict:
                    movies_dict[movie] = set()
                    movies_name_holder[movie] = movie
                else:
                    movie = movies_name_holder[movie]
                actors_dict[actor].add(movie)
                movies_dict[movie].add(actor)

    return Graph(actors_dict, movies_dict)


def make_path(parents, start, end):
    v = start
    parent = parents[v]
    final_path = []
    while v != end:
        final_path.append((parent, v))
        v = parent
        parent = parents[v]
    final_path.reverse()
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
    if actor not in graph or distance < 0:
        return []

    values = n_steps(graph, actor, distance)
    values.sort()
    return values


def popularity(graph, actor):
    """"""
    if not actor in graph:
        return False

    actors = actors_at_distance(graph, actor, 2)
    movies_counted = set()
    movies_count = 0
    for movie in graph.get_edges_of_vertex(actor):
        if movie not in movies_counted:
            movies_count += 1
            movies_counted.add(movie)
    print(movies_count)
    return len(actors) * movies_count


def n_steps(graph, vertex, n):
    if n == 0:
        return [vertex]

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
            visited[w] = True                
            level[w] = level[v] + 1
            process.put(w)
            if level[w] == n:
                at_n_steps.append(w)
    return at_n_steps


def similar(graph, vertex, n):
    if vertex not in graph:
        return False

    if n == 0:
        return []

    actors = {}

    random_walk(graph, vertex, actors)
    heap = []

    for i, (actor, value) in enumerate(actors.items()):
        if i < n:
            heapq.heappush(heap, (value, actor))  # Populate the first N
            continue
        if value > heap[0][0]:
            heapq.heappop(heap)
            heapq.heappush(heap, (value, actor))
    aux = [t for t in heap]
    aux.sort(key=lambda t: t[0], reverse=True)
    return [t[1] for t in aux]


def random_walk(graph, vertex, actors):
    original_neighbours = graph.get_neighbours(vertex)
    for i in range(random.randint(100, 200)):
        v = vertex
        for j in range(random.randint(20, 30)):
            neighbours = graph.get_neighbours(v)
            v = random.sample(neighbours, 1)[0]  # Sample returns a list
            if v in original_neighbours or v == vertex:  # If its a direct neighbour or the original ignore
                continue
            actors[v] = actors.get(v, 0) + 1


def compare_neighbours(graph, vertex, list_):
    count = 0
    for w in graph.get_neighbours(vertex):
        if w in list_:
            count += 1
    return count


# ------- PUBLIC API BECAUSE REQUIREMENTS -------
def camino(grafo, vertice1, vertice2):
    return path(grafo, vertice1, vertice2)


def actores_a_distancia(grafo, actor, distancia):
    return actors_at_distance(grafo, actor, distancia)


def popularidad(grafo, actor):
    return popularity(grafo, actor)


def similares(grafo, actor, n):
    return similar(grafo, actor, n)


def grafo_crear(archivo):
    return create_graph(archivo)
