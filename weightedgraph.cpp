
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"vehicles.h"
#include"trafficsignal.h"
#include"emergency_vehicle.h"
#include"congestion.h"
using namespace std;

struct dist_list_node
{
    int distance;
    int ver_index;
    dist_list_node* next;
    dist_list_node(const int dist = 0, const int vertex = 0)
    {
        distance = dist;
        this->ver_index = vertex;
        next = nullptr;
    }
};


class dist_list
{

public:
    dist_list_node* head;
    dist_list()
    {
        head = nullptr;
    }
    dist_list_node* get_head()
    {
        return head;
    }
    dist_list(const int size, int start)
    {

        head = new dist_list_node(numeric_limits<int>::max(), 0);
        dist_list_node* temp = head;
        for (int i = 0; i < size - 1; i++)
        {

            start += 1;
            temp->next = new dist_list_node(numeric_limits<int>::max(), start);
            temp = temp->next;
        }
    }
    dist_list_node* get_min()
    {
        dist_list_node* temp = head;
        dist_list_node* min = head;
        while (temp != nullptr)
        {
            if (temp->distance < min->distance)
            {
                min = temp;
            }
            temp = temp->next;
        }
        return min;
    }
    void delete_node(const int index)
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->ver_index == index)
        {
            dist_list_node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        else
        {
            dist_list_node* temp = head, * temp2 = head;
            while (temp != nullptr && temp->ver_index != index)
            {
                temp2 = temp;
                temp = temp->next;
            }
            if (temp == nullptr)
                return;
            temp2->next = temp->next;
            delete temp;
        }
    }
    void insert(const int distance = numeric_limits<int>::max(), const char vertex = '\0')
    {
        if (head == nullptr)
        {
            head = new dist_list_node(distance, vertex);
            return;
        }
        else
        {
            dist_list_node* traverse = head;
            while (traverse->next != nullptr)
            {
                traverse = traverse->next;
            }
            traverse->next = new dist_list_node(distance, vertex);
            return;
        }
    }
    int check_dup(const int index) const
    {
        dist_list_node* temp = head;
        if (temp == nullptr)
        {
            return 0;
        }
        else
        {
            while (temp != nullptr)
            {
                if (temp->ver_index == index) {
                    return 1;
                }
                temp = temp->next;
            }
        }
        return 0;
    }
    int is_empty() const
    {
        return head == nullptr;
    }
    void print(const char start) const
    {
        dist_list_node* temp = head;
        cout << start;
        while (temp->next != nullptr)
        {
            cout << "->" << temp->ver_index + 65;
            temp = temp->next;
        }
        cout << "->" << temp->ver_index + 65 << "   " << temp->distance << endl;
    }
};


class blocked_edge_node {
    char name;
    string status;
    blocked_edge_node* next;

public:
    blocked_edge_node(char name, string status) {
        this->name = name;
        this->status = status;
        next = nullptr;
    }

    char get_name() const {
        return name;
    }

    string get_status() const {
        return status;
    }

    void set_name(char name) {
        this->name = name;
    }

    void set_status(const string& status) {
        this->status = status;
    }

    friend class blocked_edge;
};

class blocked_edge {
    blocked_edge_node* head;
    blocked_edge_node* tail;

public:
    blocked_edge() {
        head = tail = nullptr;
    }

    void insert_at_end(const char name, const string& status) {

        if (find(name)) {
            cout << name << " is already blocked" << endl;
            return;
        }
        blocked_edge_node* new_blocked_edge = new blocked_edge_node(name, status);

        if (head == nullptr) {
            head = new_blocked_edge;
            tail = new_blocked_edge;
        }
        else {
            tail->next = new_blocked_edge;
            tail = new_blocked_edge;
        }
    }



