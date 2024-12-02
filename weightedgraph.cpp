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
    adj_list()
	{
        head = nullptr;
    }
    adj_list(char alpha, int weight)
    {
        head = new adj_list_node(alpha, weight);
    }
    adj_list_node* getHead() {
        return head;
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
    int ver_index;
    dist_list_node* next;
    dist_list_node(const int dist = 0 , const int vertex = 0)
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
    dist_list(const int size , int start)
    {
       
        head = new dist_list_node(numeric_limits<int>::max() , 0);
        dist_list_node* temp = head;
        for (int i = 0; i < size-1; i++)
        {
            
            start += 1;
            temp->next = new dist_list_node(numeric_limits<int>::max() , start);
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
    void delete_node(int index)
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
            while (temp!=nullptr && temp->ver_index != index)
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
    int check_dup(int index)
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
    }
     int is_empty()
    {
        return head == nullptr;
    }
    void print(const char start)
    {
        dist_list_node* temp = head;
        cout << start;
        while (temp->next!= nullptr)
        {
            cout << "->" << temp->ver_index+65;
            temp = temp->next;
        }
        cout << "->"<<temp->ver_index+65 << "   " << temp->distance << endl;
    }
    void print_dist(string path="", char start='\0' , char end = '\0')
    {
        dist_list_node* temp = head;
        while (temp != nullptr)
        {

            char ch = temp->ver_index + 'A';
                cout << ch << "->" << temp->distance << endl;
            temp = temp->next;
        }
        /*int index = 0;
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
        }if(dist!= numeric_limits<int>::max())
            cout << path << " " << dist;*/
    }
};




class WeightedGraph 
{
    int size;             
    adj_list** adjacency_list;
public:

    int hash(char c)
    {
        return c % 65;
    }
    int count_vertex()
    {
        fstream read;
        read.open("road_network.csv");
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
        fstream read("road_network.csv");
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
            adjacency_list[i] = new adj_list(i , 0);
        }
        load_roads();
    }
    void display() const {
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
    static int check_node(char start , char end , const dist_list_node *temp)
    {
        int s_check = 0, e_check = 0;
        start -= 65;
        end -= 65;
        while (temp != nullptr)
        {
            if (temp->ver_index == start)
            {
                s_check = 1;
            }
            else if (temp->ver_index == end)
            {
                e_check = 1;
            }
            temp = temp->next;
        }
        if (s_check && e_check)
            return 1;
        else
            return 0;
    } 

    int dijkstras(const char start, const char end)
    {
        dist_list distance(size, 0);   
        dist_list queue;
        int predecessor[26];  

        for (int i = 0; i < size; i++) 
        {
            predecessor[i] = -1;
        }

        queue.insert(0, start - 65);
        dist_list_node* min = queue.get_min();
        int min_distance = min->distance;
        int min_vertex_index = min->ver_index;
        adj_list* adjacent_list = adjacency_list[min_vertex_index];
        adj_list_node* adj_node = nullptr;
        while (!(queue.is_empty()))
        {
            adj_node = adjacent_list->getHead();

            while (adj_node != nullptr)
            {
                dist_list_node* temp = distance.get_head();
                while (temp != nullptr)
                {
                    if (temp->ver_index == adj_node->index)
                    {
                        if (temp->distance > (min_distance + adj_node->weight))
                        {
                            temp->distance = min_distance + adj_node->weight;
                            predecessor[temp->ver_index] = min->ver_index;  
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
                adjacent_list = adjacency_list[min->ver_index];
            }
        }
        //for (int i = 0; i < size; i++)
        //{
        //    cout << predecessor[i] << " ";
        //}
        //cout << endl;
       // distance.print_dist("", start, end);

        char path[26];
        int path_index = 0;
        int shortest_dist = 0;
        int current = end - 65; 
        if (current >= 0 && current < size)
        {
            while (current >=0 && current < size )
            {
                path[path_index] = current + 65;
            	if (path[path_index-1]==start)
                    break;
                current = predecessor[current];
                path_index++;
            }
            cout << "Shortest Path: ";
            for (int i = path_index - 1; i >= 0; i--)
            {
                cout << path[i];
                if (i != 0) cout << " -> ";
            }
            dist_list_node* temp2 = distance.get_head();
            while (temp2 != nullptr)
            {
                if (temp2->ver_index == end - 65)
                {
                    cout << ": " << temp2->distance << endl;
                    shortest_dist = temp2->distance;
                    break;
                }
                temp2 = temp2->next;
            }
        }
        else
        {
            cout << "End node (" << end << ") is out of valid range." << endl;
        }
        return shortest_dist;
    }

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
    int get_size() const 
    {
        return size;
    }
};

int main() 
{
    WeightedGraph g;
    int size = g.get_size();
    dist_list  distance(size , 'A');
    g.dijkstras('F', 'O');
    //distance.print_dist("  " , 'A', 'H');
    //g.display();
    return 0;
}
