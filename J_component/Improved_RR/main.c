#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

void file_write(char* str)
{
   FILE *fp;
   fp = fopen("../data.txt", "a");
   fprintf(fp, "\n%s",str);
   printf("Your message is appended in data.txt file.");
   fclose(fp);
}
struct Process {
 int p_id;
 int AT;
 int BT;
 int rem_BT;
 int CT;
 int TAT;
 int WT;
}buffer;
void SeT(struct Process Ready[], int n){
 buffer.p_id=-1;
 for(int i=0;i<n;i++){
 Ready[i].p_id=-1;
 Ready[i].AT=-1;
 Ready[i].BT=-1;
 Ready[i].rem_BT=-1;
 Ready[i].CT=-1;
 Ready[i].TAT=-1;
 Ready[i].WT=-1;
 }
}void display(struct Process Process_Array[], int n){
 for (int i=0; i<n;i++) {
 int Pno=i+1;
 printf("\n\nProcess %d\n",Pno);
 printf("p_id=%d\n",Process_Array[i].p_id);
 printf("AT=%d\n",Process_Array[i].AT);
 printf("BT=%d\n",Process_Array[i].BT);
 printf("CT=%d\n",Process_Array[i].CT);
 printf("TAT=%d\n",Process_Array[i].TAT);
 printf("WT=%d\n",Process_Array[i].WT);
 printf("Rem_BT=%d\n",Process_Array[i].rem_BT);
 char str[300]="";
 char Group[10]="IRR,";
 char PID[10];
 char AT[10];
 char BT[10];
 char CT[10];
 char TAT[10];
 char WT[10];

 sprintf(PID, "%d,", Process_Array[i].p_id);
 sprintf(AT, "%d,", Process_Array[i].AT);
 sprintf(BT, "%d,", Process_Array[i].BT);
 sprintf(CT, "%d,", Process_Array[i].CT);
 sprintf(TAT, "%d,", Process_Array[i].TAT);
 sprintf(WT, "%d", Process_Array[i].WT);
 strcat(str, Group);
 strcat(str, PID);
 strcat(str, AT);
 strcat(str, BT);
 strcat(str, CT);
 strcat(str, TAT);
 strcat(str, WT);
 file_write(str);
 }
}
//Input for every process
void getStats(struct Process Process_Array[], int n){
 printf("\nEnter the details of every process in increasing order of their arrival times.\n");
 for (int i=0; i<n;i++) {
 printf("Enter PID of Process %d = ",i+1);
 scanf("%d",&Process_Array[i].p_id);
 printf("Enter Arrival Time of Process %d = ",i+1);
 scanf("%d",&Process_Array[i].AT);
 printf("Enter Burst Time of Process %d = ",i+1);
 scanf("%d",&Process_Array[i].BT);
 Process_Array[i].rem_BT=Process_Array[i].BT;
 }
}
//queue into ready queue
void queue(struct Process Ready[], struct Process Process_Array){
 int i=0;
 while(Ready[i].p_id!=-1){
 i++;
 } Ready[i]=Process_Array;
}
//Dequeue from ready queue
struct Process dequeue(struct Process Ready[]){
 struct Process temp=Ready[0];
 int i=0;
 while(Ready[i].p_id!=-1){
 i++;
 }
 int j=0;
 for (j; j<i+1;j++){
 Ready[j]=Ready[j+1];
 }
 return temp;
}
//No of elements in ready queue
int Ready_No(struct Process Ready[]){
 int i=0;
 while(Ready[i].p_id!=-1){
 i++;
 }
 return i;
}
void calcCT(struct Process Process_Array[], struct Process Ready[], int min_Time_Quantum, int max_Time_Quantum, int n) {
  int timeline = 0;
  int Time_Quantum=0;
  int counter = 0;
  int Process_counter = 0;
  while (counter != n) {
    for (int i = Process_counter; i < n; i++) {
      if (Process_Array[i].AT <= timeline) {
        queue(Ready, Process_Array[i]);
        Process_counter++;
      }
    }
    int ReadyQueueCheck = Ready_No(Ready);
    if (ReadyQueueCheck == 0) {
      timeline++;
    }
    else {
      Time_Quantum=DTQ(Ready, Ready_No(Ready),min_Time_Quantum,max_Time_Quantum );
      struct Process temp = dequeue(Ready);
      if (temp.rem_BT <= Time_Quantum) {
        for (int i = 0; i < n; i++) {
          if (Process_Array[i].p_id == temp.p_id) {
             printf("%d,%d ",timeline,Process_Array[i].p_id);
            timeline = timeline + Process_Array[i].rem_BT;
            Process_Array[i].rem_BT = 0;
            Process_Array[i].CT = timeline;
            counter++;
          }
        }
      } else {
        for (int i = 0; i < n; i++) {
          if (Process_Array[i].p_id == temp.p_id) {
             printf("%d ",Process_Array[i].p_id);
            timeline = timeline + Time_Quantum;
            for (int i = Process_counter; i < n; i++) {
              if (Process_Array[i].AT <= timeline) {
                queue(Ready, Process_Array[i]);
                Process_counter++;
              }
            }
            Process_Array[i].rem_BT = Process_Array[i].rem_BT - Time_Quantum;
            if (Process_Array[i].rem_BT < (Time_Quantum/2)){
                 printf("*%d ",Process_Array[i].p_id);
                timeline=timeline+Process_Array[i].rem_BT;
                Process_Array[i].rem_BT=0;
                Process_Array[i].CT = timeline;
                counter++;
            }
            else{
                queue(Ready, Process_Array[i]);
            }
          }
        }
      }
    }
  }
}
int DTQ(struct Process Ready[], int  nready, int minTQ, int maxTQ){
    int sum=0;
    int dtq=0;
    for (int i=0; i<nready; i++){
        sum=sum+Ready[i].rem_BT;
    }
    dtq=sum/nready;
    dtq=dtq/2;
    if(dtq<minTQ){
        dtq=minTQ;
    }
    if(dtq>maxTQ){
        dtq=maxTQ;
    }
    return (dtq);
}