    void delete_by_value(char name) {
        if (head == nullptr) {
            return;
        }

        if (head->get_name() == name) {
            blocked_edge_node* temp = head;
            head = head->next;
            delete temp;

            if (head == nullptr) {
                tail = nullptr;
            }
            return;
        }
        blocked_edge_node* p = head;
        while (p->next && p->next->get_name() != name)
        {
            p = p->next;
        }
        if (p->next == nullptr)
        {
            return;
        }
        else
        {
            blocked_edge_node* temp = p->next;
            p->next = p->next->next;
            delete temp;
            return;
        }

    }
    bool find(const char n) const
    {
        blocked_edge_node* p = head;
        while (p != nullptr) {
            if (p->name == n) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    ~blocked_edge() {
        while (head) {
            blocked_edge_node* temp = head;
            head = head->next;
            delete temp;
        }
    }


    void print() const
    {
        blocked_edge_node* current = head;
        while (current) {
            cout << current->get_name() << " (" << current->get_status() << ") -> ";
            current = current->next;
        }

    }

    void print_all(char val) const
    {
        blocked_edge_node* current = head;
        while (current) {

            cout << "->Road from " << val << " To " << current->name << " is blocked" << endl;

            current = current->next;
        }
    }

};



struct Vertex {
    char n;
    int a;
    float weight;
    Vertex* next;
    vehicle_list cars;
    emergency_list emergency_vehicles;
    signal s;
    blocked_edge* block_roads;

    Vertex() {
        n = '\0';
        next = nullptr;
        a = 0;
        weight = 0.0;
        block_roads = new blocked_edge();
    }

    Vertex(int a, float b) {
        this->a = a;
        n = a + 65;
        this->weight = b;
        next = nullptr;
        block_roads = new blocked_edge();
    }

    void addCar(vehicles car) {
        cars.add_vehicle(car);
    }
    void add_emergency_vehicle(const string& id, const char start, const char end, const string& priority_level)
    {
        emergency_vehicles.insert(id, start, end, priority_level);
    }

    void add_block_edge(char name, string status)
    {
        block_roads->insert_at_end(name, status);
    }

};



class List {
public:
    Vertex* head;
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
    bool find(char name) {
        Vertex* p = head;
        while (p != nullptr) {
            if (p->n == name) {
                return true;
            }
            p = p->next;
        }
        return false;
    }
};

class WeightedGraph {
    int n;
public:
    List** adjacency_list;
    traffic_priority_queue signals;
    congestion_heap* h;
    int hash(char c) {
        return c % 65;
    }



    void printPossiblePaths(int* path, int pathIndex, int w) {
        for (int i = 0; i < pathIndex; i++) {
            cout << char(path[i] + 'A') << "-> ";
        }
        cout << ":" << w << endl;
    }
    void load_emergency_vehicles() {
        fstream read("ev.csv");
        string l;
        bool head = true;
        while (getline(read, l)) {
            if (head) {
                head = false;
                continue;
            }
            stringstream ss(l);
            char  st, en;
            string id, priority_level;
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
            adjacency_list[start]->getHead()->add_emergency_vehicle(id, st, en, priority_level);
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
            string t = "";
            dijkstra(st, en, t);
            if (t.length() > 1) {
                vehicles temp(st, en, id, t);
                adjacency_list[start]->getHead()->addCar(temp);
            }
            else {
                vehicles temp(st, en, id, t);
                temp.moving = false;
                adjacency_list[start]->getHead()->addCar(temp);
            }
        }
    }
    int mindistance(float* dist, bool* visited) {
        float min = 999;
        int min_index = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                min_index = i;
            }
        }
        return min_index;
    }
    static void printPath(int* prev, int vertex, string& p, int start)
    {
        if (prev[vertex] == -1)
        {
            p += vertex + 'A';
            return;
        }
        printPath(prev, prev[vertex], p, start);
        p += vertex + 'A';
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
        if (current == end)
        {
            cout << "\t";
            printPossiblePaths(path, pathIndex, w);
        }
        else {
            Vertex* neighbor = adjacency_list[current]->getHead();
            while (neighbor != nullptr) {
                w += neighbor->weight;
                if (!visited[neighbor->a]) {
                    findAllPathsUtil(neighbor->a, end, visited, path, pathIndex, w);
                }
                w -= neighbor->weight;
                neighbor = neighbor->next;
            }
        }
        pathIndex--;
        visited[current] = false;
    }
    void decrement_path(string& s) {
        string t = "";
        for (int i = 1; i < s.length(); i++) {
            t += s[i];
        }
        s = t;
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
        h = new congestion_heap();
        load_roads();
        load_signal();
        load_road_closures();
        load_vehicles();
        load_emergency_vehicles();
        for (int i = 1; i <= n; i++) {

            h->insert_car(adjacency_list[i - 1]->getHead()->n, adjacency_list[i - 1]->getHead()->cars.no_cars());
        }
    }
    void reroute_vehicles() {
        for (int i = 0; i < n; i++) {
            vehicle_list& c = adjacency_list[i]->getHead()->cars;
            vehicles* curr = c.get_head();
            while (curr != nullptr) {
                if (curr->moving == false) {
                    string t = "";
                    dijkstra(curr->st, curr->en, t);
                    if (t.length() > 1) {
                        cout << "Vehicle " << curr->id << "has been rerouted via" << t << endl;
                        curr->path = t;
                        curr->moving = true;
                    }
                }
                curr = curr->next;
            }
        }
    }
    void findAllPaths(char start, char end) {
        int startIdx = start % 65;
        int endIdx = end % 65;
        if (end < start) {
            cout << "\t\tNo possible paths\n";
            return;
        }
        bool* visited = new bool[n] {false};
        int* path = new int[n];
        int pathIndex = 0;
        int w = 0;
        cout << "\t\t\t\t\t\t --------------";
        cout << "\n\t\t\t\t\t\t|Possible Paths| \n";
        cout << "\t\t\t\t\t\t --------------\n\n";
        findAllPathsUtil(startIdx, endIdx, visited, path, pathIndex, w);
        delete[] visited;
        delete[] path;
    }
    void display_congestion() {
        h->display_congestion_levels();
    }
    void relieve_intersection() {
        char v = h->get_max_congestion().level;
        h->decrement_top();
        vehicle_list& s = adjacency_list[v - 'A']->getHead()->cars;
        vehicles* curr = s.get_head();
        vehicle_list temp;
        while (curr != nullptr) {
            if (curr->moving == false) {
                string dd = curr->path;
                vehicles c(curr->en, curr->st, curr->id, dd);
                temp.add_vehicle(c);
                s.remove_vehicle(curr->id);
            }
            else if (curr->path.length() > 2) {
                string d = curr->path;
                decrement_path(d);
                string vehicle_id = curr->id;
                s.remove_vehicle(vehicle_id);
                vehicles temp;
                temp.id = vehicle_id;
                temp.path = d;
                adjacency_list[d[0] - 'A']->getHead()->cars.add_vehicle(temp);

                h->increment_cars(d[0]);

            }
            else {
                cout << "Vehicle " << curr->id << " has reached its destination\n";
                string vehicle_id = curr->id;
                s.remove_vehicle(vehicle_id);
            }
            curr = s.get_head();
        }
        vehicles* cur = temp.get_head();
        while (cur != nullptr) {
            bool n = false;
            vehicles c(cur->st, cur->en, cur->id, cur->path, n);
            adjacency_list[v - 'A']->getHead()->addCar(c);
            h->increment_cars(adjacency_list[v - 'A']->getHead()->n);
            cur = cur->next;
        }
        adjacency_list[v - 'A']->getHead()->cars.display_vehicles();
    }

