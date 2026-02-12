#include <iostream>
#include <iomanip>
#include <fstream>

#include "RR.h"
#include "fifo.h"
#include "sjf.h"

using namespace std;

// ======================= FIFO =======================
void fifo(void)
{
    int n, bt[20], wt[20], tat[20], avwt = 0, avtat = 0, i, j;
    int numberOfProcessus;
 
    cout << "Entrer le nombre des processus(maximum 20): ";
    cin >> n;

    ifstream inputFile;
    inputFile.open("data.txt");

    i = 0;
    while (!inputFile.eof())
    {
        inputFile >> bt[i];
        i++;
    }

    numberOfProcessus = i;

    wt[0] = 0;

    for (i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];
    }

    cout << "\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";

    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        avwt += wt[i];
        avtat += tat[i];

        cout << "\nP[" << i + 1 << "]"
             << "\t\t" << bt[i]
             << "\t\t" << wt[i]
             << "\t\t" << tat[i];
    }

    avwt /= i;
    avtat /= i;

    cout << "\n\nMoyenne de Temps d'Attente:" << avwt;
    cout << "\nMoyenne de Temps de Rotation:" << avtat;
}

// ======================= ROUND ROBIN =======================
void RR(void)
{
    int i, NOP, sum = 0, count = 0, y, quant;
    int wt = 0, tat = 0;
    int at[10], bt[10], temp[10];

    float avg_wt, avg_tat;

    cout << " Entrer le nombre des processus (maximum 10): ";
    cin >> NOP;

    y = NOP;

    for (i = 0; i < NOP; i++)
    {
        cout << "\n Enter le temps d arrive et d execution :";
        cout << " Temps d'arrive : ";
        cin >> at[i];

        cout << " \nTemps d'execution : ";
        cin >> bt[i];

        temp[i] = bt[i];
    }

    cout << "Entrer le Quantum pour le processus:";
    cin >> quant;

    cout << "\n Process  \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ";

    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0)
        {
            sum += temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] -= quant;
            sum += quant;
        }

        if (temp[i] == 0 && count == 1)
        {
            y--;

            cout << "\nProcess " << i + 1
                 << " \t\t" << bt[i]
                 << "\t\t\t\t" << sum - at[i]
                 << "\t\t\t" << sum - at[i] - bt[i];

            wt += sum - at[i] - bt[i];
            tat += sum - at[i];

            count = 0;
        }

        if (i == NOP - 1)
            i = 0;
        else if (at[i + 1] <= sum)
            i++;
        else
            i = 0;
    }

    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;

    printf("\n Moyenne de Temps d'Attente: \t%f", avg_wt);
    printf("\n Moyenne de Temps de Rotation: \t%f", avg_tat);
}

