#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
typedef struct Edge {
	int u, v, w; //���� ������, ������, ����ġ
}Edge;

typedef struct Graph {
	int V, E; //vertex, edge����
	struct Edge* edge;
}Graph;

void BellmanFord(struct Graph *g, int source);
void printfArr(int source, int *dist, int n);
void Relax(int *dist, int u, int v, int w);

int ver1, ver2, cost; //vertex1, vertex2, cost 

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	int start; //���� ����
	int value[10][3];

	//g����
	struct Graph *g = (struct Graph*)malloc(sizeof(struct Graph));

	f = fopen("graph.txt", "rt"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	if (feof(f) == 0) { //������ ù��° ���� �о�´�
		fscanf(f, "%d", &g->V);
	}
	
	int e = 0; //edge����
	/*���� �о�ͼ� ver1, ver2, cost������ �̿��� value�迭�� ���� �־���*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);
		value[i-1][0] = ver1;
		value[i-1][1] = ver2;
		value[i-1][2] = cost;
		e++; //edge���� ����
	}

	g->E = e; //edge���� g->E�� �־���
	
	//g�� edge�迭
	g->edge = (struct Eege*)malloc(g->E * sizeof(struct Edge));

	//g�� edge�迭�� ������ �־���.
	for (int i = 0; i < g->E; i++) {
		g->edge[i].u = value[i][0];
		g->edge[i].v = value[i][1];
		g->edge[i].w = value[i][2];
	}
	printf("���� ������ �Է����ּ���.");
	scanf("%d", &start);
		
	startTime = clock();

	BellmanFord(g, start); //���� ���� �Լ� ȣ��

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

void BellmanFord(struct Graph *g, int source) {
	int V = g->V; //vertex����
	int E = g->E; //edge����
	int *dist; //�Ÿ������� ���� 1���� �迭

	dist = (int *)malloc(sizeof(int)*V); //Vũ�⸸ŭ �Ҵ�

	//��� ���ؽ����� ������ ���Ѱ����� �ʱ�ȭ�����ش�.
	//INITIALIZE-SINGLE-SLURCE
	for (int i = 0; i < V; i++)
		dist[i] = 999;
	dist[source] = 0; //���������� 0���� ����

	//��� ���������� RELAX�� �����Ѵ�.
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = g->edge[j].u;
			int v = g->edge[j].v;
			int w = g->edge[j].w;

			Relax(dist, u, v, w);
		}
	}

	//���� ����ġ�� check.
	for (int i = 0; i < E; i++) {
		int u = g->edge[i].u;
		int v = g->edge[i].v;
		int w = g->edge[i].w;

		if (dist[u] != 999 && dist[u] + w < dist[v])
			printf("�׷����� ���� ����ġ ����Ŭ�� �ֽ��ϴ�.");
	}

	printfArr(source, dist, V); //��� ��� �Լ� ȣ��
}

void printfArr(int source, int *dist, int n) {
	for (int i = 0; i < n;++i) {
		printf("vertex ��� : '%d -> %d' �� cost : %d\n", source,i, dist[i]);
	}
}

void Relax(int *dist,int u, int v, int w) {
	if (dist[u] != 999 && dist[u] + w < dist[v])
		dist[v] = dist[u] + w;
}
