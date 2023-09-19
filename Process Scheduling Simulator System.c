#include <stdio.h>
#include <stdlib.h>
#define max 30

void pline(int x)
{
    int i;
    for(i=0; i<x; i++)
    {
        printf("-");
    }
    printf("\n");
}


/* First Come First Serve */
struct PCB
{

    int pid,arrival,burst,turnaround;
};
void fcfs()
{

    int i, j, num;
    float avg = 0.0, sum=0.0;
    struct PCB p[max], temp;
    printf("\nWelcome to FCFS Algorithm\n");
    printf("Enter the total number of processes: ");
    scanf("%d",&num);
    for(i=0; i<num; i++)
    {
        printf("Enter the arrival time for process %d :", i+1);
        scanf("%d",&p[i].arrival);
        printf("Enter the burst time for process %d :", i+1);
        scanf("%d",&p[i].burst);
        p[i].pid= i+1;

    }
    for(i = 0; i<num; i++)
    {
        for(j=0; j<num-i-1; j++)
        {
            if(p[j].arrival > p[j+1].arrival)
            {
                temp = p[j];
                p[j]= p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(i = 0; i<num; i++)
    {
        sum = sum+ p[i].burst;
        p[i].turnaround = sum;
    }
    sum=0;
    pline(44);
    printf("PID\tArrival\tBurst\tTurn Around Time\n");
    pline(44);
    for(i=0; i<num; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival,p[i].burst,p[i].turnaround);
        sum+=p[i].turnaround;
    }

    pline(44);
    avg= sum/(float)num;
    printf("\nTotal Turnaround Time: %f",sum);
    printf("\nAverage Turn Around Time: %.2f",avg);


    /*printf("\nDo You Want to continue?\n1=Yes\n2=No\n");
    int con=0;
    scanf("%d",&p);
    if(con==1)
    {
        main();
    }
    else if(con==2)
    {
        printf("\n***THANK YOU***\n")
    }
    */

}



/* SJF */
struct PCB2
{
    int burst, pid, wait, turnaround;
};
void pline(int);
void sjf()
{
    struct PCB2 p[max],temp;
    int i,n,j=1,sum=0,w_total=0, t_total=0;
    float w_avg=0.0, t_avg=0.0;
    printf("Welcome to SJF Algorithm\n");
    printf("Enter the total number of processes:");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("Enter the burst time of process %d :",i+1);
        scanf("%d",&p[i].burst);
        p[i].pid=i+1;
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(p[j].burst >p[j+1].burst)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(i=0; i<n; i++)
    {
        p[i].wait=sum;
        sum=sum+p[i].burst;
        p[i].turnaround = sum;
    }
    pline(44);
    printf("PID\tBurst\tWait\tTurnaround\n");
    pline(44);
    for(i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p[i].pid,p[i].burst,p[i].wait,p[i].turnaround);
        w_total += p[i].wait;
        t_total += p[i].turnaround;
    }
    w_avg=w_total/(float)n;
    t_avg=t_total/(float)n;
    pline(44);
    printf("\nTotal Waiting Time: %d",w_total);
    printf("\nAverage Waiting Time: %.3f",w_avg);

    printf("\nTotal Turnaround Time: %d",t_total);
    printf("\nAverage Turnaround Time: %.3f",t_avg);
}

/*  Priority Scheduling */
void ps()
{
    int i, n, j, t, bt[max],wt[max], pr[max],tat[max],pos;   // bt= burst time, wt=waiting time, pr=priority,
    // tat=turnaround time, pos=position.
    float awt=0.0, atat=0.0;  // awt=average waiting time, atat=average turn around time.
    printf("\nWelcome to Priority Scheduling Algorithm\n");
    printf("Enter the number of process:");
    scanf("%d",&n);

    for(i=0; i<n; i++)
    {
        printf("Enter the burst time of the process[%d]:",i+1);
        scanf("%d",&bt[i]);
        printf("Enter the priority of the process[%d]:",i+1);
        scanf("%d",&pr[i]);
    }

    for(i=0; i<n; i++)
    {
        pos=i;
        for(j=i+1; j<n; j++)
        {
            if(pr[j]<pr[pos])
            {
                pos = j;
            }
        }
        t=pr[i];
        pr[i]=pr[pos];
        pr[pos]=t;

        t=bt[i];
        bt[i]=bt[pos];
        bt[pos]=t;
    }

    pline(80);
    wt[0]=0;
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurn Arround Time\n");
    pline(80);
    for(i=0; i<n; i++)
    {
        wt[i]=0;
        tat[i]=0;
        for(j=0; j<i; j++)
        {
            wt[i]=wt[i]+bt[j];
        }
        tat[i]=wt[i]+bt[i];
        awt=awt+wt[i];
        atat=atat+tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",i+1,bt[i],pr[i],wt[i],tat[i]);
    }
    awt=awt/(float)n;
    atat=atat/(float)n;
    pline(80);
    printf("Average Waiting Time: %.2f\n",awt);
    printf("Average Turn Around Time:%.2f",atat);
}

/* Round Robin */
void rr()
{
    int n,i,qt,count=0,temp,sq=0,bt[max],wt[max],tat[max],rem_bt[max];  // qt=Quantum Time
    float awt=0.0,atat=0.0;
    printf("\nWelcome to Round Robin\n");
    printf("Enter the total number of process:");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("Enter burst time of process [%d]:",i+1);
        scanf("%d",&bt[i]);
        rem_bt[i]=bt[i];
    }
    printf("Enter quantum time:");
    scanf("%d",&qt);
    while(1)
    {
        for(i=0,count=0; i<n; i++)
        {
            temp=qt;
            if(rem_bt[i]==0)
            {
                count++;
                continue;
            }
            if(rem_bt[i]>qt)
                rem_bt[i]=rem_bt[i]-qt;

            else if(rem_bt[i]>=0)
            {
                temp=rem_bt[i];
                rem_bt[i]=0;
            }
            sq=sq+temp;
            tat[i]=sq;
        }
        if(n==count)
            break;
    }
    pline(65);
    printf("Process\tBurst Time\tTurn Around Time\tWaiting Time\n");
    pline(65);
    for(i=0; i<n; i++)
    {
        wt[i]=tat[i]-bt[i];
        awt=awt+wt[i];
        atat=atat+tat[i];
        printf("\n%d\t%d\t\t%d\t\t%d",i+1,bt[i],tat[i],wt[i]);
    }
    awt=(float)awt/n;
    atat=(float)atat/n;
    printf("\n");
    pline(65);
    printf("Average Waiting Time: %.2f\n",awt);
    printf("Average Turn Around Time:%.2f",atat);
    pline(65);

}




int start()
{
    int choose;

    pline(60);
    printf("\tWELCOME TO PROCESS SCHEDULING SIMULATOR SYSTEM \t\n");
    pline(60);
    printf("Choose Your Algorithm->\n1.FCFS\n2.SJF\n3.PRIORITY SCHEDULING\n4.ROUND ROBIN\n\n*Press 0 to Quit*\n");

    scanf("%d",&choose);
    if(choose==1)
    {
        fcfs();
    }
    else if(choose==2)
    {
        sjf();
    }
    else if(choose==3)
    {
        ps();
    }
    else if(choose==4)
    {
        rr();
    }
    else if(choose==0)
    {
        printf("\n\n***THANK YOU***\n\n");
        return 0;
    }
    else
    {
        printf("\n*Wrong Command*\n");
        start();
    }
    return 0;
}

int main()
{
    start();
}

