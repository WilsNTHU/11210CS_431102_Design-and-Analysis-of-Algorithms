#include <iostream>
#include <vector>
#include <climits>


using namespace std;

#define V 9

// Vertices of NTHU Dataset
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8

int graph[V][V];
int parent[V];
int discard_edge[V][V];
int visited[V][V];
int step = 1;

char findCharacter(int val){
    switch(val){
        case 0: return 'A'; break;
        case 1: return 'B'; break;
        case 2: return 'C'; break;
        case 3: return 'D'; break;
        case 4: return 'E'; break;
        case 5: return 'F'; break;
        case 6: return 'G'; break;
        case 7: return 'H'; break;
        default: return 'I'; break;
    }
}

void addEdge(int i, int j, int val){
    graph[i][j] = val;
    graph[j][i] = val;
}

int find(int i){
    while(parent[i] != i) i = parent[i];
    return i;
}

void union_func(int i, int j){
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}


void kruskal(){
    int min_cost = INT_MAX;
    int count = 0;

    while(count < (V-1)){
        int min = INT_MAX;
        int a = -1, b = -1, flag = 1;
        while(flag){
            a = -1, b = -1, min = INT_MAX;
            flag = 1;
            for(int i=0; i<V; i++){
                for(int j=0; j<V; j++){
                    if(graph[i][j] != -1 && graph[i][j] < min && !discard_edge[i][j] && !visited[i][j]){
                        min = graph[i][j];
                        a = i;
                        b = j;
                    }
                }
            }

            if(parent[a] == parent[b]){
                discard_edge[a][b] = 1;
                discard_edge[b][a] = 1;
                printf("step%d. discard(%c, %c) due to the formation of cycle\n", step++, findCharacter(a), findCharacter(b));
            }
            else{
                visited[a][b] = 1;
                visited[b][a] = 1;
                union_func(a, b);
                printf("step%d. select(%c, %c)\n", step++, findCharacter(a), findCharacter(b));
                flag = 0;
                min_cost += min;
                count ++;
            }
        }
        
    }
    
}



int main(void){
    for(int i=0; i<V; i++){
        parent[i] = i;
        for(int j=0; j<V; j++){
            graph[i][j] = -1;
            graph[j][i] = -1;
            visited[i][j] = 0;
            visited[j][i] = 0;
            discard_edge[i][j] = 0;
            discard_edge[j][i] = 0;
        }
    }

    // Using NTHU coursework data

    addEdge(A, B, 4);
    addEdge(A, H, 8);
    addEdge(B, H, 11);
    addEdge(B, C, 8);
    addEdge(H, I, 7);
    addEdge(H, G, 1);
    addEdge(I, G, 6);
    addEdge(C, I, 2);
    addEdge(C, F, 4);
    addEdge(G, F, 2);
    addEdge(C, D, 7);
    addEdge(D, F, 14);
    addEdge(D, E, 9);
    addEdge(E, F, 10);
    
    kruskal();
    
    return 0;
}