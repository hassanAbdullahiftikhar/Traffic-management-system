#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"Header.h"
using namespace std;
struct Vertex {
    char n;
    int a;             
    float weight;      
    Vertex* next;
    vehicle_list* cars;

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

    int hash(char c) {
        return c % 65;
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
    WeightedGraph() {
        this->n = count_vertex();
        adjacency_list = new List * [n];
        for (int i = 0; i < n; i++) {
            adjacency_list[i] = new List();
            adjacency_list[i]->insert(i, 0);
        }
        load_roads();
    }
    void display() {
        cout << "Road network\n";
        for (int i = 0; i < n; i++) {
            char v = 'A';
            v += i;
            cout << "Vertex " << v<< ": ";
            Vertex* curr = adjacency_list[i]->getHead();
            while (curr != nullptr) {
                cout << "(" << curr->n << ", " << curr->weight << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
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

int main() {
    WeightedGraph g;
    g.display();
    return 0;
}
