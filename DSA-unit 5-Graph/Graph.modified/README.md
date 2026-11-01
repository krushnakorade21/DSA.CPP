# Water Depot Network: Shortest Repair Route using Dijkstra's Algorithm

A C++ program that represents the **water depot, road junctions and repair locations as vertices** and **roads as weighted edges**, then applies **Dijkstra's algorithm** to find the least-cost route and total distance from a selected source to a selected repair location. It also lets the user **change the source vertex**, view the **complete shortest path**, and **update a road distance** with automatic recalculation.

---

## 📌 Problem Statement

Develop a C++ program to represent a water depot, road junctions, and repair locations as vertices with non-negative travel distances as edge weights. Apply Dijkstra's algorithm to determine the least-cost route to a selected repair location and display the route and total distance. Modify the program to (A) select a different source vertex and recalculate the shortest distances, (B) display the complete shortest path to a destination, not only its distance, and (C) update an edge weight and recalculate the shortest paths.

---

## 🎯 Objective

- Represent a water supply road network as a weighted graph using an adjacency list.
- Implement Dijkstra's algorithm using a min-priority queue.
- Display the shortest distance and the complete location sequence to a repair location (and to every other location).
- Select a different source vertex and recalculate the shortest distances (Modification A).
- Display the complete shortest path, not only its distance (Modification B).
- Update the distance of an existing road and recalculate the shortest paths (Modification C).
- Handle edge cases such as invalid locations and unreachable repair locations.

---

## ✨ Features

- Menu-driven program
- Add new locations (water depot, road junction or repair location) and roads at runtime
- Locations can be entered by number, full name or a unique part of the name (case-insensitive)
- Preloaded sample water depot network (Sangamner area)
- Display all locations and the full network
- Shortest distance and complete route from any source to a selected repair location
- Complete shortest path from the source to every other location
- Change the source location and recalculate (the repair location is remembered)
- Update a road distance and recalculate the shortest routes automatically
- Clear messages for "Invalid location", "Not a repair location" and "No route exists"
- Input validation (negative distances, empty names, duplicate roads and roads from a location to itself are rejected)

---

## 📋 Menu

| Option | Description |
|--------|-------------|
| 1 | Add location |
| 2 | Add road |
| 3 | Display all locations |
| 4 | Display network |
| 5 | Find shortest route (select source and repair location) |
| 6 | Change source location and recalculate (Modification A) |
| 7 | Update road distance and recalculate (Modification C) |
| 8 | Exit |

*Modification B (complete shortest path) is shown automatically in options 5, 6 and 7.*

---

## 🧠 Concept Used

The water supply road network is modelled as an **undirected weighted graph**:

| Water Network Term | Graph Term |
|--------------------|------------|
| Water depot, road junction, repair location | Vertex |
| Road between two locations | Edge |
| Distance in km | Edge weight |

Dijkstra's algorithm works on graphs with non-negative weights. It always finalizes the unvisited location with the smallest known distance, then updates (relaxes) the distances of its neighbours. A `parent[]` array stores the previous location on the best path, so the complete route can be rebuilt after the search. When the source changes or a road distance is updated, the algorithm is simply run again on the updated graph.

---

## ⚙️ Algorithm (Summary)

1. Build the graph using an adjacency list (location = vertex, road = edge with distance in km as weight).
2. Read the source and the repair location; display an error if either is invalid or the destination is not a repair location.
3. Initialize `dist[] = INFINITY`, `parent[] = -1`, `visited[] = false`.
4. Set `dist[source] = 0` and push `(0, source)` into a min-priority queue.
5. Remove the location `u` with the smallest distance and mark it visited.
6. For each neighbour `v` of `u` with weight `w`, if `dist[u] + w < dist[v]`, update `dist[v]` and `parent[v] = u`, then push `(dist[v], v)` into the queue.
7. Repeat until the queue is empty.
8. If `dist[repair location] = INFINITY`, display "No route exists".
9. Otherwise, trace `parent[]` from the repair location back to the source and reverse it to get the complete route.
10. Display the total distance and the complete route (and the distance and route to every other location).
11. **Modification A:** to select a different source vertex, read the new source and repeat steps 3 to 10.
12. **Modification C:** to update a road distance, read the two locations and the new distance, update the weight in both directions, and repeat steps 3 to 10 from the same source.

---

## ⏱️ Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Add location | O(log V) | O(1) |
| Add road | O(V) | O(1) |
| Dijkstra's algorithm | O((V + E) log V) | O(V + E) |
| Complete path to one location | O(V) | O(V) |
| Paths to all locations | O(V²) | O(V) |
| Change source vertex (A) | O((V + E) log V + V²) | O(V) |
| Update road distance (C) | O((V + E) log V + V²) | O(V) |

