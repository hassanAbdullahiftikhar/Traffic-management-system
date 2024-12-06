#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct road {
	int cars_n;
	char location;
	road() {
		location = ' ';
		cars_n = -1;
	}
	road(char s,int i) {
		cars_n = i;
		location = s;
	}
};
class congestion_heap {
	int n;
	road* cars=nullptr;
	int	index = 1;
	int left_c(int i) {
		return 2 * i;
	}
	int right_c(int i) {
		return 2 * i + 1;
	}
	int parent(int i) {
		return i / 2;
	}
	void heapify(int i) {
		while (i > 1 && cars[parent(i)].cars_n < cars[i].cars_n) {
			road temp = cars[i];
			cars[i] = cars[parent(i)];
			cars[parent(i)] = temp;
			i = parent(i);
		}
	}
	void delete_top(int i) {
		int largest = i;
		int left = left_c(i);
		int right = right_c(i);

		if (left <= index && cars[left].cars_n > cars[largest].cars_n)
			largest = left;
		if (right <= index && cars[right].cars_n > cars[largest].cars_n)
			largest = right;

		if (largest != i) {
			road temp = cars[i];
			cars[i] = cars[largest];
			cars[largest] = temp;
			heapify(largest);
		}
	}
public:
	congestion_heap() {
		n = -1;
	}
	congestion_heap(int size) {
		n = size+1;
		cars = new road[size + 2];
		for (int i = 0; i <= size; i++) {
			cars[i].cars_n = -1;
			cars[i].location = ' ';
		}
	}
	void insert_car(road s) {
		if (index < n) {
			cars[index] = s;
			heapify(index);
			index++;
		}
	}
	void display_congestion_levels() {
		cout << "----------------Congestion levels------------------\n";
		for (int i = 1; i < n; i++) {
			cout <<"Intersection point:" << cars[i].location<<",No of cars:" << cars[i].cars_n << "\n";
		}
	}
	void remove() {
		road min = cars[1];
		cars[1] = cars[index--];
		heapify(1);
	}
	};