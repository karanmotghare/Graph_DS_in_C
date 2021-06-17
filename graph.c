#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define max 20
#define intsize 4
typedef enum{false,true} bool;

typedef struct node_tag
{
    int node_num;
    int weight;
    struct node *next;
}node;

typedef struct adj_tag{
    node* list;
    int node_number;
}adj;

typedef struct graph_tag{
    adj array[max];
    int used; 
}graph;

node* makeNode(int data,int weight)
{
    node* nptr=(node*)malloc(sizeof(node));
    nptr->node_num=data;
    nptr->next=NULL;
    nptr->weight=weight;
    return nptr;
}
//-------------------------------------stack function------------------------------------------//
typedef struct stack_tag
{
    node *top;
}stack;

void initialise_stack(stack* sp)
{
    sp->top=NULL;
}

bool isStackEmpty(stack* sp)
{
    if(sp->top==NULL)
    {
        return true;
    }
    return false;
}

bool isin_stack(stack *sc,int num)
{
    node *ptr;
    bool retval=false;
    ptr=sc->top;
    while(ptr!=NULL)
    {
        if(ptr->node_num==num)
        {
            retval=true;
        }
        ptr=ptr->next;
    }
    return retval;
}

bool PushStack(stack* sp,int data)
{
    bool b = true;
    node *nptr;
    nptr=makeNode(data,0);
    if(nptr==NULL)
    {
        b=false;
    }
    else
    {
        nptr->next=sp->top;
        sp->top=nptr;
    }
    return b;
}

bool PopStack(stack* sp)
{
    node *ptr;
    bool b=true;
    if(sp->top==NULL)
    {
        b=false;
    }
    else
    {
        ptr=sp->top;
        sp->top=(sp->top)->next;
        free(ptr);
    }
    return b;
}

//--------------------------------------------Queue_funct--------------------------------------------------//
typedef struct queue_tag
{
    node* rear;
    node* front;
}queue;

void initialize_queue(queue *q)
{
    q->front=q->rear=NULL;
}

void insert_queue(queue *q,int data)
{
    node *nptr,*lptr;
    lptr=q->front;    
    nptr=makeNode(data,0);
    if(lptr==NULL)
    {
        q->front=nptr;
        q->rear=nptr;
    }
    else
    {
        node *ptr;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=nptr;
        q->rear=nptr;
    }
    
}

void delete_queue(queue *q)
{
    node *lptr;
    lptr=q->front;
    if(lptr!=NULL)
    {
        q->front=lptr->next;
        free(lptr);
    }
    if(q->front==NULL)
        q->rear=NULL;
}

bool is_queue_empty(queue *q)
{
    bool retval=false;
    if(q->front==NULL && q->rear==NULL)
    {
        retval=true;
    }
    return retval;
}

bool is_in_queue(queue* q,int data)
{
    bool retval=false;
    node *lptr;
    lptr=q->front;
    while (lptr!=NULL)
    {
        if(lptr->node_num==data)
        {
            retval=true;
        }
        lptr=lptr->next;
    }
    return retval;
}

//--------------------------------------------graphfunciton-----------------------------------------------//
int search_node_graph_index(graph *g,int node_number)
{
    for(int i=0;i<max;i++)
    {
        if(g->array[i].node_number==node_number)
        {
            return i;
        }
    }
}

// node* makeNode(int data,int weight)
// {
//     node* nptr=(node*)malloc(sizeof(node));
//     nptr->node_num=data;
//     nptr->next=NULL;
//     nptr->weight=weight;
//     return nptr;
// }

graph initilize_graph()
{
    graph g;
    g.used=0;
    for(int i=0;i<max;i++)
    {
        g.array[i].node_number=-1;
        g.array[i].list=NULL;
    }
    return g;
}

void addnode(graph *g,int node_no)
{
    g->array[g->used].node_number=node_no;
    (g->used)++;
}

void delete_node_list(node **lptr)
{
    node *ptr;
    ptr=*lptr;
    if(ptr!=NULL)
    {
        if(ptr->next==NULL)
        {
            free(ptr);
            *lptr=NULL;
        }
        else
        {
            node *temp;
            temp=ptr;
            while (temp!=NULL)
            {
                temp=temp->next;
                free(ptr);
                ptr=temp;
            }
            *lptr=NULL;
        }
        
    }
}

void removenode(node** llptr,node* ptr)
{
    node* lptr=*llptr;
    if(lptr==ptr)
    {
        node* nptr=lptr;
        free(nptr);
        *llptr=NULL;
        return;    
    }
    node* temp=lptr;
    while(temp->next!=ptr)
    {
        temp=temp->next;
    }
    temp->next=ptr->next;
    free(ptr);
}

