#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"vehicles.h"
#include"trafficsignal.h"
using namespace std;

struct Vertex {
    char n;
    int a;             
    float weight;      
    Vertex* next;
    vehicle_list cars;
    signal s;
    Vertex() {
        next = nullptr;
        a = 0;
        weight = 0.0;
    }
    Vertex(int a, float b) {
        this->a = a;
        n = a + 65;
        this->weight = b;
        next = nullptr;
    }
	void addCar(vehicles car) {
		cars.add_vehicle(car);
	}
};
class stack {

};
class List {
    Vertex* head;
public:
    List() {
        head = nullptr;
    }
    Vertex* getHead() {
        return head;
    }
    Vertex* getnearest() {
        if (head == nullptr) return nullptr; 

        Vertex* curr = head;
        Vertex* nearest = head;

        while (curr != nullptr) {
            if (curr->weight < nearest->weight) {
                nearest = curr;
            }
            curr = curr->next;
        }
        return new Vertex(nearest->a,nearest->weight); 
    }
    void insert(int a, float b) {
        if (head == nullptr) {
            head = new Vertex(a, b);
        }
        else {
            Vertex* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new Vertex(a, b);
        }
    }
};

class WeightedGraph {
    int n;
    List** adjacency_list;
    traffic_priority_queue signals;
    int hash(char c) {
        return c % 65;
    }
    void printPossiblePaths(int* path, int pathIndex,int w) {
        for (int i = 0; i < pathIndex; i++) {
            cout << char(path[i] + 'A') << "-> ";
        }
        cout <<":" << w << endl;
    }
    void load_vehicles() {
        fstream read("vehicles.csv");
        string l;
        bool head = true;
        while (getline(read, l)) {
            if (head) {
                head = false;
                continue;
            }
            stringstream ss(l);
            char  st, en;
            string id;
            string token;
            getline(ss, token, ',');
            id = token;
            getline(ss, token, ',');
            st = token[0];
            getline(ss, token, ',');
            en = token[0];
            int start = st - 'A';
            int end = en - 'A';
            vehicles temp(st, en, id);
            adjacency_list[start]->getHead()->addCar(temp);
        }
    }
    int mindistance(float* dist, bool* visited) {
        float min = INFINITY;
        int min_index = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                min_index = i;
            }
        }
        return min_index;
    }
    void printPath(int* prev, int vertex) {
        if (prev[vertex] == -1) {
            cout << char(vertex + 'A');
            return;
        }
        printPath(prev, prev[vertex]);
        cout << " -> " << char(vertex + 'A');
    }
    void load_signal() {
        fstream read("traffic_signals.csv");
        string l;
        bool head = true;
        while (getline(read, l)) {
            if (head) {
                head = false;
                continue;
            }
            stringstream ss(l);
            char vertex;
            float weight;
            string token;
            getline(ss, token, ',');
            vertex = token[0];

            getline(ss, token, ',');
            weight = stof(token);

            int v_idx = vertex - 'A';
            adjacency_list[v_idx]->getHead()->s.set_signal(weight);
        }
    }
    void load_roads() {
        fstream read("road_network.csv");
        string l;
        bool head = true;
        while (getline(read, l)) {
            if (head) {
                head = false;
                continue;
            }
            stringstream ss(l);
            char vertex, nei;
            float weight;
            string token;
            getline(ss, token, ',');
            vertex = token[0];

            getline(ss, token, ',');
            nei = token[0];

            getline(ss, token, ',');
            weight = stof(token);

            int v_idx = vertex - 'A';
            int n_idx = nei - 'A';

            adjacency_list[v_idx]->insert(n_idx, weight);
        }
    }
    void findAllPathsUtil(int current, int end, bool* visited, int* path, int& pathIndex,int& w) {
        visited[current] = true;
        path[pathIndex] = current;
        pathIndex++;
        if (current == end) {
            printPossiblePaths(path, pathIndex,w);
        }
        else {
            Vertex* neighbor = adjacency_list[current]->getHead();
            while (neighbor != nullptr) {
				w += neighbor->weight;
                if (!visited[neighbor->a]) {
                    findAllPathsUtil(neighbor->a, end, visited, path, pathIndex,w);
                }
                neighbor = neighbor->next;
            }
        }
        pathIndex--;
        visited[current] = false;
        w = 0;
    }