// ======================= SJF =======================
void sjf(void)
{
    int n, temp, tt = 0, min, d, i, j;
    int numberOfProcessus;

    cout << "Entrer le nombre des processus (maximum 10):" << endl;
    cin >> n;

    int a[n], b[n], e[n], tat[n], wt[n];

    float avtat = 0, avwt = 0, stat = 0, swt = 0;

    ifstream inputFile;
    inputFile.open("burst.txt");

    i = 0;
    while (!inputFile.eof())
    {
        inputFile >> b[i];
        i++;
    }

    ifstream halFile;
    halFile.open("arrival.txt");

    i = 0;
    while (!halFile.eof())
    {
        halFile >> a[i];
        i++;
    }

    numberOfProcessus = i;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (b[i] > b[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;

                temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }

    min = a[0];

    for (i = 0; i < n; i++)
    {
        if (min > a[i])
        {
            min = a[i];
            d = i;
        }
    }

    tt = min;
    e[d] = tt + b[d];
    tt = e[d];

    for (i = 0; i < n; i++)
    {
        if (a[i] != min)
        {
            e[i] = b[i] + tt;
            tt = e[i];
        }
    }

    for (i = 0; i < n; i++)
    {
        tat[i] = e[i] - a[i];
        stat += tat[i];

        wt[i] = tat[i] - b[i];
        swt += wt[i];
    }

    avtat = stat / n;
    avwt = swt / n;

    cout << "Process  Arrival time(s)  Burst time(s)  Waiting time(s)  Turnaround time(s)\n";

    for (i = 0; i < n; i++)
    {
        cout << "P" << i + 1
             << "              " << a[i]
             << "                " << b[i]
             << "                  " << wt[i]
             << "               " << tat[i] << endl;
    }

    cout << "Moyenne de Temps d'Attente:" << avwt
         << " Moyenne de temps de Rotation:" << avtat;
}

// ======================= MQ =======================
void mq(void)
{
    int p[20], bt[20], su[20], wt[20], tat[20];
    int i, k, n, temp[20];

    float wtavg, tatavg;

    cout << "Entrer le nombre des processus(maximum 10): ";
    cin >> n;

    for (i = 0; i < n; i++)
    {
        p[i] = i;

        ifstream ouvrir;
        ouvrir.open("process.txt");

        i = 0;
        while (!ouvrir.eof())
        {
            ouvrir >> p[i];
            i++;
        }

        ifstream inputFile;
        inputFile.open("burstMQ.txt");

        i = 0;
        while (!inputFile.eof())
        {
            inputFile >> bt[i];
            i++;
        }

        ifstream halFile;
        halFile.open("userProcess.txt");

        i = 0;
        while (!halFile.eof())
        {
            halFile >> su[i];
            i++;
        }

        temp[i] = bt[i];
    }

    for (i = 0; i < n; i++)
        for (k = i + 1; k < n; k++)
            if (su[i] > su[k])
            {
                temp[i] = p[i];
                p[i] = p[k];
                p[k] = temp[i];

                temp[i] = bt[i];
                bt[i] = bt[k];
                bt[k] = temp[i];

                temp[i] = su[i];
                su[i] = su[k];
                su[k] = temp[i];
            }

    wtavg = wt[0] = 0;
    tatavg = tat[0] = bt[0];

    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];

        wtavg += wt[i];
        tatavg += tat[i];
    }

    cout << "\nProcess\tSYS/USR Process\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time";

    for (i = 0; i < n; i++)
    {
        cout << "\nP[" << i << "]"
             << "\t\t\t" << su[i]
             << "\t\t\t" << bt[i]
             << "\t\t\t" << wt[i]
             << "\t\t\t" << tat[i];
    }

    cout << "\n\nMoyenne de Temps d'Attente:" << wtavg / n;
    cout << "\nMoyenne de Temps de Rotation:" << tatavg / n;
}

