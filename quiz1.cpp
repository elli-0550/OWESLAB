#include<iostream>
#include<fstream>
#include "RR.h"
#include "fifo.h"
#include "sjf.h"

using namespace std;
void fifo(void)
{
    int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    int numberOfProcessus;
    cout<<"Entrer le nombre des processus(maximum 20):"; //Enter the number of processes (maximum 20):
    cin>>n;


    ifstream inputFile ;
    inputFile.open("data.txt");
    i = 0;
    while(!inputFile.eof())
    {
       inputFile >> bt[i];
        i++;
    }
    numberOfProcessus = i;


    wt[0]=0;    //temps d'attente du premier processus est 0 () //The waiting time for the first process is 0 ()

    //calcul du temps d'attente //calculation of waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }

    cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";

    //calculating turnaround time
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avwt+=wt[i];
        avtat+=tat[i];
        cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i];
    }

    avwt/=i;
    avtat/=i;
    cout<<"\n\nMoyenne de Temps d'Attente:"<<avwt; //Average Waiting Time
    cout<<"\nMoyenne de Temps de Rotation:"<<avtat; //Average Rotation Time:

}
void RR(void)
{
    // initialisation des variables //initialization of variables
    int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
   cout<<" Entrer le nombre des processus (maximum 10): "; //Enter the number of processes (maximum 10)
   cin>>NOP;
    y = NOP; // Assigner le nombre du processus a la variable y //Assign the process number to the variable y


for(i=0; i<NOP; i++)
{
cout<<"\n Enter le temps d arrive et d execution :" ; //Enter the arrival and execution time
cout<<" Temps d'arrive : ";  // Arrival time
cin>>at[i];
cout<<" \nTemps d'execution : "; // execution time
cin >>bt[i];
temp[i] = bt[i]; // record execution time in the array
}
// Quantum
cout<<"Entrer le Quantum pour le processus:"; //Enter the quantum for the process
cin>>quant;
// Display: the process number, burst time, turn-around time, and waiting time
cout<<"\n Process  \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ";
for(sum=0, i = 0; y!=0; )
{
if(temp[i] <= quant && temp[i] > 0) // Define the conditions
{
    sum = sum + temp[i];
    temp[i] = 0;
    count=1;
    }
    else if(temp[i] > 0)
    {
        temp[i] = temp[i] - quant;
        sum = sum + quant;
    }
    if(temp[i]==0 && count==1)
    {
        y--; //Decrement the process number
        cout<<"\nProcess "<<i+1<<" \t\t" << bt[i]<<"\t\t\t\t" << sum-at[i]<<"\t\t\t"<< sum-at[i]-bt[i];
        wt = wt+sum-at[i]-bt[i];
        tat = tat+sum-at[i];
        count =0;
    }
    if(i==NOP-1)
    {
        i=0;
    }
    else if(at[i+1]<=sum)
    {
        i++;
    }
    else
    {
        i=0;
    }
}
//Average Waiting Time and Average Turnaround Time
avg_wt = wt * 1.0/NOP;
avg_tat = tat * 1.0/NOP;
printf("\n Moyenne de Temps d'Attente: \t%f", avg_wt); //Average Waiting Time:
printf("\n Moyenne de Temps de Rotation: \t%f", avg_tat); //Average Rotation Time

}
void sjf(void)
{
// initlialiser les variables //Initialize the variables
      int n,temp,tt=0,min,d,i,j, a[n],b[n],e[n],tat[n],wt[n];
      int numberOfProcessus;
      float avtat=0,avwt=0,stat=0,swt=0;

      cout<<"Entrer le nombre des processus (maximum 10):"<<endl; //Enter the number of processes (maximum 10)
      cin>>n;

// lecture des details comme le temps d'arrive et temps d'execution //Read the details such as arrival time and execution time

      ifstream inputFile ;
    inputFile.open("burst.txt");
    i = 0;
    while(!inputFile.eof())
    {
       inputFile >> b[i];
        i++;
    }
    ifstream halFile ;
    halFile.open("arrival.txt");
    i = 0;
    while(!halFile.eof())
    {
       halFile >> a[i];
        i++;
    }
    numberOfProcessus = i;// assigner le nombre de processus a la variable i //Assign the number of processes to the variable i




      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(b[i]>b[j])
                {
                      temp=a[i];
                      a[i]=a[j];
                      a[j]=temp;

                      temp=b[i];
                      b[i]=b[j];
                      b[j]=temp;
                }
          }
      }
      min=a[0];
      for(i=0;i<n;i++)
      {
            if(min>a[i])
            {
                  min=a[i];
                  d=i;
            }
      }
      tt=min;
      e[d]=tt+b[d];
      tt=e[d];

      for(i=0;i<n;i++)
      {
            if(a[i]!=min)
            {
                  e[i]=b[i]+tt;
                  tt=e[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i]=e[i]-a[i];
            stat=stat+tat[i];
            wt[i]=tat[i]-b[i];
            swt=swt+wt[i];
      }
      avtat=stat/n;
      avwt=swt/n;
      cout<<"Process  Arrival time(s)  Burst time(s)  Waiting time(s)  Turnaround time(s)\n";

    for(i=0;i<n;i++)
    {
    cout<<"P"<<i+1<<"              "<<a[i]<<"                "<<b[i]<<"                  "<<wt[i]<<"               "<<tat[i]<<endl;
    }

    cout<<"Moyenne de Temps d'Attente:"<<avwt<<" Moyenne de temps de Rotation:"<<avtat;  //Average Waiting Time and Average Turnover Time
}

