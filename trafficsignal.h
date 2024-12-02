#pragma once
#include<ctime>
class signal {
	int s;
public:
	signal() {
		s = 0;
	}
	signal(int val) {
		s = val;
	}
	int get_signal() {
		return s;
	}
	void set_signal(int val) {
		s = val;
	}
};
struct Traffic {
	int vehicles;
	int time;
	Traffic* next;
	Traffic() {
		next = nullptr;
		vehicles = 0;
		time = 0;
	}
	Traffic(int v, int t) {
		next = nullptr;
		vehicles = v;
		time = t;
	}
};
class traffic_priority_queue {
	Traffic* head;
public:
	traffic_priority_queue() {
		head = nullptr;
	}
	void add_traffic(Traffic t) {
		Traffic* temp = new Traffic(t);
		if (head == nullptr || head->vehicles < t.vehicles) { 
			temp->next = head;
			head = temp;
		}
		else {
			Traffic* current = head;
			while (current->next != nullptr && current->next->vehicles >= t.vehicles) {
				current = current->next;
			}
			temp->next = current->next;
			current->next = temp;
		}
	}
	void display_traffic() {
		Traffic* current = head;
		while (current != nullptr) {
			cout << "Traffic: " << current->vehicles << " vehicles, " << current->time << " seconds" << endl;
			current = current->next;
		}
	}
		Traffic* get_traffic() {
		if (head == nullptr) return nullptr;
		Traffic* temp = head;
		head = head->next;
		return temp;
	}
	bool isEmpty() {
		return head == nullptr;
	}
};