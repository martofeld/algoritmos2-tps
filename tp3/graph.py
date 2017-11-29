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

    def get_information(self):
        return self.information

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
        if not name in self:
            self.vertexes[name] = set()

    def remove_vertex(self, name):
        """"""
        if not name in self:
            return
        edges = self.vertexes.pop(name)
        for edge in edges:
            self.edges[edge].remove(name)

    def add_edge(self, vertex1, vertex2, information):
        """Adds a new edge between the two vertexes with the extra information"""
        if vertex1 not in self or vertex2 not in self:
            raise KeyError("Algun vertice no esta")

        if information not in self.edges:
            self.edges[information] = set()

        self.vertexes[vertex1].add(information)
        self.vertexes[vertex2].add(information)
        self.edges[information].add(vertex1)
        self.edges[information].add(vertex2)
        print(len(self.edges))

    def remove_edge(self, vertex1, vertex2):
        """Removes the edge that connects the two vertexes"""
        # TODO, was not needed yet

    def get_vertexes(self):
        """"""
        return self.vertexes.keys()

    def get_edges(self):
        """"""
        return self.edges.keys()

    def get_vertexes_count(self):
        """Returns the amount of vertexes in the graph"""
        return len(self.vertexes.keys())

    def get_neighbours(self, vertex):
        """Returns the neighbours of a given vertex"""
        neighbours = set()
        edges = self.vertexes[vertex]
        for edge in edges:
            for neighbour in self.edges[edge]:
                neighbours.add(neighbour)
        return neighbours

    def get_information(self, vertex1, vertex2):
        """Returns the extra information from the edge of two vertexes"""
        vertex1_info = self.vertexes[vertex1]
        vertex2_info = self.vertexes[vertex2]
        return vertex1_info.intersection(vertex2_info)

    def get_edges_of_vertex(self, vertex):
        return self.vertexes[vertex]

    def __contains__(self, vertex):
        """Checks if a vertex is in the graph"""
        return vertex in self.vertexes

    def __iter__(self):
        """Returns an iterator for the graph"""
        return iter(self.vertexes)