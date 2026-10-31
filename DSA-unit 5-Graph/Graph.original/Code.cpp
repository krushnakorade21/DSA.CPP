#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <limits>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

// Vertex types
const int DEPOT    = 1;
const int JUNCTION = 2;
const int REPAIR   = 3;

struct WaterNetwork {
    int n;                                        // number of vertices
    vector<string> names;                         // index -> location name
    vector<int> type;                             // index -> DEPOT / JUNCTION / REPAIR
    map<string, int> idOf;                        // location name -> index
    vector<vector<pair<int, int>>> adj;           // adj[u] = {(v, weight), ...}
};

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

string typeName(int t) {
    if (t == DEPOT) return "Water Depot";
    if (t == JUNCTION) return "Road Junction";
    return "Repair Location";
}

void initNetwork(WaterNetwork& wn) {
    wn.n = 0;
}

int addLocation(WaterNetwork& wn, const string& name, int t) {
    string key = toLower(name);
    if (wn.idOf.count(key)) return wn.idOf[key];
    wn.idOf[key] = wn.n;
    wn.names.push_back(name);
    wn.type.push_back(t);
    wn.adj.push_back({});
    return wn.n++;
}

int findLocation(WaterNetwork& wn, const string& name) {
    string key = toLower(name);
    return wn.idOf.count(key) ? wn.idOf[key] : -1;
}

bool addRoad(WaterNetwork& wn, const string& a, const string& b, int w) {
    int u = findLocation(wn, a);
    int v = findLocation(wn, b);
    if (u == -1 || v == -1) return false;
    wn.adj[u].push_back({v, w});
    wn.adj[v].push_back({u, w});                  // two-way road
    return true;
}

int findDepot(WaterNetwork& wn) {
    for (int i = 0; i < wn.n; i++)
        if (wn.type[i] == DEPOT) return i;
    return -1;
}

void displayLocations(WaterNetwork& wn) {
    cout << "\nLocations:\n";
    for (int i = 0; i < wn.n; i++)
        cout << "  " << i + 1 << ". " << wn.names[i] << "  (" << typeName(wn.type[i]) << ")\n";
}

void displayRepairLocations(WaterNetwork& wn) {
    cout << "\nRepair Locations:\n";
    for (int i = 0; i < wn.n; i++)
        if (wn.type[i] == REPAIR)
            cout << "  - " << wn.names[i] << "\n";
}

void displayNetwork(WaterNetwork& wn) {
    cout << "\nWater Supply Road Network (Location -> Neighbour [distance]):\n";
    for (int u = 0; u < wn.n; u++) {
        cout << "  " << wn.names[u] << " -> ";
        for (size_t i = 0; i < wn.adj[u].size(); i++) {
            cout << wn.names[wn.adj[u][i].first] << " [" << wn.adj[u][i].second << " km]";
            if (i + 1 < wn.adj[u].size()) cout << ", ";
        }
        cout << "\n";
    }
}

