from queue import LifoQueue as Queue


def bfs(graph, starter_vertex):
    enqueued = [False for v in graph.vertices()]
    results = []
    q = Queue()
    q.put((starter_vertex, 0))
    results.append((starter_vertex, 0))
    enqueued[starter_vertex] = True
    while not q.empty():
        (u, pasos) = q.get()
        results.append((u, pasos))
        for w in graph.get_neighbours(u):
            if not enqueued[w]:
                q.put((w, pasos + 1))
                enqueued[w] = True
    return results


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
    father[start]= None
    visited[start]=True
    process=Queue()
    process.put(start)
    found_end = False
    while not process.empty() and not found_end:
        v=process.get()
        for w in graph.get_neighbours(v):
            visited[w]=True
            father[w]=v
            process.put(w)
            if w==end:
                found_end = True
                break
    return make_path(father,start,end)


def actors_at_distance(graph, actor, distance):
    """"""
    list= n_steps(graph,actor,distance)
    list.sort()
    return list


def popularity(graph, actor):
    """"""
    actors = 0
    neighbours = graph.get_neighbours(actor)
    actors += len(neighbours)
    for neighbour in neighbours:
        actors += len(graph.get_neighbours(neighbour)) - 1 # This way we remove myself
    movies = 0
    for edge in graph.get_edges_of_vertex(actor):
        movies += len(edge.get_information())

    return actors * movies


def similar(graph, actor):
    """"""
    # TODO

def n_steps(graph, vertex, n):
    visited = {}
    level = {}
    if vertex not in graph:
        return False
    #obtener el vertice
    level[vertex]=0
    process= Queue()
    process.put(vertex)
    visited[vertex]=True
    lista=[]
    while not process.empty():
        v= process.get()
        for w in graph.get_neighbours(v):
            if w not in visited:
                visited[w]=True
                level[w]=level[v]+1
                process.put(w)
            if level[w]==n:
                lista.append(w)
    return lista

def make_path(parents, start, end):
    v=end
    padre=parents[v]
    lista=[]
    while v != start:
        lista.insert(1,v)
        v=padre
        padre=parents[v]

def is_path(path, start, end):
    return path[0]==start and path[-1]==end

def similares(graph, vertex, n): #to do nombre
	if vertex not in graph:
		return False
	neighbours= graph.get_neighbours(vertex):
	actors={}
	for v in graph.get_vertex():
		number=compare_neighbours(graph,v,neighbours)
		actors[number]=v
	list_actors=actors.keys().sort()
	n_similars=[]
	for i in range(n):
		similar=actors[list_actors.pop()]
		n_similars.append(similar)
	return n_similars


def compare_neighbours(graph, vertex, list_):
	count=0
	for w in graph.get_neighbours(vertex):
		if w in list_:
			count+=1
	return count
