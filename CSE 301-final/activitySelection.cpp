#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
struct job{
    char jobID[10];
    int startTime;
    int finishTime;
    int compatibility;
}jobs[100];

int numOfJob;
void readInput(){
 
  scanf("%d",&numOfJob);
  for(int i=0;i<numOfJob;i++){
    
    scanf("%s %d %d",jobs[i].jobID,&jobs[i].startTime,&jobs[i].finishTime);
    jobs[i].compatibility=1;
  }
   printf("Job details read successfully. ");
  
   for(int i=0;i<numOfJob;i++){
    
    printf("Job ID: %s \nStart time: %d \nFinish time:%d \nJob comaptibility:%d\n",jobs[i].jobID,jobs[i].startTime,jobs[i].finishTime,jobs[i].compatibility);
   }
}
void sort(struct job jobs[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (jobs[j].finishTime > jobs[j + 1].finishTime) {
                struct job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}


void recursive_act(int i){
    int m=i+1;  //m=later one
    //printf("m=%d i=%d\n",m,i);
    while(m<=numOfJob && jobs[m].startTime<jobs[i].finishTime){
        jobs[m].compatibility=0;
        m++;
    }
    if(m<=numOfJob){
        recursive_act(m);
        return ;
    }
}
int main(){
    freopen("activitySelection.txt", "r", stdin);
    readInput();
   
    
    sort(jobs,numOfJob);  //on basis of finish time
    
     printf("\n-----After Sorting----\n");
     readInput();
     

    recursive_act(0);
    printf("\ncompatible jobs: \n");
    for(int i=0;i<numOfJob;i++){
        if(jobs[i].compatibility==1){
            printf("Job ID: %s \nStart time: %d \nFinish time:%d \nJob comaptibility:%d\n",jobs[i].jobID,jobs[i].startTime,jobs[i].finishTime,jobs[i].compatibility);
        }
    }
}