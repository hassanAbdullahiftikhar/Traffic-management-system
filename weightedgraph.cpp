#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"emergency_vehicle.h"
#include"vehicles.h"
#include"trafficsignal.h"
#include"congestion.h"
using namespace std;

struct Vertex {
    char n;
    int a;
    float weight;
    Vertex* next;
    vehicle_list cars;
    emergency_list emergency_vehicles;
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
    void add_emergency_vehicle (const string& id, const char start, const char end, const string& priority_level)
    {
        emergency_vehicles.insert(id , start ,end , priority_level);
    }
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
        return new Vertex(nearest->a, nearest->weight);
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
    congestion_heap* h;
    int hash(char c) {
        return c % 65;
    }
    void relieve_intersection(char v) {

    }
    void printPossiblePaths(int* path, int pathIndex, int w) {
        for (int i = 0; i < pathIndex; i++) {
            cout << char(path[i] + 'A') << "-> ";
        }
        cout << ":" << w << endl;
    }

    void load_emergency_vehicles() {
        fstream read("emergency_vehicles .csv");
        string l;
        bool head = true;
        while (getline(read, l)) {
            if (head) {
                head = false;
                continue;
            }
            stringstream ss(l);
            char  st, en;
            string id , priority_level;
            string token;
            getline(ss, token, ',');
            id = token;
            if (id == "")
                break;
            getline(ss, token, ',');
            st = token[0];
            getline(ss, token, ',');
            en = token[0];
            getline(ss, priority_level, ',');
            int start = st - 'A';
            int end = en - 'A';
            string t = "";
            dijkstra(st, en, t);
            adjacency_list[start]->getHead()->add_emergency_vehicle(id , st , en , priority_level);
        }
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
            string t = "";
            dijkstra(st, en, t);
            temp.path = t;
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
    void printPath(int* prev, int vertex, string& p) {
        if (prev[vertex] == -1) {
            //cout << char(vertex + 'A');
            p += vertex + 'A';
            p += "->";
            return;
        }
        printPath(prev, prev[vertex], p);
        //cout << " -> " << char(vertex + 'A');
        p += vertex + 'A';
    	p += "->";
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
    void findAllPathsUtil(int current, int end, bool* visited, int* path, int& pathIndex, int& w) {
        visited[current] = true;
        path[pathIndex] = current;
        pathIndex++;
        if (current == end) {
            printPossiblePaths(path, pathIndex, w);
        }
        else {
            Vertex* neighbor = adjacency_list[current]->getHead();
            while (neighbor != nullptr) {
                w += neighbor->weight;
                if (!visited[neighbor->a]) {
                    findAllPathsUtil(neighbor->a, end, visited, path, pathIndex, w);
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
        h = new congestion_heap(n);
        load_roads();
        load_vehicles();
        load_emergency_vehicles();
        load_signal();
        for (int i = 0; i < n; i++) {
            road c(adjacency_list[i]->getHead()->n, adjacency_list[i]->getHead()->cars.no_cars());
            h->insert_car(c);
        }
    }
    void findAllPaths(char start, char end) {
        int startIdx = start % 65;
        int endIdx = end % 65;
        if (end < start) {
            cout << "No possible paths";
            return;
        }
        bool* visited = new bool[n] {false};
        int* path = new int[n];
        int pathIndex = 0;
        int w = 0;
        findAllPathsUtil(startIdx, endIdx, visited, path, pathIndex, w);
        delete[] visited;
        delete[] path;
    }
    void display_congestion() {
        h->display_congestion_levels();
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
            //cout << "Green Time: " << adjacency_list[i]->getHead()->s.get_signal() << " seconds\n";
            cout << "Vertex " << v << ": ";
            Vertex* curr = adjacency_list[i]->getHead();
            /*cout << "No of cars:" << adjacency_list[i]->getHead()->cars.no_cars() << "\n";
            while (curr != nullptr) {
                cout << "(" << curr->n << ", " << curr->weight << ") -> ";
                curr = curr->next;
            }
            cout << "\nCars present:\n";
            curr = adjacency_list[i]->getHead();
            curr->cars.display_vehicles();*/
            cout << "\nEmergency Cars present: \n";
            curr = adjacency_list[i]->getHead();
            curr->emergency_vehicles.print_vehicles();
            cout << '\n';
        }
        h->display_congestion_levels();
    }
    void dijkstra(char start, char end, string& t) {
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
        //cout << "Shortest paths from vertex " << start << " to "<<end<<":\n";
        printPath(prev, end % 65, t);
        if (t[t.length()-1] == '>')
        {
            t[t.length() - 1] = ' ';
            t[t.length() - 2] = ' ';
        }
        //cout <<":" << dist[end % 65];
        delete[] dist;
        delete[] prev;
        delete[] visited;
    }
    List ** get_adjanancy_list()
    {
        return adjacency_list;
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
class simulation_dashboard {
    WeightedGraph* g;
public:
    simulation_dashboard() {
        g = new WeightedGraph();
    }
    void menu() {
        while (true) {
            cout << "\nCity traffic Network Simulation\n";
            cout << "1.Display road network\n";
            cout << "2.Display All possible paths\n";
            cout << "3.Display Traffic signals\n";
            cout << "4.Display Congestion Levels\n";
            cout << "5.Emergency Vehicle\n";
            cout << "6.Exit simulation\n";

            int a;
            cout << "\nEnter choice: ";
            cin >> a;
            if (a == 1) {
                g->display();

            }
            else if (a == 2) {
                char st, en;
                cout << "Enter start and end vertexes";
                cin >> st;
                cin >> en;
                g->findAllPaths(st, en);
            }
            else if (a == 3) {

            }
            else if (a == 4) {
                g->display_congestion();
            }
            else if (a==5)
            {
                emergency_list emer_vehicles;
                emer_vehicles.load_emergency_vehicles();
                while (!(emer_vehicles.is_empty()))
                {
                    emergency_node* temp = emer_vehicles.get_head();
                    Vertex* vertex = g->get_adjanancy_list()[temp->start - 65]->getHead();
                    emergency_node* veh = vertex->emergency_vehicles.find_vehicle(temp->id);
                    if (veh!=nullptr)
                    {
                        string path;
                        cout << "Vehicle " << veh->id << " moving from " << veh->start << " to " << veh->end << ": ";
                        g->dijkstra(veh->start, veh->end, path);
                        cout << path << endl;;
                        Vertex* vertex2 = g->get_adjanancy_list()[temp->end - 65]->getHead();
                        vertex2->add_emergency_vehicle(veh->id , veh->start , veh->end , veh->priority_level);
                    }
                    emer_vehicles.delete_head();

                }
            }
            else {
                break;
            }
        }
    }
};
int main() {
    /* WeightedGraph g;*/
     //g.create_signal();
  //   g.display();*/
  //   g.findAllPaths('A', 'F');
    simulation_dashboard s;
    s.menu();
    return 0;
}