// ======================= PROPER MLQ =======================
void propermlq()
{
    int n, i;
    int bt[20];

    int rr_bt[20], sjf_bt[20], fcfs_bt[20];
    int rr_index[20], sjf_index[20], fcfs_index[20];

    int rr_n = 0, sjf_n = 0, fcfs_n = 0;

    float global_wt = 0;
    float global_tat = 0;
    int total_process = 0;

    cout << "Enter number of processes (max 20): ";
    cin >> n;

    ifstream burstFile("burstMQ.txt");
    if (!burstFile.is_open())
    {
        cout << "Error opening burstMQ.txt\n";
        return;
    }

    for (i = 0; i < n; i++)
        burstFile >> bt[i];

    for (i = 0; i < n; i++)
    {
        int q;
        cout << "Process P" << i + 1 << " choose queue:\n";
        cout << "1. Round Robin\n2. SJF\n3. FCFS\nChoice: ";
        cin >> q;

        if (q == 1)
        {
            rr_bt[rr_n] = bt[i];
            rr_index[rr_n] = i + 1;
            rr_n++;
        }
        else if (q == 2)
        {
            sjf_bt[sjf_n] = bt[i];
            sjf_index[sjf_n] = i + 1;
            sjf_n++;
        }
        else
        {
            fcfs_bt[fcfs_n] = bt[i];
            fcfs_index[fcfs_n] = i + 1;
            fcfs_n++;
        }
    }

    // ===== ROUND ROBIN QUEUE =====
    if (rr_n > 0)
    {
        int quantum;
        cout << "\nEnter Quantum for Round Robin: ";
        cin >> quantum;

        int temp[20], wt[20], tat[20];

        for (i = 0; i < rr_n; i++)
            temp[i] = rr_bt[i];

        int complete = 0, time = 0;

        while (complete < rr_n)
        {
            for (i = 0; i < rr_n; i++)
            {
                if (temp[i] > 0)
                {
                    if (temp[i] > quantum)
                    {
                        time += quantum;
                        temp[i] -= quantum;
                    }
                    else
                    {
                        time += temp[i];
                        wt[i] = time - rr_bt[i];
                        tat[i] = time;
                        temp[i] = 0;
                        complete++;
                    }
                }
            }
        }

        cout << "\n=== Round Robin Queue ===\n";
        cout << "PID\tBurst\tWaiting\tTurnaround\n";

        for (i = 0; i < rr_n; i++)
        {
            cout << "P" << rr_index[i]
                 << "\t" << rr_bt[i]
                 << "\t" << wt[i]
                 << "\t" << tat[i] << endl;

            global_wt += wt[i];
            global_tat += tat[i];
            total_process++;
        }
    }

    // ===== SJF QUEUE =====
    if (sjf_n > 0)
    {
        for (i = 0; i < sjf_n - 1; i++)
        {
            for (int j = i + 1; j < sjf_n; j++)
            {
                if (sjf_bt[j] < sjf_bt[i])
                {
                    swap(sjf_bt[i], sjf_bt[j]);
                    swap(sjf_index[i], sjf_index[j]);
                }
            }
        }

        int wt[20], tat[20];
        int time = 0;

        for (i = 0; i < sjf_n; i++)
        {
            wt[i] = time;
            time += sjf_bt[i];
            tat[i] = time;
        }

        cout << "\n=== SJF Queue ===\n";
        cout << "PID\tBurst\tWaiting\tTurnaround\n";

        for (i = 0; i < sjf_n; i++)
        {
            cout << "P" << sjf_index[i]
                 << "\t" << sjf_bt[i]
                 << "\t" << wt[i]
                 << "\t" << tat[i] << endl;

            global_wt += wt[i];
            global_tat += tat[i];
            total_process++;
        }
    }

    // ===== FCFS QUEUE =====
    if (fcfs_n > 0)
    {
        int wt[20], tat[20];
        int time = 0;

        for (i = 0; i < fcfs_n; i++)
        {
            wt[i] = time;
            time += fcfs_bt[i];
            tat[i] = time;
        }

        cout << "\n=== FCFS Queue ===\n";
        cout << "PID\tBurst\tWaiting\tTurnaround\n";

        for (i = 0; i < fcfs_n; i++)
        {
            cout << "P" << fcfs_index[i]
                 << "\t" << fcfs_bt[i]
                 << "\t" << wt[i]
                 << "\t" << tat[i] << endl;

            global_wt += wt[i];
            global_tat += tat[i];
            total_process++;
        }
    }

    // ===== GLOBAL AVERAGES =====
    if (total_process > 0)
    {
        cout << "\n=====================================\n";

        cout << "TOTAL Average Waiting Time: "
             << fixed << setprecision(2)
             << static_cast<double>(global_wt) / total_process << endl;

        cout << "TOTAL Average Turnaround Time: "
             << fixed << setprecision(2)
             << static_cast<double>(global_tat) / total_process << endl;
    }
}

// ======================= ADMIN MENU =======================
void admin()
{
    while (1)
    {
        cout << "\n\t\t\t==============================\n";
        cout << "\n\t\t\t          BIENVENUE   \n";
        cout << "\n\t\t\t==============================\n\n";

        cout << "\n\t\t\t1. First In First Out";
        cout << "\n\t\t\t2. Multilevel Queue";
        cout << "\n\t\t\t3. Shortest Job First";
        cout << "\n\t\t\t4. Round Robin";
        cout << "\n\t\t\t5. Quitter";
        cout << "\n\t\t\t6. PROPERMLQ\n";

        cout << "\n\t\t\tEntrez votre choix !\n";

        int u;
        cin >> u;

        if (u == 1)
            fifo();
        else if (u == 2)
            mq();
        else if (u == 3)
            sjf();
        else if (u == 4)
            RR();
        else if (u == 6)
            propermlq();
        else if (u == 5)
            break;
        else
            cout << "Option invalide. Essayez encore une fois!\n";
    }
}

// ======================= MAIN =======================
int main()
{
    int ch;

    while (1)
    {
        cout << "\n\t\t\tBIENVENUE SUR LE SYSTEME D'ORDONNANCEMENT DES PROCESSUS";
        cout << "\n\t\t\t1. ACCEDER AU SYSTEME";
        cout << "\n\t\t\t2. QUITTER";
        cout << "\n\t\t\tEntrer Votre Choix: ";

        cin >> ch;

        switch (ch)
        {
            case 1:
                admin();
                break;
            case 2:
                exit(0);
                break;
            default:
                cout << "Entrer un choix valide!\n";
                break;
        }
    }

    return 0;
}