    void display_vehicles() {
        for (int i = 0; i < n; i++) {
            cout << "->Vehicles present at " << adjacency_list[i]->getHead()->n << "\n";
            adjacency_list[i]->getHead()->cars.display_vehicles();
            cout << "\n";
        }
    }
    void create_signal() {
        signals.empty();
        for (int i = 0; i < n; i++) {
            int vehicle_no = adjacency_list[i]->getHead()->cars.no_cars();
            cout << adjacency_list[i]->getHead()->n << " cars:" << vehicle_no << endl;
            int green = adjacency_list[i]->getHead()->s.get_signal();
            if (vehicle_no > 3) {
                adjacency_list[i]->getHead()->s.set_signal(green + 15);
                green += 15;
            }
            Traffic t(vehicle_no, green, adjacency_list[i]->getHead()->n);
            signals.add_traffic(t);
        }
        signals.display_traffic();
    }

    void display() const
    {
        cout << "\t\t\t\t\t\t ------------\n";
        cout << "\t\t\t\t\t\t|Road network|\n";
        cout << "\t\t\t\t\t\t ------------\n\n";
        for (int i = 0; i < n; i++) {
            char v = 'A';
            v += i;
            //cout << "Green Time: " << adjacency_list[i]->getHead()->s.get_signal() << " seconds\n";
            cout << "Vertex " << v << ": ";
            Vertex* curr = adjacency_list[i]->getHead();
            cout << "\n\t->No of cars:" << adjacency_list[i]->getHead()->cars.no_cars() << "\n\t";
            cout << "->Connected Roads: ";
            while (curr != nullptr) {
                cout << "(" << curr->n << ", " << curr->weight << ")";
                if (curr->next != nullptr)
                {
                    cout << "->";
                }
                curr = curr->next;
            }

            cout << endl;
            cout << "\t->Cars present: \n";
            curr = adjacency_list[i]->getHead();
            curr->cars.display_vehicles();
            cout << "\t->Emergency Cars present: \n";
            curr = adjacency_list[i]->getHead();
            curr->emergency_vehicles.print_vehicles();
            cout << '\n';
        }
    }

