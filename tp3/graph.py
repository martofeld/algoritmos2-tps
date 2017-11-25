from collections import Set

class _Edge:
    def __init__(self, vertex1, vertex2, information = []):
        self.vertex1 = vertex1
        self.vertex2 = vertex2
        self.information = information

    def add_to_information(self, info):
        self.information.append(info)

    def get_key(self):
        return set([self.vertex1, self.vertex2])

    def has_vertex(self, vertex):
        return vertex == self.vertex1 or vertex == self.vertex2

    def __eq__(self, other):
        return self.get_key() == other.get_key()

class Graph:
    def __init__(self):
        """Creates a new empty graph"""
        self.vertexes = {}
        self.edges = {}

    def add_vertex(self, name):
        """Adds a new vertex"""
        if not name in self.vertexes:
            self.vertexes[name] = Set()

    def remove_vertex(self, name):
        """"""
        self.vertexes.pop(name)
        for edge in self.edges:
            if edge.has_vertex(name):
                self.edges.pop(edge)


    def add_edge(self, vertex1, vertex2, information):
        """Adds a new edge between the two vertexes with the extra information"""
        key = set([vertex2, vertex1])
        if vertex2 in self.vertexes[vertex1]:
            self.edges[key].add_to_information(information)
        else:
            self.vertexes[vertex1].append(vertex2)
            self.vertexes[vertex2].append(vertex1)
            self.edges[key] = _Edge(vertex1, vertex2, [information])

    def remove_edge(self, vertex1, vertex2):
        """Removes the edge that connects the two vertexes"""
        key = set([vertex1, vertex2])
        self.vertexes[vertex2].pop(vertex1)
        self.vertexes[vertex1].pop(vertex2)
        self.edges.pop(key)

    def get_vertexes(self):
        """"""
        return self.vertexes.keys()

    def get_edges(self):
        """"""
        edges = set()
        for edge in self.edges:
            for info in edge.information:
                edges.append(info)
        return edges


    def get_vertexes_count(self):
        """Returns the amount of vertexes in the graph"""
        return len(self.vertexes.keys())

    def get_neighbours(self, vertex):
        """Returns the neighbours of a given vertex"""
        return self.vertexes[vertex]

    def get_information(self, vertex1, vertex2):
        """Returns the extra information from the edge of two vertexes"""
        key = set([vertex1, vertex2])
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