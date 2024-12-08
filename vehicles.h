#pragma once
#include<string>
using namespace std;
struct vehicles {
	char st, en;
	string id;
	vehicles* next;
	string path;
	bool moving = true;
	vehicles() {
		st = en = ' ';
		id = "";
		path = "";
		next = nullptr;
	}
	vehicles(char s, char e, string i,string tp) {
		this->st = s;
		this->en = e;
		this->id = i;
		path = tp;
		next = nullptr;
	}
	vehicles(char s, char e, string i, string tp,bool t) {
		this->st = s;
		this->en = e;
		this->id = i;
		path = tp;
		moving = t;
		next = nullptr;
	}
	
	string& getid() {
		return id;
	}
	char getstart() {
		return st;
	}
	char getend() {
		return en;
	}
};
class vehicle_list {
	vehicles* head;
	vehicles* tail;
	int no_of_vehicles;
public:
	vehicle_list() {
		head = nullptr;
		no_of_vehicles = 0;
		/*tail = nullptr;*/
	}
	vehicles* get_head() {
		return head;
	}
	void add_vehicle(vehicles v) {
		vehicles* temp = new vehicles(v);
		if (head == nullptr) {
			head = tail = temp;
			no_of_vehicles++;
			return;
		}
		else {
			tail->next = temp;
			tail = temp;
			no_of_vehicles++;
			return;
		}
	}
	void delete_list() {
		while (head != nullptr) {
			vehicles* curr = head;
			head = head->next;     
			delete curr;        
		}
	}
	int no_cars() {
		return no_of_vehicles;
	}
	void remove_vehicle(string id) {
		if (head == nullptr) {
			return;  
		}
		if (head->id == id) {
			vehicles* temp = head;
			head = head->next;
			delete temp;
			no_of_vehicles--;
			return;
		}

		vehicles* current = head;
		while (current->next != nullptr && current->next->id != id) {
			current = current->next;
		}
		if (current->next == nullptr) {
			return;
		}
		vehicles* temp = current->next;
		current->next = temp->next;
		if (temp == tail) {
			tail = current;
		}
		no_of_vehicles--;
		delete temp;
	}



	bool empty() {
		return head == nullptr;
	}
	void display_vehicles() {
		vehicles* current = head;
		if (!current) {
			return;
		}
		while(current!=nullptr) {
			cout << "\t\t->Vehicle ID: " << current->id << ",Path:"<<current->path;
			cout << endl;
			current = current->next;
		}
	}
};
