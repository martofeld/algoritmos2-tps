class _Edge:
    def __init__(self, vertex1, vertex2, information=[]):
        self.vertex1 = vertex1
        self.vertex2 = vertex2
        self.key = _Key(vertex1, vertex2)
        self.information = information

    def add_to_information(self, info):
        self.information.append(info)

    def get_key(self):
        return self.key

    def has_vertex(self, vertex):
        return vertex == self.vertex1 or vertex == self.vertex2

    def __eq__(self, other):
        return self.key == other.key

    def __hash__(self):
        return hash(self.vertex1) * hash(self.vertex2)


class _Key:
    def __init__(self, k1, k2):
        self.k1 = k1
        self.k2 = k2

    def __eq__(self, other):
        return (self.k1 == other.k1 and self.k2 == other.k2) or (self.k1 == other.k2 and self.k2 == other.k1)

    def __hash__(self):
        return hash(self.k1) * hash(self.k2)


class Graph:
    def __init__(self):
        """Creates a new empty graph"""
        self.vertexes = {}
        self.edges = {}

    def add_vertex(self, name):
        """Adds a new vertex"""
        if not name in self.vertexes:
            self.vertexes[name] = set()

    def remove_vertex(self, name):
        """"""
        self.vertexes.pop(name)
        for edge in self.edges:
            if edge.has_vertex(name):
                self.edges.remove(edge)

    def add_edge(self, vertex1, vertex2, information):
        """Adds a new edge between the two vertexes with the extra information"""
        key = _Key(vertex1, vertex2)
        if vertex2 in self.vertexes[vertex1]:
            self.edges[key].add_to_information(information)
        else:
            self.vertexes[vertex1].add(vertex2)
            self.vertexes[vertex2].add(vertex1)
            self.edges[key] = _Edge(vertex1, vertex2, [information])

    def remove_edge(self, vertex1, vertex2):
        """Removes the edge that connects the two vertexes"""
        key = _Key(vertex1, vertex2)
        self.vertexes[vertex2].remove(vertex1)
        self.vertexes[vertex1].remove(vertex2)
        self.edges.pop(key)

    def get_vertexes(self):
        """"""
        return self.vertexes.keys()

    def get_edges(self):
        """"""
        edges = set()
        for edge in self.edges:
            for info in edge.information:
                edges.add(info)
        return edges

    def get_vertexes_count(self):
        """Returns the amount of vertexes in the graph"""
        return len(self.vertexes.keys())

    def get_neighbours(self, vertex):
        """Returns the neighbours of a given vertex"""
        return self.vertexes[vertex]

    def get_information(self, vertex1, vertex2):
        """Returns the extra information from the edge of two vertexes"""
        key = _Key(vertex1, vertex2)
        return self.edges[key].information

    def are_connected(self, vertex1, vertex2):
        """"""
        return vertex2 in self.vertexes[vertex1]

    def __contains__(self, vertex):
        """Checks if a vertex is in the graph"""
        return vertex in self.vertexes

    def __iter__(self):
        """Returns an iterator for the graph"""
        return iter(self.vertexes)
    
   

def n_steps(graph, vertex, n):
    visited = {}
    level = {}
    if vertex not in graph:
        return False
    #obtener el vertice
    level[vertex]=0
    process= Cola()
    encolar.process(vertex)
    visited[vertex]=True 
    lista=[]
    while not process.esta_vacia():
        v= process.desencolar()
        for w in graph.get_neighbours(v):
            if w not in visited:
                visited[w]=True
                level[w]=level[v]+1
                process.encolar(w)
            if level[w]==n:
                lista.append(w)
    return lista

def path(graph, start, end):
    if start not in graph or end not in graph:
        return []
    path=[]
    path.append(start)
    if start==end:
        return path
    visited={}
    father={}
    #obtener start
    father[start]= ne
    visited[start]=True
    process=Cola()
    process.encolar(start)
    while not process.esta_vacia():
        v=process.desencolar()
        for w in graph.get_neighbours(v)::
            visited[w]=True
            father[w]=v
            process.encolar(w)
        if w==end:
            break
    return make_path(father,start,end)

def make_path(father, start, end):
    v=end
    padre=father[v]
    lista=[]
    while v != start:
        lista.insert(1,v)
        v=padre
        padre=father[v]

def is_path(path, start, end):
    return path[0]=start and path[-1]=end


def actores_a_distancia(graph, actor, n):
    lista= n_steps(graph,actor1,n)
    lista.sort()
    return lista

def camino(graph,actor1, actor2):
    return path(graph, actor1, actor2)
