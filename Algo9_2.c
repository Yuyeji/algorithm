#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void Dijkstra(int **weight, int source);

int v; //vertex의 수
int **weight, *visited, *dist; //가중치 들을 담은 배열, 방문 여부 배열, 최소거리의 정보 담는 배열
int ver1, ver2, cost; //vertex1, vertex2, cost 

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	int start = 0; //시작 정점

	f = fopen("graph.txt", "rt"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	if (feof(f) == 0) { //파일의 첫번째 값만 읽어온다
		fscanf(f, "%d", &v);
	}

	/*가로,세로 각각 v만큼의 크기를 가진 2차원 배열 생성*/
	weight = (int**)malloc(sizeof(int*)*(v));
	for (int i = 0; i < v; i++) {
		weight[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*weight배열 초기화*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			weight[i][j] = 999;
			if (i == j) {
				weight[i][j] = 0;
			}
		}
	}

	/*파일 읽어와서 ver1, ver2, cost값들을 이용해 weight배열 생성*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);

		weight[ver1][ver2] = weight[ver2][ver1] = cost;
	}

	printf("시작 정점을 입력해주세요.");
	scanf("%d", &start);

	startTime = clock();

	Dijkstra(weight, start); //다익스트라 알고리즘 실행

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	/*메모리 free*/
	for (int i = 0; i < v; i++) {
		free(weight[i]);
	}
	free(weight);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

void Dijkstra(int **weight, int source) {
	int vertex = 0;
	int min = 999; //최소값을 담을 변수

	/*1차원 배열 visited와 dist를 v크기만큼 할당*/
	visited = (int*)malloc(sizeof(int) * v);
	dist = (int*)malloc(sizeof(int) * v);

	/*배열 초기화*/
	for (int i = 0; i < v; i++) {
		visited[i] = 0;
		dist[i] = 999;
	}
	
	dist[source] = 0; //시작점부터 시작점 거리는 0

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			if (visited[j] == 0 && min > dist[j]) { //갈 수 있는 정점중에 가장 가까운 정점 선택
				min = dist[j];
				vertex = j;
			}	
		}
		visited[vertex] = 1; //가장 가까운 정점으로 방문, i정점에서 가장 가까운 최단경로 v
		for (int j = 0; j < v; j++) {
			if (dist[j] > dist[vertex] + weight[vertex][j]) { //거리가 짧아지면
				dist[j] = dist[vertex] + weight[vertex][j];
				//경로와 최소cost값 출력
				printf("vertex 경로 : '%d -> %d'의 최소 cost : %d\n", vertex, j, dist[j]);
			}
		}
	}	
}