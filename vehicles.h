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
	vehicles(char s, char e, string i){
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
	int no_of_vehicles;
public:
	vehicle_list() {
		head = nullptr;
		no_of_vehicles = 0;
	}
	void add_vehicle(vehicles v) {
		vehicles* temp = new vehicles(v);
		if (head == nullptr) {
			head = temp;
			no_of_vehicles++;
			return;
		}
		else {
			vehicles* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = temp;
			no_of_vehicles++;
			return;
		}
	}
	int no_cars() {
		return no_of_vehicles;
	}
	void remove_vehicle(string id) {
		if (head == nullptr) return;
		vehicles* current = head;
		vehicles* previous = nullptr;
		if (current != nullptr && current->id == id) {
			head = current->next;
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
		delete current;
		no_of_vehicles--;
	}
	void display_vehicles() {
		vehicles* current = head;
		while (current != nullptr) {
			cout << current->st << "-" << current->en << ": " << current->id ;
			cout << " Vehicle path:" << current->path<<"\n";
			current = current->next;
		}
	}
};
