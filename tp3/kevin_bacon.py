import sys
import seis_grados as graph_functions
import re

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

    graph = graph_functions.create_graph(sys.argv[1])
    run_command(graph)


def run_command(graph):
    for line in sys.stdin:
        args = re.split("\s(?=')", line.strip())
        print(args)

        func = FUNCTIONS.get(args[0], None)
        if func:
            func(graph, *args[1:])  # Black magic
        else:
            print("No existe el comando especificado")


def complete_information(graph, path):
    complete_path = []
    for sth in path:  # Assuming path is a list of touples of the actors
        actor1, actor2 = sth
        information = graph.get_information(actor1, actor2)
        step = (actor1, actor2, information.pop())
        complete_path.append(step)
    return complete_path


def path_to_kb(graph, actor):
    """"""
    path = graph_functions.bfs(graph, KB, actor)
    movie_path = complete_information(graph, path)
    for step in movie_path:
        print("'{}' actuo con '{}' en '{}'".format(step[0], step[1], step[2]))


def obtain_bacon_number(graph, actor):
    """"""
    if actor not in graph.get_vertexes():
        print("No hay un camino posible de {} a Kevin Bacon").format(actor)
        return
    path = graph_functions.bfs(graph, KB, actor)
    bacon_number = len(path)
    if not bacon_number:
        return -1
    return bacon_number


def bacon_number(graph, actor):
    bn = obtain_bacon_number(graph, actor)
    print("'{}' tiene un Bacon Number de {}".format(actor, bn))


def bacon_number_gt_6(graph):
    """"""
    kb_numbers = {}
    distance = 6
    should_continue = True
    while should_continue:
        actors = graph_functions.actors_at_distance(graph, KB, distance)
        if not actors:
            should_continue = False
            continue
        kb_numbers[distance] = len(actors)
        distance += 1

    if kb_numbers:
        print("Los actores con un KBN mayor a 6 son:")
        for i, amount in kb_numbers.items():
            print("Con KBN igual a {}: {} actores".format(i, amount))
    else:
        print("No hay actores con KBN mayor a 6")


def bacon_number_inf(graph):
    """"""
    list = []
    for vertex in graph:
        path = graph_functions.bfs(graph, vertex, KB)
        if not path:
            list.append(vertex)
    if not list:
        print("No hay actores con KBN infinito")
    else:
        print("Los actores con un Bacon Number infinito son", len(list))


def average_kbn(graph):
    """"""
    count = 0
    actors = 0
    for i, actor in enumerate(graph.get_vertexes()):
        number = obtain_bacon_number(graph, actor)
        if number != -1:
            count += number
            actors += 1
    print("El KBN promedio es {:.2f}".format(count / actors))


def actors_like(graph, max):
    """"""
    similar = graph_functions.similar(graph, KB, int(max))
    print("Los {} actores más similares KB son{}".format(max, similar))


def popularity_vs(graph, actor):
    """"""
    pop_actor = graph_functions.popularity(graph, actor)
    if pop_actor < 0:
        print("No hay datos de '{}'".format(actor))
        return
    pop_kb = graph_functions.popularity(graph, KB)
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
