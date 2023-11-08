#include<bits/stdc++.h>

using namespace std;

int numVertices, numEdges;
vector<string> vertices;
set<pair<int, pair<string,string>>> edges;
set<pair<int, pair<string,string>>> A;
vector<set<string>> sets;
 int totalWeight=0;
void getInput() {
    freopen("kruskalLab.txt", "r", stdin);
    cin >> numVertices >> numEdges;
    vertices.clear();  // Clear the vertices set

    for (int i = 0; i < numEdges; i++) {
       
        string u, v;
        int w;
        cin >> u >> v >> w;
        totalWeight+=w;
        // Add unique vertices to the 'vertices' set
        if (find(vertices.begin(), vertices.end(), u) == vertices.end()) {
        vertices.push_back(u);
    }
    if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
        vertices.push_back(v);
    }

        edges.insert({w, {u, v}});
    }
}

int findSet(string u)
{
    int count=0;
    for(auto i: sets)
    {
        auto a= i.find(u);
        if(a != i.end())
        {
            break;
        }
        count++;
    }
    return count;
}

void Union(string u, string v)
{
    set<string> temp;
    int index_u = findSet(u);
    int index_v = findSet(v);
   
    for(auto a: sets[index_v])
    {
        sets[index_u].insert(a);
    }

    sets.erase(sets.begin()+ index_v);
}

void MST()
{
    for(int i=0; i<numVertices; i++)
    {
        set<string> temp;
        temp.insert(vertices[i]);
        sets.push_back(temp);
    }

    for(auto i: edges)
    {
        string u, v;
        u= i.second.first;
        v= i.second.second;
       if(findSet(u) != findSet(v))
       {
        A.insert(i);
        Union(u,v);
       }
    }
}

int main()
{
    getInput();
    MST();
    int total=0;
    for(auto i: A)
    {
        cout << i.second.first << ", ";
        cout << i.second.second << " -> ";
        cout<< i.first << endl;
        total+=i.first;
    }
    cout<<endl;
   cout<<"you can save "<<totalWeight-total<<" rupees"; 
}