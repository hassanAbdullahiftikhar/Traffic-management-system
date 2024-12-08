# Traffic Management System

This project implements a traffic management simulation using key data structures, including:

- **Hash Tables**  
- **Weighted Directional Graphs**  
- **Priority Queues**  
- **Max Heaps**  
- **Lists**  
- **Arrays**  

The simulation focuses on **smart traffic management**, addressing key aspects such as:

- Congestion resolution  
- Smart traffic signal management  
- Vehicle routing  

Additionally, the program keeps track of vehicle positions and identifies the most congested roads. Overridden methods for emergency vehicles provide the ability to reroute them by clearing road paths and blocked roads.

---

## Project Structure

1. **Road Network**  
   Represented as a **weighted directional graph** using adjacency lists and a hash table.

2. **Vehicles**  
   Stored in the form of **lists**.

3. **Emergency Vehicles**  
   Managed using **priority queues**.

4. **Traffic Signals**  
   Controlled using **priority queues**.

5. **Congested Areas**  
   Maintained in the form of a **max heap**.

6. **Blocked Roads**  
   Managed as lists.

---

## Algorithms

This project makes use of efficient algorithms for key tasks, such as:

- **Dijkstra's Algorithm**  
  Used for the calculation of shortest paths and assigning vehicle routes.

- **Depth First Search (DFS)**  
  Utilized on the weighted graph to calculate all possible paths from a given vertex.

---

## Features

- Smart traffic management simulation.
- Identification of the most congested roads and areas.
- Automatic rerouting of emergency vehicles to ensure timely response.
- Dynamic traffic signal management based on real-time congestion data.

---

## Running the Code

1. Create a new project on Visual Studio Community.
2. Add the necessary header files and `weightedgraph.cpp`.
3. Build the project.

---

## Project Visuals

### **Menu**
<img width="845" alt="Menu" src="https://github.com/user-attachments/assets/13ba541e-5e82-45eb-af20-3f953c23877d">

### **Road Network**
<img width="650" alt="Road Network" src="https://github.com/user-attachments/assets/8b4c5eca-eb87-4087-87f9-3c58633237b2">

### **All Possible Paths**
<img width="842" alt="All Possible Paths" src="https://github.com/user-attachments/assets/7892adba-48be-4652-9f7f-d7496cbd2295">

### **Traffic Signals**
<img width="848" alt="Traffic Signals" src="https://github.com/user-attachments/assets/8b8f8d5e-de23-4580-bbb5-9164b5332131">

### **Congestion Resolution**
<img width="866" alt="Congestion Resolution" src="https://github.com/user-attachments/assets/615a6df4-1f9a-4aee-8d62-d563d36b8d70">

### **Vehicles**
<img width="958" alt="Vehicles" src="https://github.com/user-attachments/assets/3c66ba99-2481-4939-9e64-593da67f24d3">

### **Blocked Roads**
<img width="887" alt="Blocked Roads" src="https://github.com/user-attachments/assets/2eb1b878-3f10-4289-8ef4-16292f5d8ad7">

### **Blocking Roads**
<img width="557" alt="Blocking Roads" src="https://github.com/user-attachments/assets/a0a17354-c935-44aa-976b-4ca7decd1f59">

### **Unblocking Roads**
<img width="884" alt="Unblocking Roads" src="https://github.com/user-attachments/assets/388b08f3-f9e2-4258-a62d-0dcefdd242ad">

### **Moving Emergency Vehicles**
<img width="868" alt="Moving Emergency Vehicles" src="https://github.com/user-attachments/assets/6742f1d4-78cf-4a6a-8e60-356cc7ba58cd">

### **Adding a Vehicle**
<img width="959" alt="Adding a Vehicle" src="https://github.com/user-attachments/assets/a0b865f8-4e73-4d63-815d-8717facb20a4">
