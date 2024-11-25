#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<limits>
using namespace std;
struct adj_list_node {
    char vertex;
    int index;             
    float weight;      
    adj_list_node* next;        
    adj_list_node() 
    {
        next = nullptr;
        index = 0;
        weight = 0.0;
    }
    adj_list_node(int index, float weight) 
    {
        this->index = index;
        vertex = index + 65;
        this->weight = weight;
        next = nullptr;
    }
};
class adj_list {
    adj_list_node* head;  
public:
    adj_list() {
        head = nullptr;
    }
    adj_list_node* getHead() {
        return head;
    }
    adj_list_node* get_min(char end)
    {
        
        adj_list_node* temp = head;
        adj_list_node* min = head;
        while (temp != nullptr)
        {
            if (temp->weight < min->weight)
                min = temp;
            temp = temp->next;
        }
        return min;
    }
    void insert(int index, float weight) {
        if (head == nullptr) {
            head = new adj_list_node(index, weight);
        }
        else {
            adj_list_node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new adj_list_node(index, weight);
        }
    }
};



struct dist_list_node
{
    int distance;
    char vertex;
    dist_list_node* next;
    dist_list_node(const int dist = 0 , const char vertex = '\0')
    {
        distance = dist;
        this->vertex = vertex;
        next = nullptr;
    }
};


class dist_list
{
    dist_list_node* head;
public:
    dist_list()
    {
        head = nullptr;
    }
    dist_list_node* get_head()
    {
        return head;
    }
    dist_list(const int size , char start)
    {
       
        head = new dist_list_node(numeric_limits<int>::max() , start);
        dist_list_node* temp = head;
        for (int i = 0; i < size-1; i++)
        {
            
            start += 1;
            temp->next = new dist_list_node(numeric_limits<int>::max() , start);
            temp = temp->next;
        }
    }
    void insert(const int distance = numeric_limits<int>::max(), const char vertex ='\0')
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
    void print(const char start)
    {
        dist_list_node* temp = head;
        cout << start;
        while (temp->next!= nullptr)
        {
            cout << "->" << temp->vertex;
            temp = temp->next;
        }
        cout << "->"<<temp->vertex << "   " << temp->distance << endl;
    }
    void print_dist(string path , char start , char end)
    {
        dist_list_node* temp = head;
        int index = 0;
        int index2 = 0;
        int check = 0;
        int dist = 0;
        while (temp != nullptr)
        {
            if (temp->vertex == end)
            {
                dist = temp->distance;
                break;
            }
            temp = temp->next;
            index += 1;
        }
        cout << path << " " << dist;
    }
    void assign_weight(adj_list *&singly , char alpha)
    {
        adj_list_node* singly_node = singly->getHead();
        dist_list_node* temp = head;
        while (singly_node != nullptr)
        {
            temp = head;
            int vertex = singly_node->vertex;
            int weight = singly_node->weight;
            for (int i = 0; i < vertex - 65; i++)
            {
                temp = temp->next;
            }
            temp->distance = weight;
            temp->vertex = vertex;
            singly_node = singly_node->next;
        }
    }
};




class WeightedGraph {
    int size;             
    adj_list** adjacency_list;
    int hash(char c) {
        return c % 65;
    }
    int count_vertex() {
        fstream read;
        read.open("exp.csv");
        int count = 0;
        char max_character= NULL;
        string line;
        bool head = true;
        while (getline(read, line)) 
        {
            if (head) 
            {
                head = false;
                continue;
            }
            stringstream ss(line);
            string check;
            getline(ss, check, ',');
            if (check[0] > max_character)
            {
                max_character = check[0];
            }
            getline(ss, check, ',');
            if(check[0] >max_character)
            {
                max_character = check[0];
            }
        }
        return max_character %64;
    }
    void load_roads() {
        fstream read("exp.csv");
        string l;
        bool head = true;
        while (getline(read, l)) 
        {
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
    WeightedGraph() {
        this->size = count_vertex();
        adjacency_list = new adj_list * [size];
        for (int i = 0; i < size; i++) {
            adjacency_list[i] = new adj_list();
        }
        load_roads();
    }
    void display() {
        for (int i = 0; i < size; i++) 
        {
            char v = 'A';
            v += i;
            cout << "Vertex " << v<< ": ";
            adj_list_node* curr = adjacency_list[i]->getHead();
            while (curr != nullptr)
            {
                cout << "(" << curr->vertex << ", " << curr->weight << ") -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }


    void dijkstras(char start, char end)
    {
        string path;
        dist_list distance(size , 'A');
        distance.assign_weight(adjacency_list[start - 65 ] , start);
        //distance.print_dist();
        int min_node_weight = 0;
        char min_node_vertex = '\0';
        adj_list* adjacent_list = adjacency_list[start-65];
        int index = 0;
        path += start;
        for (int i = 0; i < size-1-(start-65); i++)
        {
            
            adj_list_node* min = adjacent_list->get_min(end);
            path += "->";
            path += min->vertex;

            adjacent_list = adjacency_list[min->index];
            min_node_weight += min->weight;
            min_node_vertex = min->vertex;
            adj_list_node* node_adj_list = adjacent_list->getHead();
            while (node_adj_list != nullptr)
            {
                char vertex = node_adj_list->vertex;
                int weight = node_adj_list->weight;
                dist_list_node* temp = distance.get_head();
                while (temp != nullptr)
                {
                    if (temp->vertex == vertex)
                    {
                        if (temp->distance > (min_node_weight+weight))
                        {
                            temp->distance = min_node_weight + weight;
                        }
                        break;
                    }
                    temp = temp->next;
                }
                node_adj_list = node_adj_list->next;
            }
        }
        distance.print_dist(path , start , end);
        
    }


    /*void dijkstras(char start, char end)
    {
        if (start == end)
            return;
        int index = start - 65;
        int weight = 0;
        char vertex = '\0';
        int pre_weight = weight;
        if (index > size)
            return;
        dist_list distance , visited;
        adj_list* singly_list = nullptr;
        for (int i = index; vertex!=end ;)
        {
            singly_list = adjacency_list[i];
            if (singly_list->getHead() == nullptr)
            {
                cout << "Node Do Not Exists\n";
                return;
            }
            adj_list_node* min = singly_list->get_min(end);
            weight = min->weight;
            vertex = min->vertex;
            weight += pre_weight;
            distance.insert(weight , vertex);
            if (min->vertex == end)
                break;
            pre_weight = weight;
            i = vertex - 65;
            visited.insert(0 , vertex);
        }
        distance.print(start);
    }*/


    /*void dijkstras(char st,char end) {
        List path;
        int start = hash(st);
        int cd = 0;
        path.insert(adjacency_list[start]->getHead()->a,
            adjacency_list[start]->getHead()->weight);
        Vertex* curr = path.getHead();
        Vertex* p;
        int d = 999999;
        while (curr != nullptr) {
            if (curr->weight < d) {
                p = curr;
                d = cd + curr->weight;
            }
            curr = curr->next;
        }
    }*/
    ~WeightedGraph() {
        for (int i = 0; i < size; i++) {
            adj_list_node* curr = adjacency_list[i]->getHead();
            while (curr != nullptr) {
                adj_list_node* temp = curr;
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
    /*int maxValue = numeric_limits<int>::max();
    std::cout << "The maximum value for int is: " << maxValue << std::endl;*/
    g.dijkstras('C', 'F');
    //dist_list d(5);
    //d.print_dist();
    return 0;
}
