# 🚨 Emergency Vehicle Assignment using Hopcroft-Karp Algorithm

## 📌 Problem Statement
In emergency situations like fires or accidents, it's crucial to assign available vehicles (e.g., ambulances, fire trucks) to the nearest emergency sites within a strict time limit. This project helps automate and optimize that assignment using **graph theory** and the **Hopcroft-Karp Algorithm**.

---

## 🔍 How It Works

### 🔹 1. Problem as a Bipartite Graph
- We treat:
  - **Vehicles** as one set of nodes.
  - **Emergency Locations** as another set of nodes.
- An **edge** connects a vehicle to a location if it can reach within the given time limit.

### 🔹 2. Graph Construction
- **Input**:
  - Number of vehicles and locations
  - A response time matrix
  - The maximum allowed response time
- We create a graph where only valid vehicle-location pairs (within time limit) are connected.

### 🔹 3. Maximum Matching with Hopcroft-Karp
- Uses a **BFS + DFS** combo to find the **maximum number of emergency assignments**.
- Ensures **no two vehicles are assigned to the same location**.
- Guarantees **optimal performance** in large-scale emergencies.

---

## 🧠 Algorithms Used

### ✅ Hopcroft-Karp Algorithm
- Efficient for bipartite graphs
- Time Complexity: **O(√V × E)**  
- Space Complexity: **O(V + E)**

### 🔁 Components:
- **BFS**: Finds shortest augmenting paths
- **DFS**: Updates matchings along these paths

---

## 🔢 Example Input
Enter number of emergency vehicles: 3
Enter number of emergency locations: 3
Enter response time matrix:
2 9 4
7 5 3
8 1 6
Enter maximum acceptable response time: 5


### 🧾 Output
Maximum number of emergencies that can be handled: 3
Vehicle 1 is assigned to emergency location 1
Vehicle 2 is assigned to emergency location 3
Vehicle 3 is assigned to emergency location 2
Number of unhandled emergencies: 0

---

## 🚀 Why This Project is Useful
- ✅ **Real-world relevance**: Ambulance/fire/police dispatch
- 🔁 **Efficient matching**: Fast and optimal
- 💡 **Teaches graph algorithms**: Bipartite matching, BFS, DFS

---

## 📦 Files Included
- `main.cpp` – Full C++ code
- `README.md` – Explanation, instructions, and algorithm details
