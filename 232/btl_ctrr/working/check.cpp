#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <cstring>
#include <fstream>

using namespace std;

void tsp(int graph[][20], int num_vertices, int current, bool visited[], int visited_count, int current_distance, int& min_distance,int cc, vector<int>& path, vector<int>& best_path) {
    if (visited_count == num_vertices && graph[current][0] != 0) {
        if (current_distance + graph[current][0] < min_distance) {
            min_distance = current_distance + graph[current][0];
            best_path = path;
            best_path.push_back(0);
        }
        return;
    }

    for (int v = 0; v < num_vertices; ++v) {
        if (!visited[v] && graph[current][v] != 0) {
            visited[v] = true;
            path.push_back(v);
            if()
            tsp(graph, num_vertices, v, visited, visited_count + 1, current_distance + graph[current][v], min_distance, cc, path, best_path);
            path.pop_back();
            visited[v] = false;
        }
    }
}

string Traveling(int graph[][20], int num_vertices, char start_vertex) {
    bool visited[20] = { false };
    vector<int> path;
    vector<int> best_path;
    int min_distance = INT_MAX;
    long long cc = 9999999;
    int start = start_vertex - 'A';
    visited[start] = true;
    path.push_back(start);
    for(int i = 0; i < num_vertices; i++) {
        for(int j = 0; j < num_vertices; j++) {
            if(graph[i][j] < cc) {
                cc = graph[i][j];
            }
    }
    tsp(graph, num_vertices, start, visited, 1, 0, min_distance,cc, path, best_path);

    if (best_path.empty()) {
        return "not cycle";
    }

    string result;
    for (size_t i = 0; i < best_path.size(); ++i) {
        result += static_cast<char>('A' + best_path[i]);
        if (i < best_path.size() - 1) {
            result += " ";
        }
    }
    return result;
}