void mq(void)
{
    // initlialiser les variables

int p[20],bt[20], su[20], wt[20],tat[20],i, k, n, temp[20];
float wtavg, tatavg;
cout<<"Entrer le nombre des processus(maximum 10):";
cin>>n;
//lire les details des processus
for(i=0; i<n; i++)
{
   p[i]=i;
  ifstream ouvrir;
   ouvrir.open("process.txt");
    i = 0;
    while(!ouvrir.eof())
    {
       ouvrir >> p[i] ;
        i++;
    }


 ifstream inputFile ;
    inputFile.open("burstMQ.txt");
    i = 0;
    while(!inputFile.eof())
    {
       inputFile >> bt[i];
        i++;
    }
    ifstream halFile ;
    halFile.open("userProcess.txt");
    i = 0;
    while(!halFile.eof())
    {
      halFile >> su[i];
        i++;
    }
    temp[i] = bt[i];
    }
for(i=0;i<n;i++)
for(k=i+1;k<n;k++)
if(su[i] > su[k])// definir les conditions
{
temp[i]=p[i];
p[i]=p[k];
p[k]=temp[i];
temp[i]=bt[i];
bt[i]=bt[k];
bt[k]=temp[i];
temp[i]=su[i];
su[i]=su[k];
su[k]=temp[i];
}
wtavg = wt[0] = 0;
tatavg = tat[0] = bt[0];
for(i=1;i<n;i++)
{
//  temps d'attente et temps de rotation
wt[i] = wt[i-1] + bt[i-1];
tat[i] = tat[i-1] + bt[i];
// Moyenne de Temps d'Attente et Moyenne de temps de Rotation
wtavg = wtavg + wt[i];
tatavg = tatavg + tat[i];
}
cout<<"\nProcess\tSYS/USR Process\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time";
for(i=0;i<n;i++)
cout<<"\nP["<<i<<"]"<<"\t\t\t"<<su[i]<<"\t\t\t"<<bt[i]<<"\t\t\t"<<wt[i]<<"\t\t\t"<<tat[i];
// Moyenne de Temps d'Attente et Moyenne de temps de Rotation
// give process
cout<<"\n\nMoyenne de Temps d'Attente:"<<wtavg/n;
cout<<"\nMoyenne de Temps de Rotation:"<<tatavg/n;


}

