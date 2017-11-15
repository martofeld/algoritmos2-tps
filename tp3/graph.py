class Graph:
    def __init__(self):
        """Creates a new empty graph"""
        self.vertexes = {}

    def add_vertex(self, name):
        """Adds a new vertex"""
        self.vertexes[name] = {}

    def remove_vertex(self, name):
        """"""
        self.vertexes.pop(name)
        for v in self.vertexes:
            self.vertexes[v].pop(name)

    def add_edge(self, vertex1, vertex2, information):
        """Adds a new edge between the two vertexes with the extra information"""
        self.vertexes[vertex1][vertex2] = information
        self.vertexes[vertex2][vertex1] = information

    def remove_edge(self, vertex1, vertex2):
        """Removes the edge that connects the two vertexes"""
        self.vertexes[vertex1].pop(vertex2)
        self.vertexes[vertex2].pop(vertex1)

    def get_vertexes(self):
        """"""
        return self.vertexes.keys()

    def get_vertexes_count(self):
        """Returns the amount of vertexes in the graph"""
        return len(self.vertexes.keys())

    def get_neighbours(self, vertex):
        """Returns the neighbours of a given vertex"""
        return self.vertexes[vertex].keys()

    def get_information(self, vertex1, vertex2):
        """Returns the extra information from the edge of two vertexes"""
        return self.vertexes[vertex1][vertex2]

    def __contains__(self, vertex):
        """Checks if a vertex is in the graph"""
        return vertex in self.vertexes

    def __iter__(self):
        """Returns an iterator for the graph"""
        return iter(self.vertexes)