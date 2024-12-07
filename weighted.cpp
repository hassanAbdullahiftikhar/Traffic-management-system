#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"vehicles.h"
#include"trafficsignal.h"
#include"congestion.h"
using namespace std;


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

    void insert_at_end(char name, string status) {
    
    if (find(name)) {
        cout << name << " is already blocked"<<endl;
        return; 
    }
    blocked_edge_node* new_blocked_edge = new blocked_edge_node(name, status);

    if (head == nullptr) {
        head = new_blocked_edge;
        tail = new_blocked_edge;
    } else {
        tail->next = new_blocked_edge;
        tail = new_blocked_edge;
    }
}


    
    void delete_by_value(char name) {
        if (head!=nullptr) 
        {
        return;  
        }
        if (head->get_name() == name) {
            blocked_edge_node* temp = head;
            head = head->next;
            delete temp;

            
            if (!head) {
                tail = nullptr;
            }
            return;
        }

    
        blocked_edge_node* p = head;
        while (p->next && p->next->get_name() != name) {
            p = p->next;
        }

        if (p->next) {
            blocked_edge_node* temp = p->next;
            p->next = p->next->next;
            if (p->next == nullptr) {
                tail = p;
            }

            delete temp;
        }
    }
     bool find(char n) {
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

   
    void print() {
        blocked_edge_node* current = head;
        while (current) {
            cout << current->get_name() << " (" << current->get_status() << ") -> ";
            current = current->next;
        }
      
    }

void print_all(char val) {
    blocked_edge_node* current = head;
    while (current) {
      
        cout << val << " To " << current->name << " is blocked" << endl;
       
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
    signal s;
    blocked_edge* block_roads ;
    
Vertex() {
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
   
   void add_block_edge(char name ,string status)
   {
        block_roads->insert_at_end(name,status) ;
   }
   
};



class List {
    public:
    Vertex* head ;
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
    congestion_heap *h;
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
            string t="";
            dijkstra(st, en,t);
            temp.path = t;
            adjacency_list[start]->getHead()->addCar(temp);
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
    void printPath(int* prev, int vertex,string &p) {
        if (prev[vertex] == -1) {
            //cout << char(vertex + 'A');
			p+=vertex + 'A';
            return;
        }
        printPath(prev, prev[vertex],p);
        //cout << " -> " << char(vertex + 'A');
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
				w -= neighbor->weight;
                neighbor = neighbor->next;
            }
        }
        pathIndex--;
        visited[current] = false;
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
        load_vehicles();
        load_signal();
        load_road_closures();
        for (int i = 1; i <=n; i++) {

            h->insert_car(adjacency_list[i - 1]->getHead()->n, adjacency_list[i-1]->getHead()->cars.no_cars());
        }
    }
    void findAllPaths(char start, char end) {
        int startIdx = start%65;
        int endIdx = end%65;
        if (end < start) {
            cout << "No possible paths";
            return;
        }
        bool* visited = new bool[n] {false};
        int* path = new int[n];
        int pathIndex = 0;
        int w = 0;
        findAllPathsUtil(startIdx, endIdx, visited, path, pathIndex,w);
        delete[] visited;
        delete[] path;
    }
    void display_congestion() {
        h->display_congestion_levels();
    }
    void relieve_intersection() {
        char v = h->get_max_congestion().level;
        Vertex* current_vertex = adjacency_list[hash(v)]->getHead();
        vehicle_list& car_list = current_vertex->cars;
        h->decrement_top();
        while (car_list.get_head() != nullptr) {
            vehicles temp = *car_list.get_head();
            if (temp.path.length()>1) {
                car_list.remove_vehicle(temp.id);
                temp.path.erase(0, 1);
                char new_index = temp.path[0];
                if (temp.path.length()!=0) {
                    if (temp.en != new_index) {
                        adjacency_list[hash(new_index)]->getHead()->cars.add_vehicle(temp);
                    }
                    h->increment_cars(adjacency_list[hash(new_index)]->getHead()->n);
                }
            }
            else {
                break;
            }
        }
    }
    void display_vehicles() {
        for (int i = 0; i < n; i++) {
            cout << "Vehicles present at " << adjacency_list[i]->getHead()->n << "\n";
			adjacency_list[i]->getHead()->cars.display_vehicles();
            cout << "\n";
        }
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
            cout << "Vertex " << v<< ": ";
            Vertex* curr = adjacency_list[i]->getHead();
			cout << "No of cars:" << adjacency_list[i]->getHead()->cars.no_cars() << "\n"; 
            while (curr != nullptr) {
                cout << "(" << curr->n << ", " << curr->weight << ") -> ";
                curr = curr->next;
            }
            cout << "\nCars present:\n";
            curr = adjacency_list[i]->getHead();
        }
    }
  
      void dijkstra(char start, char end, string &t) {
    int start_index = start - 'A';
    int end_index = end - 'A';
    float* dist = new float[n];
    int* prev = new int[n];
    bool* visited = new bool[n];


    for (int i = 0; i < n; i++) {
        dist[i] = 999; 
        prev[i] = -1;       
        visited[i] = false;
    }
    dist[start_index] = 0; 

    for (int i = 0; i < n; i++) {
        int u = mindistance(dist, visited); // Get the vertex with the smallest distance
        if (u == -1) break; // If no vertex is reachable, exit the loop
        visited[u] = true;

        // Iterate through neighbors of u
        Vertex* neighbor = adjacency_list[u]->getHead();
        while (neighbor != nullptr) {
            int v = neighbor->a; // Neighbor vertex
            float weight = neighbor->weight;

         
            bool road_blocked = adjacency_list[u]->getHead()->block_roads->find(neighbor->n);

            if (!visited[v] && !road_blocked && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            neighbor = neighbor->next;
        }
    }

    // Build the new path
    printPath(prev, end_index, t);

    delete[] dist;
    delete[] prev;
    delete[] visited;
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
            start_vertex->block_roads->insert_at_end(en,status);
          
           // cout<<"intersecton1:"<<st <<" intersection2:"<<en <<" status:"<<status;
            //cout<<endl;
        }
    }
}