void calcTAT(struct Process Process_Array[],int n){
 for (int i=0; i<n;i++) {
 Process_Array[i].TAT = Process_Array[i].CT - Process_Array[i].AT;
 }
}
void calcWT(struct Process Process_Array[],int n){
 for (int i=0; i<n;i++) {
 Process_Array[i].WT = Process_Array[i].TAT - Process_Array[i].BT;
 }
}
void calcAvgTAT(struct Process Process_Array[],int n){
 float sumTAT=0;
 for (int i=0; i<n;i++) {
 sumTAT = sumTAT + Process_Array[i].TAT;
 }
 printf("\n\nAverage Turnaround time= %.3f", (sumTAT/n));
}
void calcAvgWT(struct Process Process_Array[],int n){
 float sumWT=0;
 for (int i=0; i<n;i++) {
 sumWT = sumWT + Process_Array[i].WT;
 }
 printf("\n\nAverage Waiting time= %.3f", (sumWT/n));
}int main(){
 int n, min_Time_Quantum, max_Time_Quantum;
 printf("\nEnter Number of Processes in the system: ");
 scanf ("%d",&n);
 printf("Enter min Time Quantum: ");
 scanf("%d",&min_Time_Quantum);
 printf("Enter max Time Quantum: ");
 scanf("%d",&max_Time_Quantum);
 struct Process Process_Array[100];
 struct Process Ready[100];
 SeT(Ready, 100);
 struct Process temp=dequeue(Ready);
 getStats(Process_Array, n);
 calcCT(Process_Array,Ready, min_Time_Quantum, max_Time_Quantum, n);
 calcTAT(Process_Array, n);
 calcWT(Process_Array, n);
 display(Process_Array, n);
 calcAvgTAT(Process_Array, n);
 calcAvgWT(Process_Array, n);
 return 0;
}
