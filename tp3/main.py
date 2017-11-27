import sys
import graph_functions

from datetime import datetime
from graph import Graph

PATH_TO_KB = "camino_hasta_KB"
BACON_NUMBER = "bacon_number"
BACON_NUMBER_GT_6 = "bacon_number_mayor_a_6"
BACON_NUMBER_INF = "bacon_number_infinito"
AVERAGE_KBN = "KBN_promedio"
ACTORS_LIKE = "similares_a_KB"
POPULARITY_VS = "popularidad_contra_KB"
MOVIES_COUNT = "cantidad_peliculas"
ACTORS_COUNT = "cantidad_actores"
KB = "Bacon Kevin"


def main():
    if len(sys.argv) != 2:
        print("Wrong params")
        exit(1)

    print ("loading file", datetime.now())
    graph = create_graph(sys.argv[1])
    print ("finished loading file", datetime.now())
    run_command(graph)


def create_graph(file):
    """"""
    dict = {}
    graph = Graph()
    with open(file, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip().split(',')
            actor = line[0]
            movies = line[1:]
            for movie in movies:
                if movie in dict:
                    dict[movie].append(actor)
                else:
                    dict[movie] = [actor]
            graph.add_vertex(actor)

    for movie in dict:
        actors = dict[movie]
        for i in range(0, len(actors)):
            for j in range(0, len(actors)):
                if j != i:
                    graph.add_edge(actors[i], actors[j], movie)
    return graph


def run_command(graph):
    for line in sys.stdin:
        args = line.strip().split(' ')
        FUNCTIONS[args[0]](graph, *args[1:])  # Black magic


def movie_path(grah, path):
    for i in range(len(path)-1):
        information=graph.get_information(lista[i],lista[i+1])
        step=(path[i],path[i+1],information[0])
        path.append(step)
    return path

def path_to_kb(graph, actor):
    """"""
    path = graph_functions.path(graph, KB, actor)
    movie_path = movie_path(graph, path)
    for step in movie_path:
        print("'{}' actuo con '{}' en '{}'\n").format(step[0],step[1],step[2])
    
def bacon_number(graph, actor):
    """"""
    if actor not in graph.get_vertexes():
        print("No hay un camino posible de {} a Kevin Bacon\n").format(actor)
        return
    path = graph_functions.path(graph, KB, actor)
    bacon_number=len(path)
    if not bacon_number:
        return -1
    return bacon_number

    >>> Con KBN igual a 6: N actores

def bacon_number_gt_6(graph):
    """"""
    kb_numbers={}
    print("Los actores con un KBN mayor a 6 son:\n")
    for actor in graph.get_vertexes():
        number=bacon_number(graph,actor)
        if number>=6:
            if number not in actors:
                kb_numbers[number]=0
            kb_numbers[number]+=1
    keys=kb_numbers.keys().sort()
    for i in keys:
        print("Con KBN igual a {}: {} actores").format(i,actors[i])
#que pasa si no hay?



def bacon_number_inf(graph):
    """"""
    list = []
    for vertex in graph:
        path = graph_functions.path(graph, vertex, KB)
        if not path:
            list.append(vertex)
    if not list:
        print("No hay actores con KBN infinito")
    else:
        print("Los actores con un Bacon Number infinito son", len(list))


def average_kbn(graph):
    """"""
    count=0
    actors=0
    for actor in graph.get_vertexes():
        number=bacon_number(graph, actor)
        if number!=-1:
            count+=number
            actors+=1
    return count//actors


def actors_like(graph, max):
    """"""
    # TODO

def popularity_vs(graph, actor):
    """"""
    pop_actor = graph_functions.popularity(actor)
    pop_kb = graph_functions.popularity(KB)
    amount = (pop_actor * 100 / pop_kb)
    print("'{}' es {} de lo popular que es Kevin Bacon".format(actor, amount))


def movies_count(graph):
    """"""
    edges = graph.get_edges()
    count = len(edges)
    print("El dataset contiene", count, "peliculas")


def actors_count(graph):
    """"""
    count = graph.get_vertexes_count()
    print("El dataset contiene", count, "actores")


FUNCTIONS = {
    PATH_TO_KB: path_to_kb,
    BACON_NUMBER: bacon_number,
    BACON_NUMBER_GT_6: bacon_number_gt_6,
    BACON_NUMBER_INF: bacon_number_inf,
    AVERAGE_KBN: average_kbn,
    ACTORS_LIKE: actors_like,
    POPULARITY_VS: popularity_vs,
    MOVIES_COUNT: movies_count,
    ACTORS_COUNT: actors_count,
}

if __name__ == '__main__':
    main()
