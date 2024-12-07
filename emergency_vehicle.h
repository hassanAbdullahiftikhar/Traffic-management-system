#pragma once
#include <iostream>
#include<string>
#include<fstream>
#include <sstream>
using namespace std;
struct emergency_node
{
	string id , priority_level;
	char start, end;
	emergency_node* next;
	emergency_node(const string &temp_id = " " , const string &temp_priority_level=" " ,const char temp_start ='\0' ,const char temp_end = '\0')
	{
		id = temp_id;
		priority_level = temp_priority_level;
		start = temp_start;
		end = temp_end;
		next = nullptr;
	}
};
class emergency_list
{
	emergency_node* head;
public:
	emergency_list()
	{
		head = nullptr;
	}
	void load_emergency_vehicles()
	{
		fstream file;
		file.open("emergency_vehicles .csv", ios::in);
		string data;
		string id, priority_level;
		string start, end;
		getline(file, data);
		while (getline(file, data))
		{
			stringstream ss(data);
			getline(ss, id, ',');
			getline(ss, start, ',');
			getline(ss, end, ',');
			getline(ss, priority_level, ',');
			if (id == ",")
				break;

			insert(id, start[0], end[0], priority_level);
		}
	}
	void insert(const string& id, const char start, const char end, const string& priority_level)
	{
		if (head == nullptr)
		{
			head = new emergency_node(id, priority_level, start, end);
			return;
		}
		else
		{
			if (priority_level == "High")
			{
				emergency_node* temp = new emergency_node(id, priority_level, start, end);
				temp->next = head;
				head = temp;
				temp = nullptr;
			}
			else if (priority_level == "Medium")
			{
				emergency_node* traverse = head;
				while (traverse->next != nullptr)
					traverse = traverse->next;
				traverse->next = new emergency_node(id, priority_level, start, end);
			}
		}
	}

	emergency_node* find_vehicle(string id)
	{
		emergency_node* temp = head;
		if (head == nullptr)
			return nullptr;
		if (temp->id == id)
		{
			emergency_node* temp2 = head;
			head = head->next;
			return temp2;
		}
		else
		{
			emergency_node* temp = head;
			emergency_node* temp2 = head;
			while (temp != nullptr && temp->id != id)
			{
				temp2 = temp;
				temp = temp->next;
			}
			if (temp != nullptr)
			{
				temp2->next = temp->next;
				return temp;
			}
			else
			{
				return nullptr;
			}
		}
	}

	void print_vehicles()
	{
		emergency_node* temp = head;
		if (temp==nullptr)
		{
			cout << "\n\t\t->No Vehicle Present\n";
			return;
		}
		cout << '\n';
		while (temp != nullptr)
		{
			cout << "\t\t->" << temp->id << endl;// " Vehicle path: " << temp->start << "-" << temp->end << endl;
			temp = temp->next;
		}
	}
	bool is_empty() const
	{
		return head == nullptr;
	}
	emergency_node * get_head() const
	{
		return head;
	}
	void delete_head()
	{
		emergency_node* temp = head;
		head = head->next;
		delete temp;
	}
};
