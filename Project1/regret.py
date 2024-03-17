import math
import random
import numpy as np
import tsplib95


def calculate_distance(node1, node2, coordinates):
    """Calculate the Euclidean distance between two nodes"""
    x1, y1 = coordinates[node1]
    x2, y2 = coordinates[node2]
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)


def get_distance_matrix(path):
    # Load the TSP instance
    problem = tsplib95.load(path)

    # Get the coordinates of the nodes
    coordinates = problem.node_coords

    # Create a distance matrix
    num_nodes = len(coordinates)
    dist_matrix = [[0] * num_nodes for _ in range(num_nodes)]

    # Fill the distance matrix with distances between nodes
    for i in range(num_nodes):
        for j in range(num_nodes):
            dist_matrix[i][j] = calculate_distance(i + 1, j + 1, coordinates)

    return dist_matrix


def get_random_elem(dist_matrix):
    # Define the range
    my_range = range(len(dist_matrix))

    # Choose a random element from the range
    elem = random.choice(my_range)
    return elem


def get_graph_length(dist_matrix):
    return np.ceil(len(dist_matrix) / 2)


def regret_graph_build(distance_matrix, unused_vertices, start, graph_length):
    graph_path = [start, start]
    total_length = 0
    while len(graph_path) < graph_length + 1:
        regrets = []
        for vertex in unused_vertices:
            considered = sorted(((total_length - distance_matrix[graph_path[i - 1]][graph_path[i]] +
                                  distance_matrix[graph_path[i - 1]][vertex] + distance_matrix[vertex][graph_path[i]],
                                  i) for i in range(1, len(graph_path))), key=lambda x: x[0])
            if len(considered) >= 2:
                regret = considered[1][0] - considered[0][0]
            else:
                regret = -considered[0][0]
            length, best_i = considered[0]
            regrets.append((regret, vertex, best_i, length))
        temp = max(regrets, key=lambda x: x[0])
        best_vertex, best_i, total_length = temp[1], temp[2], temp[3]
        graph_path = graph_path[:best_i] + [best_vertex] + graph_path[best_i:]
        unused_vertices.remove(best_vertex)
    return graph_path, total_length, unused_vertices


def run_algorithm(dist_matrix, first_vertex, length, unvisited):
    obtained_tour, cycle_length, not_used_in_cycle = regret_graph_build(dist_matrix, unvisited, first_vertex, length)
    obtained_tour = obtained_tour[:-1]
    cycle_length = round(cycle_length)
    return obtained_tour, cycle_length, not_used_in_cycle


def run_x_times(path, x=2):
    min_iter = 0
    min_cycle = 65000
    max_iter = 0
    max_cycle = -1
    avg_cycle = 0
    distance_matrix = get_distance_matrix(path)
    for i in range(x):
        start = get_random_elem(distance_matrix)
        unvisited_vertices = set(range(len(distance_matrix))) - {start}
        graph_length = get_graph_length(distance_matrix)
        tour_1, length_1, not_used = run_algorithm(distance_matrix, start, graph_length, unvisited_vertices)
        random_element = random.choice(list(not_used))
        graph_length = len(distance_matrix) - graph_length
        not_used = not_used - {random_element}
        tour_2, length_2, not_used = run_algorithm(distance_matrix, random_element, graph_length, not_used)
        sum_lengths = length_1 + length_2
        if sum_lengths < min_cycle:
            min_iter = i
            min_cycle = sum_lengths
            min_tour_1 = tour_1
            min_tour_2 = tour_2
            min_length_1 = length_1
            min_length_2 = length_2
        if sum_lengths > max_cycle:
            max_iter = i
            max_cycle = sum_lengths
            max_tour_1 = tour_1
            max_tour_2 = tour_2
            max_length_1 = length_1
            max_length_2 = length_2
        avg_cycle += sum_lengths
    print("Najdłuższy cykl ma długość", max_cycle, "dla iteracji", max_iter)
    print("Najkrótszy cykl ma długość", min_cycle, "dla iteracji", min_iter)
    avg_cycle /= x
    print("Średni cykl długości dla wszystkich iteracji to", np.round(avg_cycle))
    print("Trasy dla najkrótszego cyklu:")
    print(min_tour_1)
    print(min_length_1)
    print(min_tour_2)
    print(min_length_2)
    print("Trasy dla najdłuższego cyklu:")
    print(max_tour_1)
    print(max_length_1)
    print(max_tour_2)
    print(max_length_2)
    return


print("kroA100")
run_x_times('C:/Users/wikto/Documents/Informatyka/semestr_1/IMO/lab1/IMO/Project1/kroA100.tsp', 100)
print("kroB100")
run_x_times('C:/Users/wikto/Documents/Informatyka/semestr_1/IMO/lab1/IMO/Project1/kroB100.tsp', 100)




