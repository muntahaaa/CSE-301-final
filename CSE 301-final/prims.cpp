#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <climits>
using namespace std;

#define Max 20

int numVertices, numEdges;
int graph[Max][Max] = {0};

map<string, int> names;
int previous[Max];
int key[Max];
bool inMST[Max];

void printGraph() {
    for (int i = 1; i <= names.size(); i++) {
        for (int j = 1; j <= names.size(); j++) {
            cout << graph[i][j] << "  ";
        }
        cout << endl;
    }
}

void getInput() {
    fstream myfile("kruskalLab.txt");
    if (!myfile.is_open()) {
        cerr << "Failed to open the file" << endl;
        exit(1);
    }

    myfile >> numVertices >> numEdges;
    string s;
    int w, x, y, z, i = 0;

    while (myfile >> s) {
        if (s == "END")
            break;
        if (names[s] == 0) {
            names[s] = ++i;
        }
        x = names[s];
        myfile >> s;
        if (names[s] == 0) {
            names[s] = ++i;
        }
        y = names[s];
        myfile >> w;
        graph[x][y] = w;
        graph[y][x] = w;
    }

    cout << "file is closing " << endl;
    myfile.close();
}

void relax(int u, int v) {
    if (key[v] > graph[u][v] && graph[u][v] != 0) {
        key[v] = graph[u][v];
        previous[v] = u;
    }
}

void MST() {
    for (auto u : names) {
        key[u.second] = INT_MAX;
        previous[u.second] = -1;
        inMST[u.second] = false;
    }

    key[names.begin()->second] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({key[names.begin()->second], names.begin()->second});

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (inMST[u]) {
            continue; // Skip if u is already in MST
        }

        inMST[u] = true;

        for (int v = 1; v <= names.size(); v++) {
            if (graph[u][v] && !inMST[v]) {
                relax(u, v);
                q.push({key[v], v});
            }
        }
    }
}


void printingMST(){
    for(auto u:names){
        cout<<u.first<<"-- ";
        for(auto v: names){
            if(previous[names[u.first]]==v.second){
                cout<<v.first<<"  --->";
            }
        }
        cout<<key[names[u.first]]<<endl;
    }
}


int savings(){
    int totalWeight=0,usedWeight=0;
    for(int i=1;i<=names.size();i++){
        for(int j=1;j<=names.size();j++){
            totalWeight+=graph[i][j];
        }
    }
    for(auto u:names){
        usedWeight += key[u.second];
    }
    //cout<<"Total"<<totalWeight<<" Used "<<usedWeight;
    return (totalWeight/2) - usedWeight;
}
int main() {
    getInput();
    printGraph();

    for (auto u : names) {
        cout << u.first << "  " << u.second << endl;
    }

    MST();

    for (int i = 1; i <= names.size(); i++) {
        cout << "Vertex: " << i << " Key: " << key[i] << " Previous: " << previous[i] << endl;
    }
    cout<<endl<<endl;
    printingMST();
    cout<<endl<<endl<<endl<<endl;
    cout<<"Savings :"<<savings()<<endl;

    return 0;
}