node* Search(node* lptr,int data)
{
    node* temp=lptr;
    while(temp!=NULL)
    {
        if(data==temp->node_num)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

void delete_node_from_different_list(graph *g,int node_no)
{
    for(int i=0;i<g->used;i++)
    {
        if(g->array[i].list!=NULL)
        {
            node* del=Search(g->array[i].list,node_no);
            if(del!=NULL)
            {
                removenode(&(g->array[i].list),del);
            }
        }
    }
}

void deletenode(graph *g,int node_no)
{
    if(g->array[search_node_graph_index(g,node_no)].node_number==-1)
        printf("node dosent exit\n");
    else
    {
        delete_node_list(&(g->array[search_node_graph_index(g,node_no)].list));
        int k=0;
        for(int i=0;i<g->used;i++)
        {
            if(g->array[i].node_number==node_no)
            {
                k=i+1;
                while(k<max)
                {
                    g->array[k-1]=g->array[k];
                    k++;
                }
            }
        }
        g->used--;
        delete_node_from_different_list(g,node_no);
    }
    
}

void insert_nodelist(node** lptr,int dest)
{
    node* nptr=makeNode(dest,0);
    node* temp=*lptr;
    if(*lptr==NULL)
    {
        temp=nptr;
        *lptr=nptr;
        return;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=nptr;

}


void insert_weightnode(node** lptr,int dest,int weight)
{
    node* nptr=makeNode(dest,weight);
    node* temp=*lptr;
    if(*lptr==NULL)
    {
        temp=nptr;
        *lptr=nptr;
        return;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=nptr;

}

void add_edge_directed(graph *g,int src,int dest)
{
    insert_nodelist(&(g->array[search_node_graph_index(g,src)].list),dest);
}

void add_edge_undirected(graph *g,int src,int dest)
{
    insert_nodelist(&(g->array[search_node_graph_index(g,src)].list),dest);
    insert_nodelist(&(g->array[search_node_graph_index(g,dest)].list),src);
}

void add_weight_edge_directed(graph *g,int src,int dest,int weight)
{
    insert_weightnode(&(g->array[search_node_graph_index(g,src)].list),dest,weight);
}

void add_weight_edge_undirected(graph *g,int src,int dest,int weight)
{
    insert_weightnode(&(g->array[search_node_graph_index(g,src)].list),dest,weight);
    insert_weightnode(&(g->array[search_node_graph_index(g,dest)].list),src,weight);
}

void delete_edge_directed(graph* g,int src,int dest)
{
    removenode(&(g->array[src].list),Search(g->array[search_node_graph_index(g,src)].list,dest));
}

void delete_edge_undirected(graph* g,int src,int dest)
{
    removenode(&(g->array[src].list),Search(g->array[search_node_graph_index(g,src)].list,dest));
    removenode(&(g->array[dest].list),Search(g->array[search_node_graph_index(g,dest)].list,src));
}

//--------------------------------------------------------algorithms----------------------------------------------------------//

void DFT(graph *g)
{
    int connected=0;
    stack stck;
    initialise_stack(&stck);
    bool visited[max];
    for(int i=0;i<max;i++)
    {
        visited[i]=false;
    }
    visited[g->array[0].node_number]=true;
    PushStack(&stck,g->array[0].node_number);
    connected++;
    node *temp;
    while (!isStackEmpty(&stck))
    {
        
        printf("%d\n",stck.top->node_num);
        temp=g->array[search_node_graph_index(g,stck.top->node_num)].list;
        PopStack(&stck);
        while (temp!=NULL)
        {
            if(visited[temp->node_num]==false)
            {
                visited[temp->node_num]=true;
                PushStack(&stck,temp->node_num);
                printf("%d\n",stck.top->node_num); 
                connected++;

            }       
            if(visited[temp->node_num]==true)
            {
                //cycle exits
            }
            temp=temp->next;
        }
    }
    if(g->used==connected)
    {
        //connected
    }
}

void BFT(graph *g)
{
    queue q;
    initialize_queue(&q);
    bool visited[max];
    for(int i=0;i<max;i++)
    {
        visited[i]=false;
    }
    visited[g->array[0].node_number]=true;
    insert_queue(&q,g->array[0].node_number);
    node* temp;
    while (!is_queue_empty(&q))
    {
        printf("%d\n",q.front->node_num);
        temp=g->array[search_node_graph_index(g,q.front->node_num)].list;
        delete_queue(&q);
        while (temp!=NULL)
        {
            if(visited[temp->node_num]==false)
            {
                visited[temp->node_num]=true;
                insert_queue(&q,temp->node_num);
            }       
            temp=temp->next;
        }
    }
}

bool DFS(graph* g,int node_num)
{
    stack stck;
    initialise_stack(&stck);
    bool visited[max];
    for(int i=0;i<max;i++)
    {
        visited[i]=false;
    }
    visited[g->array[0].node_number]=true;
    PushStack(&stck,g->array[0].node_number);
    node *temp;
    while (!isStackEmpty(&stck))
    {
        temp=g->array[search_node_graph_index(g,stck.top->node_num)].list;
        PopStack(&stck);
        while (temp!=NULL)
        {
            if(temp->node_num==node_num)
                return true;

            if(visited[temp->node_num]==false)
            {
                visited[temp->node_num]=true;
                PushStack(&stck,temp->node_num);
            }       
            temp=temp->next;
        }
    }
    return false;
}

bool BFS(graph *g,int node_no)
{
    queue q;
    initialize_queue(&q);
    bool visited[max];
    for(int i=0;i<max;i++)
    {
        visited[i]=false;
    }
    visited[g->array[0].node_number]=true;
    insert_queue(&q,g->array[0].node_number);
    node* temp;
    while (!is_queue_empty(&q))
    {
        temp=g->array[search_node_graph_index(g,q.front->node_num)].list;
        delete_queue(&q);
        while (temp!=NULL)
        {
            if(temp->node_num==node_no)
                return true;

            if(visited[temp->node_num]==false)
            {
                visited[temp->node_num]=true;
                insert_queue(&q,temp->node_num);
            }       
            temp=temp->next;
        }
    }
    return false;
}


void topology(int v,bool visited[],stack* st,graph* g)
{
    visited[search_node_graph_index(g,v)]=true;
    node* lptr=g->array[search_node_graph_index(g,v)].list;
    node* temp=lptr;
    if(temp!=NULL)
    {
        while(temp!=NULL)
        {
            if(visited[search_node_graph_index(g,temp->node_num)]==false)
            {
                topology(temp->node_num,visited,st,g);
            }
            temp=temp->next;
        }
    }
    PushStack(st,v);
}

void TopologicalSort(graph* g){
    stack st;
    bool visited[g->used];
    for(int i=0;i<g->used;i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<g->used;i++)
    {
        if(visited[i]==false)
        {
            topology(g->array[i].node_number,visited,&st,g);
        }
    }

    int j=0;
    while(!isStackEmpty(&st) && j<g->used)
    {
        printf("%d-->",st.top->node_num);
        PopStack(&st);
        j++;
    }

}

int Cost(graph* g,int src,int dest)
{
    if(src==dest)
        return 0;

    int index=search_node_graph_index(g,src);
    node* lptr;
    int Cost=INT_MAX;
    lptr=g->array[index].list;
    while (lptr!=NULL)
    {
        if(lptr->node_num==dest)    Cost=lptr->weight;
        
        lptr=lptr->next;
    }
    return Cost;
}

int mindistance(int dist[],int size,bool setSPT[])
{
    int min=INT_MAX;
    int index;
    for(int i=0;i<size;i++)
    {
        if(setSPT[i]!=true && dist[i]<=min) 
        {   
            min=dist[i];index=i;
        }
    }
    return index;
}

void printCost(int dist[],int size,int src)
{
      printf("\nCosts from vertex %d\n",src);
    for(int i=0;i<size;i++)
    {
        printf("vertex %d Cost %d\n",i,dist[i]);
    }
}

void printpath(int path[],int size,int src)
{
    for(int i=0;i<size;i++)
    {
        printf("path from %d to %d\t",src,i);
        if(path[i]==src)
        {
            if(src==i)
            {
                printf("same\n");
            }
            else
            { 
                printf("%d -> %d\n",src,i);
            }
        }
        else
        {
            stack pathhh;
            initialise_stack(&pathhh);
            printf("%d->",src);
            int pth=path[i];
            do
            {
                PushStack(&pathhh,pth);
                //printf("%d->",pth);
                pth=path[pth];
            } while (pth!=src);
            printf("%d\n",i);
        }
    }
}

void Dijkstra_shortest_path(graph* g,int src)
{
    bool setSPT[g->used];
    int path[g->used];
    int dist[g->used];
    for(int i=0;i<g->used;i++)
    {
        path[i]=src;
        setSPT[i]=false;
        dist[i]=INT_MAX;
    }
    for(int i=0;i<g->used;i++)
    {
        if(i==search_node_graph_index(g,src))
            setSPT[i]=true;
        
        dist[i]=Cost(g,src,g->array[i].node_number);
    }
    for(int i=0;i<g->used;i++)
    {
        int min = mindistance(dist,g->used,setSPT);
        setSPT[min]=true;
        for(int j=0;j<g->used;j++)
        {
            if(setSPT[j]==false && dist[min]+Cost(g,min,j)<dist[j])
            {
                dist[j]=dist[min]+Cost(g,min,j);
                path[j]=g->array[min].node_number;
            }
        }
    }
    printCost(dist,g->used,src);
    printf("\npaths are\n\n");
    printpath(path,g->used,src);
}

void all_pair_shortest_path(graph* g)
{
    int dist[g->used][g->used];
    int path[g->used][g->used];
    for(int i=0;i<g->used;i++)
    {
        for(int j=0;j<g->used;j++)
        {
            dist[i][j]=Cost(g,g->array[i].node_number,g->array[j].node_number);
            path[i][j]=i;
        }
    }

    for(int i=0;i<g->used;i++)
    {
        for(int j=0;j<g->used;j++)
        {
            for(int k=0;k<g->used;k++)
            {
                if(dist[j][k]>dist[j][i]+dist[i][k])
                {
                    dist[j][k]=dist[j][i]+dist[i][k];
                    path[j][k]=g->array[i].node_number;
                }
            }
        }
    }
    for(int i=0;i<g->used;i++)
    {
        int distance[g->used];
        int pathh[g->used];
        for(int j=0;j<g->used;j++)
        {
            distance[j]=dist[i][j];
            pathh[j]=path[i][j];
        }
        printCost(distance,g->used,i);
        printpath(pathh,g->used,i);
    }
}


int minKey(int key[], bool mstSet[],int sz) 
{ 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v <sz ; v++) 
        if (mstSet[v] == false && key[v] < min) 
            min = key[v], min_index = v; 
  
    return min_index; 
} 


int printMST(int parent[], graph* graph) 
{ 
    int V=graph->used;
    printf("Edge \tWeight\n"); 
    for (int i = 1; i < V; i++) 
        printf("%d---%d \t%d \n", parent[i], i, Cost(graph,i,parent[i])); 
} 

void prims_minimun_spanning_tree(graph *g)
{
    int parent[g->used]; // Key values used to pick minimum weight edge in cut 
    int key[g->used];//To represent set of vertices included in MST 
    bool mstSET[g->used];// To represent set of vertices not yet included in MST 
    for(int i=0;i<g->used;i++)
        key[i]=INT_MAX,mstSET[i]=false;
    
    key[0]=0;
    parent[0]=-1;

    for(int count=0;count<g->used-1;count++)
    {
        int u = minKey(key,mstSET,g->used);
        mstSET[u]=true;
        for(int v=0;v<g->used;v++)
        {
            if(Cost(g,u,v) && mstSET[v]==false && Cost(g,u,v)<key[v])
                parent[v]=u,key[v]=Cost(g,u,v);
        }
    } 
    int sum=0;
    for(int i=0;i<g->used;i++)
    {
        sum = sum+key[i];
    }
    printf("Cost is %d\n",sum);
    printMST(parent,g);
}

void printallpathutil(int src,int dest,bool visited[],int path[],graph *g,int path_index)
{
    visited[src]=true;
    path[path_index]=src;
    path_index++;
    if(src==dest)
    {
        for(int i=0;i<path_index;i++)
        {
            printf("%d-->",path[i]);
        }
        printf("\n");
    }
    else
    {
        node* temp;
        temp=g->array[search_node_graph_index(g,src)].list;
        while (temp->next!=NULL)
        {
            if(visited[temp->node_num]==false)
            {
                printallpathutil(temp->node_num,dest,visited,path,g,path_index);
            }
        }
    }
    path_index--;
    visited[src]=false;
}

void printallpaths(int src,int dest,graph *g)
{
    bool visited[g->used];
    int path_index=0;
    int path[g->used];
    for(int i=0;i<g->used;i++)
    {
        visited[i]=false;
    }
    printallpathutil(src,dest,visited,path,g,path_index);
}

void main()
{
    graph g = initilize_graph();
    addnode(&g,0);
    addnode(&g,1);
    addnode(&g,2);
    addnode(&g,3);
    addnode(&g,4);
    add_weight_edge_undirected(&g,0,1,2);
    add_weight_edge_undirected(&g,0,2,5);
    add_weight_edge_undirected(&g,0,4,3);
    add_weight_edge_undirected(&g,1,2,6);
    add_weight_edge_undirected(&g,1,4,10);
    add_weight_edge_undirected(&g,1,3,4);
    add_weight_edge_undirected(&g,4,3,2);
    add_weight_edge_undirected(&g,4,2,1);
    add_weight_edge_undirected(&g,2,3,6);
    add_weight_edge_undirected(&g,2,4,2);    
    //printf("DFT for graph is\n");
    //DFT(&g);
    //printf("BFT is\n");
    //BFT(&g);
    //printf("topological sort\n");
    //TopologicalSort(&g);
    //printf("\ndijkstra shortest\n");
    //Dijkstra_shortest_path(&g,0);
    //printf("\nAll shortest path\n");
    //all_pair_shortest_path(&g);
    //printf("\nMST\n");
    prims_minimun_spanning_tree(&g);
}
