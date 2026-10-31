#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <limits>
#include <algorithm>
#include <sstream>
using namespace std;

const int INF = numeric_limits<int>::max();

// Vertex types
const int DEPOT    = 1;
const int JUNCTION = 2;
const int REPAIR   = 3;

struct WaterNetwork {
    int n;                                        // number of locations
    vector<string> names;                         // index -> location name
    vector<int> type;                             // index -> DEPOT / JUNCTION / REPAIR
    map<string, int> idOf;                        // location name -> index
    vector<vector<pair<int, int>>> adj;           // adj[u] = {(v, weight), ...}
    vector<int> dist;                             // shortest distances of last run
    vector<int> parent;                           // previous location on shortest path
};

string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s)
        if (!isdigit((unsigned char)c)) return false;
    return true;
}

string typeName(int t) {
    if (t == DEPOT) return "Water Depot";
    if (t == JUNCTION) return "Road Junction";
    return "Repair Location";
}

void initNetwork(WaterNetwork& wn) {
    wn.n = 0;
}

int addLocation(WaterNetwork& wn, const string& rawName, int t) {
    string name = trim(rawName);
    string key = toLower(name);
    if (wn.idOf.count(key)) return wn.idOf[key];
    wn.idOf[key] = wn.n;
    wn.names.push_back(name);
    wn.type.push_back(t);
    wn.adj.push_back({});
    return wn.n++;
}

// Finds a location by: serial number (1,2,3..), full name, or a unique part of the name
int findLocation(WaterNetwork& wn, const string& rawName) {
    string text = trim(rawName);
    if (text.empty()) return -1;

    if (isNumber(text)) {                         // e.g. "2" -> 2nd location
        int num = stoi(text);
        return (num >= 1 && num <= wn.n) ? num - 1 : -1;
    }

    string key = toLower(text);
    if (wn.idOf.count(key)) return wn.idOf[key];  // exact name

    int found = -1, count = 0;                    // partial name, e.g. "bus stand"
    for (int i = 0; i < wn.n; i++) {
        if (toLower(wn.names[i]).find(key) != string::npos) {
            found = i;
            count++;
        }
    }
    return (count == 1) ? found : -1;
}

bool roadExists(WaterNetwork& wn, int u, int v) {
    for (auto& e : wn.adj[u])
        if (e.first == v) return true;
    return false;
}

void addRoad(WaterNetwork& wn, int u, int v, int w) {
    wn.adj[u].push_back({v, w});
    wn.adj[v].push_back({u, w});                  // two-way road
}

string locationName(WaterNetwork& wn, int i) {
    return wn.names[i];
}

// Modification C: update the weight of an existing road
bool updateRoad(WaterNetwork& wn, int u, int v, int w, int& oldW) {
    if (u == -1 || v == -1 || u == v) return false;
    bool found = false;
    for (auto& e : wn.adj[u])
        if (e.first == v) { oldW = e.second; e.second = w; found = true; }
    for (auto& e : wn.adj[v])
        if (e.first == u) e.second = w;
    return found;
}

void displayLocations(WaterNetwork& wn) {
    cout << "\nLocations:\n";
    for (int i = 0; i < wn.n; i++)
        cout << "  " << i + 1 << ". " << wn.names[i] << "  (" << typeName(wn.type[i]) << ")\n";
}

void displayNetwork(WaterNetwork& wn) {
    cout << "\nWater Supply Road Network (Location -> Neighbour [distance]):\n";
    for (int u = 0; u < wn.n; u++) {
        cout << "  " << wn.names[u] << " -> ";
        if (wn.adj[u].empty()) cout << "(no roads)";
        for (size_t i = 0; i < wn.adj[u].size(); i++) {
            cout << wn.names[wn.adj[u][i].first] << " [" << wn.adj[u][i].second << " km]";
            if (i + 1 < wn.adj[u].size()) cout << ", ";
        }
        cout << "\n";
    }
}

// Dijkstra's algorithm from the selected source location
void dijkstra(WaterNetwork& wn, int src) {
    int n = wn.n;
    wn.dist.assign(n, INF);
    wn.parent.assign(n, -1);
    vector<bool> visited(n, false);

    // min-heap: (distance, location)
    priority_queue<pair<int, int>,
