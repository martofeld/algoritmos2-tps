import sys
import graph_functions

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

    graph = create_graph(sys.argv[1])
    run_command(graph)


def create_graph(file):
    """"""
    actors_dict = {}
    dict = {}
    graph = Graph()
    with open(file, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip().split(',')
            actor = line[0]
            if actor in actors_dict:
                actor = actors_dict[actor]
            else:
                actors_dict[actor] = actor
            movies = line[1:]
            for movie in movies:
                if movie in dict:
                    dict[movie].append(actor)
                else:
                    dict[movie] = [actor]
            graph.add_vertex(actor)

    print(dict)
    for movie in dict:
        actors = dict[movie]
        # print(actors, "for", movie)
        for i in range(0, len(actors)):
            for j in range(i, len(actors)):
                if j != i:
                    graph.add_edge(actors[i], actors[j], movie)
    return graph


def run_command(graph):
    for line in sys.stdin:
        args = line.strip().split(' ')
        FUNCTIONS[args[0]](graph, *args[1:])  # Black magic


def path_to_kb(graph, actor):
    """"""
    graph_functions.path(graph, KB, actor)


def bacon_number(graph, actor):
    """"""
    # TODO


def bacon_number_gt_6(graph):
    """"""
    # TODO


def bacon_number_inf(graph):
    """"""
    # TODO


def average_kbn(graph):
    """"""
    # TODO


def actors_like(graph, max):
    """"""
    # TODO


def popularity_vs(graph, actor):
    """"""
    # TODO


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
