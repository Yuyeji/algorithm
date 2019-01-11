#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void Dijkstra(int **weight, int source);

int v; //vertex�� ��
int **weight, *visited, *dist; //����ġ ���� ���� �迭, �湮 ���� �迭, �ּҰŸ��� ���� ��� �迭
int ver1, ver2, cost; //vertex1, vertex2, cost 

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	int start = 0; //���� ����

	f = fopen("graph.txt", "rt"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	if (feof(f) == 0) { //������ ù��° ���� �о�´�
		fscanf(f, "%d", &v);
	}

	/*����,���� ���� v��ŭ�� ũ�⸦ ���� 2���� �迭 ����*/
	weight = (int**)malloc(sizeof(int*)*(v));
	for (int i = 0; i < v; i++) {
		weight[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*weight�迭 �ʱ�ȭ*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			weight[i][j] = 999;
			if (i == j) {
				weight[i][j] = 0;
			}
		}
	}

	/*���� �о�ͼ� ver1, ver2, cost������ �̿��� weight�迭 ����*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);

		weight[ver1][ver2] = weight[ver2][ver1] = cost;
	}

	printf("���� ������ �Է����ּ���.");
	scanf("%d", &start);

	startTime = clock();

	Dijkstra(weight, start); //���ͽ�Ʈ�� �˰��� ����

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	/*�޸� free*/
	for (int i = 0; i < v; i++) {
		free(weight[i]);
	}
	free(weight);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

void Dijkstra(int **weight, int source) {
	int vertex = 0;
	int min = 999; //�ּҰ��� ���� ����

	/*1���� �迭 visited�� dist�� vũ�⸸ŭ �Ҵ�*/
	visited = (int*)malloc(sizeof(int) * v);
	dist = (int*)malloc(sizeof(int) * v);

	/*�迭 �ʱ�ȭ*/
	for (int i = 0; i < v; i++) {
		visited[i] = 0;
		dist[i] = 999;
	}
	
	dist[source] = 0; //���������� ������ �Ÿ��� 0

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			if (visited[j] == 0 && min > dist[j]) { //�� �� �ִ� �����߿� ���� ����� ���� ����
				min = dist[j];
				vertex = j;
			}	
		}
		visited[vertex] = 1; //���� ����� �������� �湮, i�������� ���� ����� �ִܰ�� v
		for (int j = 0; j < v; j++) {
			if (dist[j] > dist[vertex] + weight[vertex][j]) { //�Ÿ��� ª������
				dist[j] = dist[vertex] + weight[vertex][j];
				//��ο� �ּ�cost�� ���
				printf("vertex ��� : '%d -> %d'�� �ּ� cost : %d\n", vertex, j, dist[j]);
			}
		}
	}	
}