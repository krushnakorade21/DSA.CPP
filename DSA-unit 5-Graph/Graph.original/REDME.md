Water Depot Network: Shortest Repair Route using Dijkstra's Algorithm

A C++ program that represents the water depot, road junctions and repair locations as vertices and roads as weighted edges, then applies Dijkstra's algorithm to find the least-cost route and total distance from the water depot (or any selected source vertex) to a selected repair location.

📌 Problem Statement

Develop a C++ program to represent a water depot, road junctions, and repair locations as vertices with non-negative travel distances as edge weights. Apply Dijkstra's algorithm to determine the least-cost route to a selected repair location and display the route and total distance. Modify the program to select a different source vertex and recalculate the shortest distances.

🎯 Objective
Represent a water supply road network as a weighted graph using an adjacency list.
Implement Dijkstra's algorithm using a min-priority queue.
Display the shortest distance and the complete location sequence to a repair location.
Select a different source vertex and recalculate the shortest distances to all locations.
Handle edge cases such as invalid locations and unreachable repair locations.
✨ Features
Menu-driven program
Add new locations (water depot, road junction or repair location) and roads at runtime
Locations can be entered by number, full name or a unique part of the name (case-insensitive)
Preloaded sample water depot network (Sangamner area)
Display all locations and the full network
Shortest distance and route from the Water Depot to a selected repair location
Change the source vertex and recalculate the shortest distance to all other locations
Clear messages for "Invalid repair location" and "No route exists"
Input validation (negative distances, empty names and roads from a location to itself are rejected)
🧠 Concept Used

The water supply road network is modelled as an undirected weighted graph:

Water Network Term	Graph Term
Water depot, road junction, repair location	Vertex
Road between two locations	Edge
Distance in km	Edge weight

Dijkstra's algorithm works on graphs with non-negative weights. It always finalizes the unvisited location with the smallest known distance, then updates (relaxes) the distances of its neighbours. A parent[] array stores the previous location on the best path, so the route can be rebuilt after the search.

⚙️ Algorithm (Summary)
Build the graph using an adjacency list (location = vertex, road = edge with distance in km as weight).
Read the source (the Water Depot, or any other vertex chosen by the user) and the repair location; display an error if either is invalid.
Initialize dist[] = INFINITY, parent[] = -1, visited[] = false.
Set dist[source] = 0 and push (0, source) into a min-priority queue.
Remove the location u with the smallest distance and mark it visited.
For each neighbour v of u with weight w, if dist[u] + w < dist[v], update dist[v] and parent[v] = u, then push (dist[v], v) into the queue.
Repeat until the queue is empty.
If dist[repair location] = INFINITY, display "No route exists".
Otherwise, trace parent[] from the repair location back to the source and reverse it to get the route.
Display the shortest distance and the route.
To select a different source vertex, read the new source and repeat steps 3 to 10.
⏱️ Complexity Analysis
Operation	Time Complexity	Space Complexity
Add location	O(log V)	O(1)
Add road	O(V)	O(1)
Dijkstra's algorithm	O((V + E) log V)	O(V + E)
Change source vertex	O((V + E) log V)	O(V)
Path reconstruction	O(V)	O(V)

V = number of locations, E = number of roads.

📁 Project Structure
Water-Depot-Dijkstra/
│── water_depot_dijkstra.cpp  # Source code
│── Algorithm.pdf             # Step-wise algorithm
│── Flowchart.pdf             # Flowchart of the program
│── Output.png                # Program output screenshots
│── Output_Analysis.pdf       # Analysis of the output
│── Report.pdf                # Project report
│── README.md                 # Project documentation
🚀 How to Compile and Run

Requirements: a C++ compiler (g++ recommended)

bash
g++ water_depot_dijkstra.cpp -o water_depot_dijkstra
./water_depot_dijkstra

On Windows:

bash
g++ water_depot_dijkstra.cpp -o water_depot_dijkstra.exe
water_depot_dijkstra.exe
🧪 Sample Input and Output

Preloaded roads (distance in km):

Location A	Location B	Distance
Sangamner Water Depot	Bus Stand Chowk	4
Sangamner Water Depot	Nashik Naka	7
Bus Stand Chowk	Nashik Naka	2
Bus Stand Chowk	Pune Naka	6
Nashik Naka	Ghulewadi Junction	5
Pune Naka	Samnapur	3
Pune Naka	Ghulewadi Junction	4
Ghulewadi Junction	MIDC Area	6
Ghulewadi Junction	Amrutvahini College	8
Samnapur	MIDC Area	5

Source: Sangamner Water Depot

Repair Location	Shortest Distance	Route
Samnapur	13 km	Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur
MIDC Area	17 km	Sangamner Water Depot -> Bus Stand Chowk -> Nashik Naka -> Ghulewadi Junction -> MIDC Area
Amrutvahini College	19 km	Sangamner Water Depot -> Bus Stand Chowk -> Nashik Naka -> Ghulewadi Junction -> Amrutvahini College
Hospital	Invalid repair location	Error message displayed

Source changed to: Pune Naka (Modification A)

Repair Location	Shortest Distance	Route
Samnapur	3 km	Pune Naka -> Samnapur
MIDC Area	8 km	Pune Naka -> Samnapur -> MIDC Area
Amrutvahini College	12 km	Pune Naka -> Ghulewadi Junction -> Amrutvahini College

Example run (Water Depot to Samnapur):

Source          : Sangamner Water Depot
Repair Location : Samnapur
Total Distance  : 13 km
Route           : Sangamner Water Depot -> Bus Stand Chowk -> Pune Naka -> Samnapur

Example run (new source Pune Naka to MIDC Area):

Source          : Pune Naka
Repair Location : MIDC Area
Total Distance  : 8 km
Route           : Pune Naka -> Samnapur -> MIDC Area
⚠️ Edge Cases Handled
Source or repair location not present in the network
Selected destination is not a repair location
Source and repair location are the same location (distance 0)
Repair location not reachable from the source
Duplicate location names (rejected, case-insensitive)
Partial name matching more than one location (rejected as not found)
Negative distance input
Road from a location to itself
Invalid menu choice
💡 Applications
Planning repair routes for water pipeline and supply networks
GPS and road navigation systems
Emergency vehicle and maintenance crew dispatch
Logistics and delivery path optimization
🔮 Future Scope
Add location or road deletion
Support directed (one-way) roads
Use travel time or fuel cost as alternate weights
Load the road network from a file
👤 Author

Name: Shubham Rambhau Barkade Roll No: 110 Course: Data Structures and Algorithms Institute: Amrutvahini College of Engineering, Sangamner

⭐ If you found this project helpful, consider giving it a star!