*V = number of locations, E = number of roads.*

---

## 📁 Project Structure

```
Water-Depot-Dijkstra/
│── water_depot_dijkstra.cpp  # Source code
│── Algorithm.pdf             # Step-wise algorithm
│── Flowchart.pdf             # Flowchart of the program
│── Output.png                # Program output screenshots
│── Output_Analysis.md        # Analysis of the output
│── Report.pdf                # Project report
│── README.md                 # Project documentation
```

---

## 🚀 How to Compile and Run

**Requirements:** a C++ compiler (g++ recommended)

```bash
g++ water_depot_dijkstra.cpp -o water_depot_dijkstra
./water_depot_dijkstra
```

On Windows:

```bash
g++ water_depot_dijkstra.cpp -o water_depot_dijkstra.exe
water_depot_dijkstra.exe
```

---

## 🧪 Sample Input and Output

**Preloaded roads (distance in km):**

| Location A | Location B | Distance |
|------------|------------|----------|
| Sangamner Water Depot | Bus Stand Chowk | 4 |
| Sangamner Water Depot | Nashik Naka | 7 |
| Bus Stand Chowk | Nashik Naka | 2 |
| Bus Stand Chowk | Pune Naka | 6 |
| Nashik Naka | Ghulewadi Junction | 5 |
| Pune Naka | Samnapur | 3 |
| Pune Naka | Ghulewadi Junction | 4 |
| Ghulewadi Junction | MIDC Area | 6 |
| Ghulewadi Junction | Amrutvahini College | 8 |
| Samnapur | MIDC Area | 5 |

**Source: Sangamner Water Depot**

| Repair Location | Shortest Distance | Complete Route |
|-----------------|-------------------|----------------|
| Samnapur | 13 km | Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur |
| MIDC Area | 17 km | Sangamner Water Depot -> Bus Stand Chowk -> Nashik Naka -> Ghulewadi Junction -> MIDC Area |
| Amrutvahini College | 19 km | Sangamner Water Depot -> Bus Stand Chowk -> Nashik Naka -> Ghulewadi Junction -> Amrutvahini College |
| Hospital | Invalid location | Error message displayed |
| Nashik Naka | Not a repair location | Error message displayed |

**Modification A: source changed to Pune Naka**

| Repair Location | Shortest Distance | Complete Route |
|-----------------|-------------------|----------------|
| Samnapur | 3 km | Pune Naka -> Samnapur |
| MIDC Area | 8 km | Pune Naka -> Samnapur -> MIDC Area |
| Amrutvahini College | 12 km | Pune Naka -> Ghulewadi Junction -> Amrutvahini College |

**Modification C: road Bus Stand Chowk - Pune Naka updated from 6 km to 1 km (source: Sangamner Water Depot)**

| Repair Location | Before | After | Complete Route (After) |
|-----------------|--------|-------|------------------------|
| Samnapur | 13 km | 8 km | Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur |
| MIDC Area | 17 km | 13 km | Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur -> MIDC Area |
| Amrutvahini College | 19 km | 17 km | Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Ghulewadi Junction -> Amrutvahini College |

**Example run (Water Depot to Samnapur):**

```
Source          : Sangamner Water Depot
Repair Location : Samnapur
Total Distance  : 13 km
Route           : Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur
```

**Example run (road updated, recalculated):**

```
Road updated: Bus Stand Chowk - Pune Naka changed from 6 km to 1 km.
Recalculating shortest routes...

Source          : Sangamner Water Depot
Repair Location : Samnapur
Total Distance  : 8 km
Route           : Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur
```

---

## ⚠️ Edge Cases Handled

- Source or repair location not present in the network
- Selected destination is not a repair location
- Source and repair location are the same location (distance 0)
- Repair location not reachable from the source
- Duplicate location names (rejected, case-insensitive)
- Duplicate road between the same two locations (use the update option instead)
- Partial name matching more than one location (rejected as not found)
- Updating a road that does not exist
- Negative distance input
- Road from a location to itself
- Invalid menu choice or non-numeric input

---

## 💡 Applications

- Planning repair routes for water pipeline and supply networks
- GPS and road navigation systems
- Emergency vehicle and maintenance crew dispatch
- Logistics and delivery path optimization

---

## 🔮 Future Scope

- Add location or road deletion
- Support directed (one-way) roads
- Use travel time or fuel cost as alternate weights
- Load the road network from a file

---

## 👤 Author

**Name:** Shubham Rambhau Barkade
**Roll No:** 110
**Course:** Data Structures and Algorithms
**Institute:** Amrutvahini College of Engineering, Sangamner

---

⭐ If you found this project helpful, consider giving it a star!
