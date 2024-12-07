#pragma once
#include<string>
using namespace std;
struct vehicles {
	char st, en;
	string id;
	vehicles* next;
	string path;
	vehicles() {
		st = en = ' ';
		id = ' ';
		path = ' ';
		next = nullptr;
	}
	vehicles(char s, char e, string i) {
		this->st = s;
		this->en = e;
		this->id = i;
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
	int no_cars() {
		return no_of_vehicles;
	}
	void remove_vehicle(string id) {
		if (head == nullptr)
			return;
		vehicles* current = head;
		vehicles* previous = nullptr;

		if (current->id == id) {
			head = current->next;
			if (head == nullptr) {
				tail = nullptr;
			}
			delete current;
			no_of_vehicles--;
			return;
		}
		while (current != nullptr && current->id != id) {
			previous = current;
			current = current->next;
		}
		if (current == nullptr) return;
		previous->next = current->next;
		if (current == tail) {
			tail = previous;
		}
		delete current;
		no_of_vehicles--;
	}


	bool empty() {
		return head == nullptr;
	}
	void display_vehicles() {
		vehicles* current = head;
		if (!current) {
			cout << "\n\t\t->No Vehicle Present\n";
			return;
		}
		for (int i = 0; i < no_of_vehicles; i++) {
			cout << "\t\t->Vehicle ID: " << current->id << ",Path:" << current->path << endl;
			current = current->next;
		}
	}
};