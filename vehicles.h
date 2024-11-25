#pragma once
#include<string>
using namespace std;
struct vehicles {
	char st, en;
	string id;
	vehicles* next;
	vehicles() {
		st = en = ' ';
		id = ' ';
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
public:
	vehicle_list() {
		head = nullptr;
	}
	void add_vehicle(vehicles v) {
		vehicles* temp = new vehicles(v);
		if (head == nullptr) {
			head = temp;
		}
		else {
			vehicles* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = temp;
		}
	}
	void remove_vehicle(string id) {
		if (head == nullptr) return;
		vehicles* current = head;
		vehicles* previous = nullptr;
		if (current != nullptr && current->id == id) {
			head = current->next;
			delete current;
			return;
		}
		while (current != nullptr && current->id != id) {
			previous = current;
			current = current->next;
		}
		if (current == nullptr) return;
		previous->next = current->next;
		delete current;
	}
	void display_vehicles() {
		vehicles* current = head;
		while (current != nullptr) {
			cout << current->st << "-" << current->en << ": " << current->id << endl;
			current = current->next;
		}
	}
};