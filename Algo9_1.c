#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
typedef struct Edge {
	int u, v, w; //각각 시작점, 도착점, 가중치
}Edge;

typedef struct Graph {
	int V, E; //vertex, edge개수
	struct Edge* edge;
}Graph;

void BellmanFord(struct Graph *g, int source);
void printfArr(int source, int *dist, int n);
void Relax(int *dist, int u, int v, int w);

int ver1, ver2, cost; //vertex1, vertex2, cost 

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	int start; //시작 정점
	int value[10][3];

	//g생성
	struct Graph *g = (struct Graph*)malloc(sizeof(struct Graph));

	f = fopen("graph.txt", "rt"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	if (feof(f) == 0) { //파일의 첫번째 값만 읽어온다
		fscanf(f, "%d", &g->V);
	}
	
	int e = 0; //edge개수
	/*파일 읽어와서 ver1, ver2, cost값들을 이용해 value배열에 값을 넣어줌*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);
		value[i-1][0] = ver1;
		value[i-1][1] = ver2;
		value[i-1][2] = cost;
		e++; //edge개수 증가
	}

	g->E = e; //edge값을 g->E에 넣어줌
	
	//g의 edge배열
	g->edge = (struct Eege*)malloc(g->E * sizeof(struct Edge));

	//g의 edge배열에 값들을 넣어줌.
	for (int i = 0; i < g->E; i++) {
		g->edge[i].u = value[i][0];
		g->edge[i].v = value[i][1];
		g->edge[i].w = value[i][2];
	}
	printf("시작 정점을 입력해주세요.");
	scanf("%d", &start);
		
	startTime = clock();

	BellmanFord(g, start); //벨만 포드 함수 호출

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

void BellmanFord(struct Graph *g, int source) {
	int V = g->V; //vertex개수
	int E = g->E; //edge개수
	int *dist; //거리정보를 담을 1차원 배열

	dist = (int *)malloc(sizeof(int)*V); //V크기만큼 할당

	//모든 버텍스들을 임의의 무한값으로 초기화시켜준다.
	//INITIALIZE-SINGLE-SLURCE
	for (int i = 0; i < V; i++)
		dist[i] = 999;
	dist[source] = 0; //시작점값은 0으로 설정

	//모든 엣지에대해 RELAX를 진행한다.
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = g->edge[j].u;
			int v = g->edge[j].v;
			int w = g->edge[j].w;

			Relax(dist, u, v, w);
		}
	}

	//음수 가중치를 check.
	for (int i = 0; i < E; i++) {
		int u = g->edge[i].u;
		int v = g->edge[i].v;
		int w = g->edge[i].w;

		if (dist[u] != 999 && dist[u] + w < dist[v])
			printf("그래프에 음수 가중치 사이클이 있습니다.");
	}

	printfArr(source, dist, V); //경로 출력 함수 호출
}

void printfArr(int source, int *dist, int n) {
	for (int i = 0; i < n;++i) {
		printf("vertex 경로 : '%d -> %d' 의 cost : %d\n", source,i, dist[i]);
	}
}

void Relax(int *dist,int u, int v, int w) {
	if (dist[u] != 999 && dist[u] + w < dist[v])
		dist[v] = dist[u] + w;
}
