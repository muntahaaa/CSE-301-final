#include<bits/stdc++.h>
using namespace std;
void print_sol(vector<int>&prev, vector<int>&num, int i)
{
    if(prev[i]!=-1)
        print_sol(prev,num, prev[i]);
    cout<<num[i]<<" ";
}
int main(){
    int n,l;
    cout<<"how many inputs? ";
    cin>>l;
    n=l+1;
    vector<int>input(n),len(n, 1),prev(n,-1);
    input[0]=0;
    for(int i=1;i<n;i++){
        cout<<"enter value: ";
        cin>>input[i];
    }
    //len[0]=0;
    prev[0]=-1;
    int maxLen=0,maxIndex=0;
    for(int i=1;i<n;i++){
        //len[i]=0;
        for(int j=0;j<i-1;j++){
            if((input[j]<input[i]) && (len[j]+1>len[i])){
                len[i]=len[j]+1;
                prev[i]=j;

            }
           
        }

         if(len[i]>maxLen){
                maxLen=len[i];
                maxIndex=i;
            }
    }
    cout<<"max Length: "<<maxLen<<endl;
     print_sol(prev, input, maxIndex);
    return 0;
}