public:
    int count_vertex() {
        fstream read("road_network.csv");
        string l;
        bool head = true;
        char max = ' ';
        while (getline(read, l)) {
            if (head) {
                head = false;
                continue;
            }

            stringstream ss(l);
            char vertex, nei;
            string token;

            getline(ss, token, ',');
            vertex = token[0];
            if (vertex > max) {
                max = vertex;
            }

            getline(ss, token, ',');
            nei = token[0];
            if (nei > max) {
                max = nei;
            }

        }
        return max % 64;
    }
    void signal_adjust() {

    }
    WeightedGraph() {
        this->n = count_vertex();
        adjacency_list = new List * [n];
        for (int i = 0; i < n; i++) {
            adjacency_list[i] = new List();
            adjacency_list[i]->insert(i, 0);
        }
        load_roads();
        load_vehicles();
        load_signal();
    }
    void findAllPaths(char start, char end) {
        int startIdx = start%65;
        int endIdx = end%65;
        bool* visited = new bool[n] {false};
        int* path = new int[n];
        int pathIndex = 0;
        int w = 0;
        findAllPathsUtil(startIdx, endIdx, visited, path, pathIndex,w);
        delete[] visited;
        delete[] path;
    }
    void create_signal() {
        for (int i = 0; i < n; i++) {
            int vehicle_no = adjacency_list[i]->getHead()->cars.no_cars();
            int green = adjacency_list[i]->getHead()->s.get_signal();
            if (vehicle_no > 3) {
                adjacency_list[i]->getHead()->s.set_signal(green + 15);
                green += 15;
            }
            Traffic t(vehicle_no, green);
            signals.add_traffic(t);
        }
        signals.display_traffic();
    }

    void display() {
        cout << "Road network\n";
        for (int i = 0; i < n; i++) {
            char v = 'A';
            v += i;
			cout << "Green Time: " << adjacency_list[i]->getHead()->s.get_signal() << " seconds\n";
            cout << "Vertex " << v<< ": ";
            Vertex* curr = adjacency_list[i]->getHead();
			cout << "No of cars:" << adjacency_list[i]->getHead()->cars.no_cars() << "\n"; 
            while (curr != nullptr) {
                cout << "(" << curr->n << ", " << curr->weight << ") -> ";
                curr = curr->next;
            }
            cout << "\nCars present:\n";
            curr = adjacency_list[i]->getHead();
			curr->cars.display_vehicles();
        }
    }
    void dijkstra(char start,char end) {
        int start_index = start - 'A';
        float* dist = new float[n];
        int* prev = new int[n];
        bool* visited = new bool[n];

        // Initialize distances, predecessors, and visited
        for (int i = 0; i < n; i++) {
            dist[i] = INFINITY; // Set initial distances to infinity
            prev[i] = -1;       // No predecessor
            visited[i] = false; // Not visited
        }
        dist[start_index] = 0; // Distance to the source is zero

        for (int i = 0; i < n; i++) {
            int u = mindistance(dist, visited); // Get the vertex with the smallest distance
            if (u == -1) break; // If no vertex is reachable, exit the loop
            visited[u] = true;

            // Iterate through neighbors of `u`
            Vertex* neighbor = adjacency_list[u]->getHead()->next;
            while (neighbor != nullptr) {
                int v = neighbor->a; // Neighbor vertex
                float weight = neighbor->weight;

                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
                neighbor = neighbor->next;
            }
        }

        // Display the results
        cout << "Shortest paths from vertex " << start << " to "<<end<<":\n";
		printPath(prev, end%65);
        cout <<":" << dist[end % 65];
        delete[] dist;
        delete[] prev;
        delete[] visited;
    }
    ~WeightedGraph() {
        for (int i = 0; i < n; i++) {
            Vertex* curr = adjacency_list[i]->getHead();
            while (curr != nullptr) {
                Vertex* temp = curr;
                curr = curr->next;
                delete temp;
            }
            delete adjacency_list[i];
        }
        delete[] adjacency_list;
    }
};

int main() {
    WeightedGraph g;
    //g.display();
	g.dijkstra('F','O');/*
	g.create_signal();
    g.display();*/
    g.findAllPaths('A', 'F');
    return 0;
}
