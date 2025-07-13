#include <iostream>
#include <vector>
#include <queue>
#include <limits>

// 🔹 1️⃣ Graph Representation & Input Handling (Person 1)
// 📌 Implements a bipartite graph representation for emergency vehicles and incidents.
class HopcroftKarp {
private:
    int numVehicles, numLocations;
    std::vector<std::vector<int>> graph;
    std::vector<int> matchedVehicle;
    std::vector<int> matchedLocation;
    std::vector<int> distance;
    const int NIL = 0;
    const int INF = std::numeric_limits<int>::max();

public:
    HopcroftKarp(int v, int l) : numVehicles(v), numLocations(l) {
        graph.resize(numVehicles + 1);
        matchedVehicle.resize(numLocations + 1, NIL);
        matchedLocation.resize(numVehicles + 1, NIL);
        distance.resize(numVehicles + 1);
    }
    
    void addEdge(int vehicle, int location) {
        graph[vehicle].push_back(location);
    }
    
    // 🔹 2️⃣ BFS for Finding Augmenting Paths (Person 2)
    // 📌 Implements BFS to find the shortest augmenting paths.
    bool bfs() {
        std::queue<int> q;
        for (int vehicle = 1; vehicle <= numVehicles; vehicle++) {
            if (matchedLocation[vehicle] == NIL) {
                distance[vehicle] = 0;
                q.push(vehicle);
            } else {
                distance[vehicle] = INF;
            }
        }
        
        distance[NIL] = INF;
        
        while (!q.empty()) {
            int vehicle = q.front();
            q.pop();
            
            if (distance[vehicle] < distance[NIL]) {
                for (int location : graph[vehicle]) {
                    int nextVehicle = matchedVehicle[location];
                    if (distance[nextVehicle] == INF) {
                        distance[nextVehicle] = distance[vehicle] + 1;
                        q.push(nextVehicle);
                    }
                }
            }
        }
        return distance[NIL] != INF;
    }
    
    // 🔹 3️⃣ DFS for Maximum Matching (Person 3)
    // 📌 Implements DFS to find augmenting paths and update matches.
    bool dfs(int vehicle) {
        if (vehicle == NIL) return true;
        
        for (int location : graph[vehicle]) {
            int nextVehicle = matchedVehicle[location];
            
            if (distance[nextVehicle] == distance[vehicle] + 1) {
                if (dfs(nextVehicle)) {
                    matchedVehicle[location] = vehicle;
                    matchedLocation[vehicle] = location;
                    return true;
                }
            }
        }
        
        distance[vehicle] = INF;
        return false;
    }
    
    // 🔹 4️⃣ Main Algorithm + Visualization (Person 4)
    // 📌 Integrates BFS and DFS to find the maximum matching and prints results.
    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int vehicle = 1; vehicle <= numVehicles; vehicle++) {
                if (matchedLocation[vehicle] == NIL && dfs(vehicle)) {
                    matching++;
                }
            }
        }
        return matching;
    }
    
    void printMatching() {
        std::cout << "Emergency Vehicle Assignments:\n";
        for (int vehicle = 1; vehicle <= numVehicles; vehicle++) {
            if (matchedLocation[vehicle] != NIL) {
                std::cout << "Vehicle " << vehicle << " is assigned to emergency location " 
                          << matchedLocation[vehicle] << std::endl;
            } else {
                std::cout << "Vehicle " << vehicle << " is not assigned\n";
            }
        }
    }
    
    bool allEmergenciesHandled() {
        for (int location = 1; location <= numLocations; location++) {
            if (matchedVehicle[location] == NIL) return false;
        }
        return true;
    }
};

std::vector<std::vector<bool>> buildResponseTimeGraph(
    const std::vector<std::vector<int>>& responseTime,
    int timeLimit) {
    int numVehicles = responseTime.size();
    int numLocations = responseTime[0].size();
    std::vector<std::vector<bool>> canReach(numVehicles, std::vector<bool>(numLocations, false));
    
    for (int vehicle = 0; vehicle < numVehicles; vehicle++) {
        for (int location = 0; location < numLocations; location++) {
            if (responseTime[vehicle][location] <= timeLimit) {
                canReach[vehicle][location] = true;
            }
        }
    }
    return canReach;
}

int main() {
    int numVehicles, numLocations, timeLimit;
    std::cout << "Enter the number of emergency vehicles: ";
    std::cin >> numVehicles;
    std::cout << "Enter the number of emergency locations: ";
    std::cin >> numLocations;
    std::vector<std::vector<int>> responseTime(numVehicles, std::vector<int>(numLocations));
    
    std::cout << "Enter the response time matrix:\n";
    for (int vehicle = 0; vehicle < numVehicles; vehicle++) {
        for (int location = 0; location < numLocations; location++) {
            std::cin >> responseTime[vehicle][location];
        }
    }
    
    std::cout << "Enter the maximum acceptable response time: ";
    std::cin >> timeLimit;
    auto canReach = buildResponseTimeGraph(responseTime, timeLimit);
    HopcroftKarp hk(numVehicles, numLocations);
    
    for (int vehicle = 0; vehicle < numVehicles; vehicle++) {
        for (int location = 0; location < numLocations; location++) {
            if (canReach[vehicle][location]) {
                hk.addEdge(vehicle + 1, location + 1);
            }
        }
    }
    
    int maxMatches = hk.maxMatching();
    std::cout << "\nRESULTS:\n";
    std::cout << "Maximum number of emergencies that can be handled: " << maxMatches << std::endl;
    hk.printMatching();
    
    std::cout << "Number of unhandled emergencies: " << (numLocations - maxMatches) << std::endl;
    return 0;
}