    int dijkstra(const char start, const char end, string& temp)
    {
        dist_list distance(n, 0);
        float* dist = new float[n];
        dist_list queue;
        int predecessor[26];

        for (int i = 0; i < n; i++)
        {
            predecessor[i] = -1;
        }
        queue.insert(0, start - 65);
        dist_list_node* min = queue.get_min();
        int min_distance = min->distance;
        int min_vertex_index = min->ver_index;
        List* adjacent_list = adjacency_list[min_vertex_index];
        Vertex* adj_node = nullptr;
        int i = 0;
        while (!(queue.is_empty()))
        {
            adj_node = adjacent_list->getHead();

            while (adj_node != nullptr)
            {
                dist_list_node* temp = distance.get_head();
                while (temp != nullptr)
                {
                    if (temp->ver_index == adj_node->a)
                    {
                        if (!(adjacent_list->getHead()->block_roads->find(adj_node->n)) && (temp->distance > (min_distance + adj_node->weight)))
                        {
                            temp->distance = min_distance + adj_node->weight;
                            predecessor[temp->ver_index] = min_vertex_index;
                            if (queue.check_dup(temp->ver_index))
                            {
                                queue.delete_node(temp->ver_index);
                            }
                            queue.insert(temp->distance, temp->ver_index);
                        }
                        break;
                    }
                    temp = temp->next;
                }

                adj_node = adj_node->next;
            }
            queue.delete_node(min->ver_index);
            min = nullptr;
            if (!(queue.is_empty()))
            {
                min = queue.get_min();
                min_distance = min->distance;
                min_vertex_index = min->ver_index;
                adjacent_list = adjacency_list[min->ver_index];
            }
        }
        predecessor[start - 65] = -1;
        printPath(predecessor, end % 65, temp, start - 65);
        if (temp[temp.length() - 1] == '>')
        {
            temp[temp.length() - 1] = ' ';
            temp[temp.length() - 2] = ' ';
        }
        dist_list_node* temp2 = distance.get_head();
        while (temp2 != nullptr)
        {
            if (temp2->ver_index == end - 65)
            {
                return temp2->distance;
            }
            temp2 = temp2->next;
        }
    }

