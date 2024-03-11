#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm> // For reverse
#include <list>

using namespace std;

// Define Node class
class Node
{
public:
    string name;
    int heuristic;
    vector<pair<Node *, int>> adjacencies;

    Node(string n, int h) : name(n), heuristic(h) {}
};

// Define Edge class
class Edge
{
public:
    Node *target;
    int weight;

    Edge(Node *targetNode, int w) : target(targetNode), weight(w) {}
};

vector<string> AStarAlgo(Node *start, Node *goal, map<Node*, int>& distances)
{
    // min priority queue
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> pq;

    map<Node *, int> visited;

    map<Node *, Node *> parent;

    // start node to queue
    pq.push(make_pair(start->heuristic, start));
    distances[start] = 0;

    while (!pq.empty())
    {
        Node *currentNode = pq.top().second;
        int currentCost = pq.top().first;
        pq.pop();

        // target reach
        if (currentNode == goal)
        {
            vector<string> path;
            int distance = distances[currentNode];
            while (currentNode != start)
            {
                path.push_back(currentNode->name);
                currentNode = parent[currentNode];
            }
            path.push_back(start->name);
            reverse(path.begin(), path.end());
            cout << "Distance from starting point to destination: " << distance << endl;

            return path;
        }

        visited[currentNode] = currentCost;

        // Explore all neighboring nodes
        for (const auto &edge : currentNode->adjacencies)
        {
            Node *neighborNode = edge.first;
            int neighborCost = edge.second;

            int edgeWeight = edge.second;
            int newDistance = distances[currentNode] + edgeWeight;

            int estimatedCostToGoal = neighborNode->heuristic;
            int totalCost = currentCost + neighborCost + estimatedCostToGoal;

            // Add the neighbor node to the pq if it's not visited
            if (visited.find(neighborNode) == visited.end() || totalCost < visited[neighborNode])
            {
                pq.push(make_pair(totalCost, neighborNode));
                parent[neighborNode] = currentNode;
                distances[neighborNode] = newDistance;
            }
        }
    }

    cout << "Not reachable" << endl;
    return vector<string>();
}

int main()
{
    // Initialize the graph based on the provided map
    Node *n1 = new Node("Arad", 366);
    Node *n2 = new Node("Zerind", 374);
    Node *n3 = new Node("Oradea", 380);
    Node *n4 = new Node("Sibiu", 253);
    Node *n5 = new Node("Timisoara", 329);
    Node *n6 = new Node("Lugoj", 244);
    Node *n7 = new Node("Mehadia", 241);
    Node *n8 = new Node("Craiova", 160);
    Node *n9 = new Node("Drobeta", 242);
    Node *n10 = new Node("Eforie", 161);
    Node *n11 = new Node("Fagaras", 178);
    Node *n12 = new Node("Giurgiu", 77);
    Node *n13 = new Node("Bucharest", 0);
    Node *n14 = new Node("Hirsova", 151);
    Node *n15 = new Node("Iasi", 226);
    Node *n16 = new Node("Neamt", 234);
    Node *n17 = new Node("Pitesti", 98);
    Node *n18 = new Node("Rimnicu Vilcea", 193);
    Node *n19 = new Node("Vaslui", 199);
    Node *n20 = new Node("Urziceni", 80);

    // Initialize the edges
    n1->adjacencies = {{n2, 75}, {n4, 140}, {n5, 118}};
    n2->adjacencies = {{n1, 75}, {n3, 71}};
    n3->adjacencies = {{n2, 71}, {n4, 151}};
    n4->adjacencies = {{n1, 140}, {n11, 99}, {n3, 151}, {n18, 80}};
    n5->adjacencies = {{n1, 118}, {n6, 111}};
    n6->adjacencies = {{n5, 111}, {n7, 70}};
    n7->adjacencies = {{n6, 70}, {n9, 75}};
    n8->adjacencies = {{n9, 120}, {n18, 146}, {n17, 138}};
    n9->adjacencies = {{n7, 75}, {n8, 120}};
    n10->adjacencies = {{n14, 86}};
    n11->adjacencies = {{n4, 99}, {n13, 211}};
    n12->adjacencies = {{n13, 90}};
    n13->adjacencies = {{n12, 90}, {n17, 101}, {n20, 85}};
    n14->adjacencies = {{n10, 86}, {n20, 98}};
    n15->adjacencies = {{n16, 87}, {n19, 92}};
    n16->adjacencies = {{n15, 87}};
    n17->adjacencies = {{n18, 97}, {n13, 101}, {n8, 138}};
    n18->adjacencies = {{n4, 80}, {n17, 97}, {n8, 146}};
    n19->adjacencies = {{n15, 92}, {n20, 152}};
    n20->adjacencies = {{n19, 142}, {n14, 98}, {n13, 85}};

    map<Node*, int> distances;
    
    cout << "Using A* algorithm - "<< endl;
    vector<string> path = AStarAlgo(n1, n13, distances);

    // Print the path
    cout << "Path: ";
    for (const auto &city : path)
    {
        cout << city << " -> ";
    }
    cout << endl;

    return 0;
}
