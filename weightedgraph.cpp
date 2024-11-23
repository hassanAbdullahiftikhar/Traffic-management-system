#include <iostream>
using namespace std;
struct Vertex {
    int a;             
    float weight;      
    Vertex* next;        
    Vertex() {
        next = nullptr;
        a = 0;
        weight = 0.0;
    }
    Vertex(int a, float b) {
        this->a = a;
        this->weight = b;
        next = nullptr;
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
public:
    WeightedGraph(int n) {
        this->n = n;
        adjacency_list = new List * [n];
        cout << "Enter vertices and their neighbors (enter -1 to stop):\n";
        for (int i = 0; i < n; i++) {
            adjacency_list[i] = new List();
            cout << "Vertex " << i << ":\n";
            while (true) {
                int neighbor;
                float weight;
                cin >> neighbor;
                if (neighbor == -1) break;
                cin >> weight;
                adjacency_list[i]->insert(neighbor, weight);
            }
        }
    }
    void display() {
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i << ": ";
            Vertex* curr = adjacency_list[i]->getHead();
            while (curr != nullptr) {
                cout << "(" << curr->a << ", " << curr->weight << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }
    /*List dijkstras(int s,int d) {
        List minpath;
        Vertex* src = adjacency_list[s]->;
    }*/
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
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    WeightedGraph graph(vertices);
    cout << "\nGraph representation:\n";
    graph.display();
    return 0;
}