    void load_road_closures() {
        fstream read("road_closures.csv");
        string line;
        bool head = true;

        while (getline(read, line)) {
            if (head) {
                head = false;
                continue;
            }

            stringstream ss(line);
            string start, end, status;
            char st, en;


            getline(ss, start, ',');
            getline(ss, end, ',');
            getline(ss, status, ',');


            st = start[0];
            en = end[0];


            if (status == "Blocked" || status == "Under Repair") {

                int st_index = st - 'A';
                int en_index = en - 'A';

                Vertex* start_vertex = adjacency_list[st_index]->getHead();
                Vertex* end_vertex = adjacency_list[en_index]->getHead();

                if (adjacency_list[st_index]->find(en))
                    start_vertex->block_roads->insert_at_end(en, status);
            }
        }
    }

    void show_blocked_roads()
    {
        cout << "\t\t\t\t\t --------------------------\n";
        cout << "\t\t\t\t\t|Blocked/Under Repair Roads|\n";
        cout << "\t\t\t\t\t --------------------------\n\n";
        for (int i = 0; i < n; i++)
        {

            adjacency_list[i]->getHead()->block_roads->print_all(adjacency_list[i]->getHead()->n);
        }
    }

    void block_certain_road() {
        char start, end;

        do {
            cout << "Enter the road to block\n" << "Start: ";
            cin >> start;
            cout << "End: ";
            cin >> end;


            if (!((start >= 'A' && start <= 'Z') || (start >= 'a' && start <= 'z')) ||
                !((end >= 'A' && end <= 'Z') || (end >= 'a' && end <= 'z'))) {
                cout << "Please type correct destination\n";
            }
            else {

                if (start >= 'a' && start <= 'z') {
                    start = start - 32;
                }
                if (end >= 'a' && end <= 'z') {
                    end = end - 32;
                }
                break;
            }
        } while (true);

        Vertex* start_vertex = adjacency_list[start - 'A']->getHead();

        Vertex* road = adjacency_list[start - 'A']->getHead();
        bool is_adjacent = false;
        while (road != nullptr) {
            if (road->n == end) {
                is_adjacent = true;
                break;
            }
            road = road->next;
        }

        if (is_adjacent) {
            start_vertex->block_roads->insert_at_end(end, "Blocked");
            cout << "\t\t\t\t\tRoad Blocked Successfully!!\n";
        }
        else {
            cout << "->Roads are not adjacent and cant be blocked\n";
        }
    }
    void clear_certain_road()
    {
        char start, end;
        bool is_blocked = true;
        do {
            cout << "Enter the road to clear\n" << "Start: ";
            cin >> start;
            cout << "End: ";
            cin >> end;


            if (!((start >= 'A' && start <= 'Z') || (start >= 'a' && start <= 'z')) ||
                !((end >= 'A' && end <= 'Z') || (end >= 'a' && end <= 'z'))) {
                cout << "Please type correct destination \n";
            }
            else {

                if (start >= 'a' && start <= 'z') {
                    start = start - 32;
                }
                if (end >= 'a' && end <= 'z') {
                    end = end - 32;
                }
                break;
            }
        } while (true);

        Vertex* start_vertex = adjacency_list[start - 'A']->getHead();

        Vertex* road = adjacency_list[start - 'A']->getHead();
        bool is_adjacent = false;
        while (road != nullptr) {
            if (road->n == end) {
                is_adjacent = true;
                break;
            }
            road = road->next;
        }

        if (is_adjacent) {
            if (start_vertex->block_roads->find(end))
            {
                start_vertex->block_roads->delete_by_value(end);
                cout << "->Road has been cleared\n";
                cout << "Routing vehicles started";
                reroute_vehicles();
                is_blocked = false;
            }
            else
            {
                cout << "\n->Road wasn't blocked in the first place\n";
            }


        }
    }