void propermlq()
{
    int n, i;
    int bt[20], type[20];
    int sys_bt[20], usr_bt[20];
    int sys_index[20], usr_index[20];
    int sys_n = 0, usr_n = 0;

    cout << "Enter the number of processes (maximum 20): ";
    cin >> n;

    ifstream burstFile("burstMQ.txt");
    ifstream typeFile("userProcess.txt");

    if(!burstFile.is_open() || !typeFile.is_open())
    {
        cout << "Error: file not found!\n";
        return;
    }

    for(i = 0; i < n; i++)
    {
        burstFile >> bt[i];
        typeFile >> type[i];

        if(type[i] == 0) // System Queue
        {
            sys_bt[sys_n] = bt[i];
            sys_index[sys_n] = i + 1;
            sys_n++;
        }
        else // User process
        {
            usr_bt[usr_n] = bt[i];
            usr_index[usr_n] = i + 1;
            usr_n++;
        }
    }

    int quantum;
    cout << "\nEnter the quantum for system processes: ";
    cin >> quantum;

    int temp[20], wt_sys[20], tat_sys[20];
    for(i = 0; i < sys_n; i++) temp[i] = sys_bt[i];

    int complete = 0, time = 0;
    float total_wt = 0;
    float total_tat = 0;

    while(complete < sys_n)
    {
        for(i = 0; i < sys_n; i++)
        {
            if(temp[i] > 0)
            {
                if(temp[i] > quantum)
                {
                    time += quantum;
                    temp[i] -= quantum;
                }
                else
                {
                    time += temp[i];

                    wt_sys[i] = time - sys_bt[i];
                    tat_sys[i] = time;

                    total_wt += wt_sys[i];
                    total_tat += tat_sys[i];

                    temp[i] = 0;
                    complete++;
                }
            }
        }
    }


    cout << "\n System Queue Scheduling (Round Robin)";
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for(i = 0; i < sys_n; i++)
    
        cout << "P" << sys_index[i]<< "\t" << sys_bt[i]<< "\t\t" << wt_sys[i]<< "\t\t" << tat_sys[i] << "\n";
    int wt_usr[20], tat_usr[20];

    if(usr_n > 0)
    {
        wt_usr[0] = 0;
        tat_usr[0] = usr_bt[0];

        total_wt += wt_usr[0];
        total_tat += tat_usr[0];

        for(i = 1; i < usr_n; i++)
        {
            wt_usr[i] = wt_usr[i-1] + usr_bt[i-1];
            tat_usr[i] = wt_usr[i] + usr_bt[i];

            total_wt += wt_usr[i];
            total_tat += tat_usr[i];
        }

        cout << "\n User Queue Scheduling (FCFS)";
        cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";

        for(i = 0; i < usr_n; i++)
        
            cout << "P" << usr_index[i]<< "\t" << usr_bt[i]<< "\t\t" << wt_usr[i]<< "\t\t" << tat_usr[i] << "\n";
    
    }
    int total_processes = sys_n + usr_n;

    cout << "\n Overall MLQ Scheduling Result";
    cout << "Average Waiting Time: "
         << total_wt / total_processes;
    cout << "\nAverage Turnaround Time: "
         << total_tat / total_processes << "\n";
}

void admin()
{
  while(1)
  {
 	cout<<"\n\t\t\t==============================\n";
	cout<<"\n\t\t\t          BIENVENUE   \n";
	cout<<"\n\t\t\t==============================\n\n";
	cout<<"\n\t\t\t* * * * * * * * * * * * * * * *\n";
 	cout<<"\n\t\t\t1. First In First Out  \n\n\t\t\t2. Multilevel Queue\n\n\t\t\t3. Shortest Job First\n\n\t\t\t4. Round Robin \n\n\t\t\t5. Quitter \n \n\n\t\t\t6. PROPERMLQ \n";
  cout<<"\n\n\t\t\tEntrez votre choix !\n";
  int u;
  cin>>u;
if(u==1)
  {
  fifo();
}
  else if(u==2)
  {
  mq();
}
  else if(u==3)
  {
  sjf();
}
  else if(u==4)
  {
  RR();
}
  else if(u==6)
  {
    propermlq();
  }

  else if(u==5)
  {
  break;
}
  else cout<<"Option invalide. Essayez encore une fois!\n";
 }

}


int main(){

    int ch;

      while(1){
        cout<<"\n \t\t\t ";
        cout<<"\n \t\t\t";
        cout<<"\n \t\t\t";
        cout<<"\n \t\t\t* * * * * * * * * * * *  * * * * * * * * * * *  * ";
         cout<<"\n \t\t\tBIENVENUE SUR LE SYSTEME D'ORDONNANCEMENT DES PROCESSUS";
        cout<<"\n \t\t\t* * * * * * * * * * * *  * * * * * * * * * * *  * ";
        cout<<"\n\t\t\t  1. ACCEDER AU SYSTEME";
        cout<<"\n\t\t\t  2. QUITTER";
        cout<<"\n\t\t\t* * * * * * * * * * * *\n";
        cout<<"\n\t\t\t Entrer Votre Choix: ";
        cin>>ch;
        switch(ch){
            case 1:
                admin();
                break;
            case 2:
                exit(0);
                break;
            default:
                cout<<"Entrer un choix valide!\n";
                break;
        }
    }
    return 0;
}