#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define MAX 6555 
#define TRUE 1
#define FALSE 0

// Functions declaration

void networkInit(int N, int X, float network[][X]);
int CheckValue(int N, float dist[]);
float Rc(int N, float arr[]);
void dijkstra(int u, int N, int X, float network[][X], float dist[]);
float networkDiam(int N, int X, float NodesPath[][X]);

int main()
{
    int N;
    printf("Please enter the number of network's nodes <= 100\n");
    scanf("%d", &N);
    while (N > 100) {
        printf("The number of nodes is incorrect.\n Please enter Again the number of network's nodes \n");
        scanf("%d", &N);
    }
    
    float nodesCoords[N][2];

    int i, j, k, i1, j1; // Counters
    
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        for (j = 0; j < 2; j++) {
            nodesCoords[i][j] = (float) rand() / (float) RAND_MAX;
        }
    }

    float EuclDist[N][N];
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i != j) {
                EuclDist[i][j] = sqrt(pow(nodesCoords[i][0] - nodesCoords[j][0], 2) + pow(nodesCoords[i][1] - nodesCoords[j][1], 2));
            } else {
                EuclDist[i][j] = 0.0;
            }
        }
    }
    
    float network[N][N];  // Network array contains network's nodes connections weights
    networkInit(N, N, network); // Network Initialization
    
    float r;
    
    int u = 0; 
    float dist[N]; 
    for (i = 0; i < N; i++) {
        dist[i] = MAX;
    }
    
    /*  ******************************************************
        *                 rc calculation                     *
        ******************************************************  */
    
    int CheckMatrix = (N * N - N) / 2;
    float Check_rc[CheckMatrix]; 
    for (k = 0; k < CheckMatrix; k++) {
        Check_rc[k] = MAX;
    }

    int count = 0;
    float rc;

    for (i1 = 0; i1 < N; i1++) {
        for (j1 = 0; j1 < N; j1++) {
            if (i1 < j1) {
                r = EuclDist[i1][j1];
                for (i = 0; i < N; i++) {
                    for (j = 0; j < N; j++) {
                        if (EuclDist[i][j] <= r) {
                            network[i][j] = EuclDist[i][j];
                        }
                    }
                }
                dijkstra(u, N, N, network, dist);
                if (!CheckValue(N, dist)) {
                    Check_rc[count] = r;
                    count++;
                }
                networkInit(N, N, network);
            }
        }
    }
    
    rc = Rc(CheckMatrix, Check_rc);
    printf("\n***************************\n");
    printf("The value of rc = %f \n", rc);
    printf("***************************\n");
    
    
    float NodesPath[N][N];
    networkInit(N, N, network);

    printf("\nPlease enter the number of parameter r \n");
    scanf("%f", &r);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (EuclDist[i][j] <= r) {
                network[i][j] = EuclDist[i][j];
            }
        }
    }

    for (i = 0; i < N; i++) {
        dijkstra(i, N, N, network, dist);
        for (j = 0; j < N; j++) {
            NodesPath[i][j] = dist[j];
        }
    }

    float D;
    D = networkDiam(N, N, NodesPath);
    printf("The diameter of the network is D = %f\n", D);
    
    
    
    
    
    system("pause");
    
    return 0;

   
}    

  /*  **************************************
      *                                    *
      *             Functions              *
      *                                    *
      **************************************   */
      
  void networkInit(int N, int X, float network[][X]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < X; j++) {
            if (i == j) {
                network[i][j] = 0.0;
            } else {
                network[i][j] = MAX;
            }
        }
    }
 }
 

 void dijkstra(int u, int N, int X, float network[][X], float dist[]) {
    int w, v, onScanQ[N], k, prevNode[N];
    for (v = 0; v < N; v++) {
        dist[v] = MAX;
        onScanQ[v] = FALSE;
        prevNode[v] = -1;
    }
    dist[u] = 0;
    v = u;
    onScanQ[u] = TRUE;
    k = 0;
    for (k = 0; k < N; k++) {
        int min = MAX;
        for (w = 0; w < N; w++) {
            if (network[v][w] < MAX) {
                if (dist[w] > dist[v] + network[v][w]) {
                    dist[w] = dist[v] + network[v][w];
                    prevNode[w] = v;
                }
            }
        }
        for (w = 0; w < N; w++) {
            if (!onScanQ[w]) {
                if (min > dist[w]) {
                    min = dist[w];
                    v = w;
                }
            }
            onScanQ[v] = TRUE;
        }
    }

 }
 
 int CheckValue(int N, float dist[]) {
    int k;
    int result = FALSE;
    for (k = 0; k < N; k++) {
        if (dist[k] == MAX) {
            result = TRUE;
            break;
        }
    }
    return result;
 }        
 
 
   float Rc(int n, float arr[]) {
    int i;
    float result = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] < result) {
            result = arr[i];
        }
    }
    return result;
 }
 
 float networkDiam(int N, int X, float NodesPath[][X]) {
    int i, j;
    float diam = NodesPath[0][0];
    for (i = 0; i < N; i++) {
        for (j = 1; j < X; j++) {
            if ((NodesPath[i][j] > diam)&&(NodesPath[i][j] < MAX)) {
                diam = NodesPath[i][j];
            }
        }
    }
    return diam;
}