    List** get_adjacancy_list() const
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
    void menu() const
    {
        emergency_list emer_vehicles;
        emer_vehicles.load_emergency_vehicles();
        while (true)
        {
            cout << "------------------------------------------------------------------------------------------------------------------------\n";
            cout << "\n\t\t\t\t\tCity traffic Network Simulation\n";
            cout << "Options:\n";
            cout << "\t1-Display road network\n";
            cout << "\t2-Display All possible Permutations of paths\n";
            cout << "\t3-Display Traffic signals\n";
            cout << "\t4-Display Congestion Levels\n";
            cout << "\t5-Display Vehicles along with the paths\n";
            cout << "\t6-Display Blocked Roads\n";
            cout << "\t7-Enforce a blockade\n";
            cout << "\t8-Clear a blockade\n";
            cout << "\t9-Move emergency vehicle\n";
            cout << "\t10-Add a vehicle\n";
            cout << "\t11-Exit simulation\n";

            int a;
            cout << "\n\tEnter choice:";
            cin >> a;
            if (a == 1) {
                g->display();

            }
            else if (a == 2) {
                char st, en;
                cout << "Enter Start: ";
                cin >> st;
                cout << "Enter End: ";
                cin >> en;
                g->findAllPaths(st, en);
            }
            else if (a == 3) {
                g->create_signal();
            }
            else if (a == 4) {
                g->display_congestion();
                int i = -1;
                cout << "\nResolve most congested road?(0=no/1=yes)\nEnter Choice: ";
                cin >> i;
                if (i == 1) {
                    g->relieve_intersection();
                }
            }
            else if (a == 5) {
                g->display_vehicles();
            }
            else if (a == 6) {

                g->show_blocked_roads();
            }
            else if (a == 7) {
                g->block_certain_road();
            }
            else if (a == 8) {
                g->clear_certain_road();
            }
            else if (a == 9)
            {
                cout << "\t\t\t\t\t\t ------------------\n";
                cout << "\t\t\t\t\t\t|Emergency Vehicles|\n";
                cout << "\t\t\t\t\t\t ------------------\n\n";
                if (!(emer_vehicles.is_empty()))
                {
                    emergency_node* temp = emer_vehicles.get_head();
                    Vertex* vertex = g->get_adjacancy_list()[temp->start - 65]->getHead();
                    emergency_node* veh = vertex->emergency_vehicles.find_vehicle(temp->id);

                    if (veh != nullptr)
                    {
                        string path;
                        cout << "->Vehicle " << veh->id << " moving from ";
                        g->dijkstra(veh->start, veh->end, path);
                        cout << path << endl;
                        Vertex* vertex2 = g->get_adjacancy_list()[temp->end - 65]->getHead();
                        vertex2->add_emergency_vehicle(veh->id, veh->start, veh->end, veh->priority_level);
                        emer_vehicles.delete_head();
                    }
                }
                else
                {
                    cout << "\n\tAll Emergency Vehicles Have Reached Their Destination.\n";
                }
            }
            else if (a == 10)
            {
                string temp;
                char start, end;
                bool r = true;
                cout << "Enter Start and end vertexs";
                cin >> start;
                cin >> end;
                string id;
                cout << "Enter name:";
                cin >> id;
                g->dijkstra(start, end, temp);
                if (temp.length() <= 1) {
                    r = false;
                }
                vehicles s(start, end, id, temp, r);
                g->adjacency_list[start - 'A']->getHead()->addCar(s);
            }
            else {
                break;
            }

        }
    }
};
int main() {
    simulation_dashboard s;
    s.menu();
    return 0;
}