// Dijkstra's algorithm: fills dist[] and parent[] for the given source
void dijkstra(WaterNetwork& wn, int src, vector<int>& dist, vector<int>& parent) {
    int n = wn.n;
    dist.assign(n, INF);
    parent.assign(n, -1);
    vector<bool> visited(n, false);

    // min-heap: (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto& edge : wn.adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Show route and total distance from src to dest
void showRoute(WaterNetwork& wn, int src, int dest, vector<int>& dist, vector<int>& parent) {
    cout << "\n--------------------------------------------\n";
    if (dist[dest] == INF) {
        cout << "No route exists from " << wn.names[src] << " to " << wn.names[dest] << ".\n";
        cout << "--------------------------------------------\n";
        return;
    }

    // Rebuild path from destination back to source
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Source          : " << wn.names[src] << "\n";
    cout << "Repair Location : " << wn.names[dest] << "\n";
    cout << "Total Distance  : " << dist[dest] << " km\n";
    cout << "Route           : ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << wn.names[path[i]];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\n--------------------------------------------\n";
}

void showAllDistances(WaterNetwork& wn, int src, vector<int>& dist) {
    cout << "\nShortest distance from " << wn.names[src] << " to all locations:\n";
    for (int i = 0; i < wn.n; i++) {
        cout << "  " << wn.names[i] << " : ";
        if (dist[i] == INF) cout << "Unreachable\n";
        else cout << dist[i] << " km\n";
    }
}

int main() {
    WaterNetwork wn;
    int choice;

    initNetwork(wn);

    // Preloaded sample network
    addLocation(wn, "Water Depot", DEPOT);
    addLocation(wn, "Junction A", JUNCTION);
    addLocation(wn, "Junction B", JUNCTION);
    addLocation(wn, "Junction C", JUNCTION);
    addLocation(wn, "Junction D", JUNCTION);
    addLocation(wn, "Repair Site 1", REPAIR);
    addLocation(wn, "Repair Site 2", REPAIR);
    addLocation(wn, "Repair Site 3", REPAIR);

    addRoad(wn, "Water Depot", "Junction A", 4);
    addRoad(wn, "Water Depot", "Junction B", 7);
    addRoad(wn, "Junction A", "Junction B", 2);
    addRoad(wn, "Junction A", "Junction C", 6);
    addRoad(wn, "Junction B", "Junction D", 5);
    addRoad(wn, "Junction C", "Repair Site 1", 3);
    addRoad(wn, "Junction C", "Junction D", 4);
    addRoad(wn, "Junction D", "Repair Site 2", 6);
    addRoad(wn, "Junction D", "Repair Site 3", 8);
    addRoad(wn, "Repair Site 1", "Repair Site 2", 5);

    do {
        cout << "\n===== WATER DEPOT NETWORK - DIJKSTRA =====\n";
        cout << "1. Add location\n";
        cout << "2. Add road\n";
        cout << "3. Display all locations\n";
        cout << "4. Display network\n";
        cout << "5. Find shortest route from Water Depot to a repair location\n";
        cout << "6. Change source vertex and recalculate distances\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name;
            int t;
            cout << "Enter location name : ";
            getline(cin, name);
            cout << "Type (1-Depot, 2-Junction, 3-Repair): ";
            cin >> t;
            cin.ignore();
            if (t < 1 || t > 3) {
                cout << "Invalid type.\n";
                break;
            }
            if (findLocation(wn, name) != -1) {
                cout << "Location already exists.\n";
                break;
            }
            addLocation(wn, name, t);
            cout << "Location added successfully.\n";
            break;
        }
        case 2: {
            string a, b;
            int w;
            cout << "Enter first location : ";
            getline(cin, a);
            cout << "Enter second location: ";
            getline(cin, b);
            cout << "Enter distance (km)  : ";
            cin >> w;
            cin.ignore();
            if (w < 0) {
                cout << "Distance cannot be negative.\n";
                break;
            }
            if (!addRoad(wn, a, b, w))
                cout << "Error: One or both locations do not exist. Add them first.\n";
            else
                cout << "Road added successfully.\n";
            break;
        }
        case 3:
            displayLocations(wn);
            break;
        case 4:
            displayNetwork(wn);
            break;
        case 5: {
            int src = findDepot(wn);
            if (src == -1) {
                cout << "\nError: No water depot defined.\n";
                break;
            }
            string r;
            displayRepairLocations(wn);
            cout << "\nEnter repair location: ";
            getline(cin, r);
            int dest = findLocation(wn, r);
            if (dest == -1 || wn.type[dest] != REPAIR) {
                cout << "\nError: Invalid repair location.\n";
                break;
            }
            vector<int> dist, parent;
            dijkstra(wn, src, dist, parent);
            showRoute(wn, src, dest, dist, parent);
            showAllDistances(wn, src, dist);
            break;
        }
        case 6: {
            string s, r;
            displayLocations(wn);
            cout << "\nEnter new source location: ";
            getline(cin, s);
            int src = findLocation(wn, s);
            if (src == -1) {
                cout << "\nError: Invalid source location.\n";
                break;
            }
            vector<int> dist, parent;
            dijkstra(wn, src, dist, parent);
            showAllDistances(wn, src, dist);

            displayRepairLocations(wn);
            cout << "\nEnter repair location: ";
            getline(cin, r);
            int dest = findLocation(wn, r);
            if (dest == -1 || wn.type[dest] != REPAIR) {
                cout << "\nError: Invalid repair location.\n";
                break;
            }
            showRoute(wn, src, dest, dist, parent);
            break;
        }
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