void show_blocked_roads()
{
     cout << "------blocked/under repair roads-------------\n";
    for (int i =0 ; i<n ; i++)
    {
         
        adjacency_list[i]->getHead()->block_roads->print_all(adjacency_list[i]->getHead()->n) ;
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

    Vertex* start_vertex = adjacency_list[start-'A']->getHead();

    Vertex* road = adjacency_list[start-'A']->getHead();
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
       
    } else {
       cout<<"roads are not adjacent and cant be blocked\n";
    }
}
void clear_certain_road()
{
     char start, end;
     bool is_blocked =true;
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

    Vertex* start_vertex = adjacency_list[start-'A']->getHead();

    Vertex* road = adjacency_list[start-'A']->getHead();
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
        cout<<"road has been cleared\n";
        is_blocked = false;
        }
        else 
        {
            cout<<"road wasnt blocked in the first place\n";
        }
       
     
    }
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
	simulation_dashboard(){
		g = new WeightedGraph();
    }
    void menu() {
        while (true) {
            cout << "City traffic Network Simulation\n";
            cout << "1.Display road network\n";
            cout << "2.Display All possible paths\n";
            cout << "3.Display Traffic signals\n";
            cout << "4.Display Congestion Levels\n";
            cout << "5.Display Vehicles along with the paths\n";
            cout << "6.Display Signal statuses\n";
            cout << "7.Enforce a blockade\n";
            cout << "8.Clear a blockade\n";
         
            cout << "9.Exit simulation\n";

            int a;
            cout << "enter choice:";
            cin>>a;
            if (a == 1) {
                g->display();
               
            }
			else if (a == 2) {
				char st,en;
                cout << "Enter start and end vertexes";
                cin >> st;
                cin >> en;
				g->findAllPaths(st, en);
            }
            else if (a == 3) {
                g->create_signal();
            }
            else if (a == 4) {
                g->display_congestion();
                int i = -1;
                cout << "Resolve most congested road?(0=no/1=yes)";
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
            else{
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
