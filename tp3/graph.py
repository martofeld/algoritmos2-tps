class Graph:
    def __init__(self, vertexes={}, edges={}):
        """Creates a new empty graph"""
        self.vertexes = vertexes
        self.edges = edges

    def add_vertex(self, name):
        """Adds a new vertex"""
        if name not in self:
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
