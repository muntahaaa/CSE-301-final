#include<bits/stdc++.h>
using namespace std;
#define mx 100

map <string,int> cityNames;
int shortDist[mx];
int graph[mx][mx]={0};
int predecessor[mx];

void readInitializePair(){
    string city;
    int weight,source,dest,i=0;
    freopen("dijkstraInput.txt", "r", stdin);

    while(cin>>city){
        if(city=="END") break;

        if(cityNames[city]==0) 
        {
            cityNames[city]=++i;
        }
        source=cityNames[city];
         
         cin>>city;
          if(cityNames[city]==0) 
        {
            cityNames[city]=++i;
        }
        dest=cityNames[city];

        cin>>weight;
        graph[source][dest]=weight;

    }
}

void initializeSource(string src){
    for(int i=0;i<cityNames.size();i++){
        shortDist[i]=INT_MAX;
        predecessor[i]=-1;

    }
    shortDist[cityNames[src]]=0;
}

void relax(int src, int dest){
    if(shortDist[dest]>shortDist[src]+graph[src][dest]){

        shortDist[dest]=shortDist[src]+graph[src][dest];
        predecessor[dest]=src;

    }
}

void dijkstra(string src){
    initializeSource(src);
    priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push({shortDist[cityNames[src]],cityNames[src]});

    while(!q.empty()){
        int city=q.top().second;
        q.pop();
        for(int i=0;i<cityNames.size();i++){
            if(graph[city][i])
            {
                relax(city,i);
                q.push({shortDist[i],i});
            }
        }
    }
}

void printGraph()
{
    for(int i=1; i<=cityNames.size(); i++)
    {
        for(int j=1; j<=cityNames.size(); j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printPath(int i){
     
    if(i==-1) return;
    printPath(predecessor[i]);
   
    for(auto x: cityNames){
        if(x.second==i){
           cout<<x.first<<" ";
           //cout<<x.second<<" ";
           
           break;
        }
        cout<<"->";
    }
}

int main(){
    string dest,src;
    readInitializePair();
    printGraph();
    cin>>src;
    dijkstra(src);
    cin>>dest;
    cout<<"Path from "<<src<<" to "<<dest<<": ";
    printPath(cityNames[dest]);
    return 0;

}