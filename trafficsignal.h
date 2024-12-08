#pragma once
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
	int ttime;
	Traffic* next;
	char c;
	Traffic() {
		next = nullptr;
		vehicles = 0;
		ttime = 0;
		c = ' ';
	}
	Traffic(int v, int t,char n) {
		next = nullptr;
		vehicles = v;
		ttime = t;
		c = n;

	}
};
class traffic_priority_queue {
	Traffic* head;
public:
	traffic_priority_queue() {
		head = nullptr;
	}
	void dequeue() {
		if (head == nullptr) {
			return;
		}
		else {
			Traffic* temp = head;
			head = head->next;
			delete temp;
		}
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
	void empty() {
		Traffic* temp;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
		}
	}
	Traffic* getHead() {
		return head;
	}
	void display_traffic() {
		Traffic* current = head;
		cout << "\n\t\t\t\t\t\t --------------";
		cout << "\n\t\t\t\t\t\t|Traffic Signal|";
		cout << "\n\t\t\t\t\t\t --------------\n\n";
		while (current != nullptr) {
			cout <<"Vertex:"<<current->c << " ->Traffic: " << current->vehicles 
		<< " vehicles, " << current->ttime << " seconds ";
			cout << endl;
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
