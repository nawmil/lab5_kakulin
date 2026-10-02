#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ОБЩИЕ

void free_matrix(int** matrix, int rows) {
    if (!matrix) return;
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

void print_matrix(int** adj, int n, const char* title) {
    printf("%s\n   ", title);
    for (int i = 0; i < n; i++) printf("v%-2d ", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("v%-2d ", i);
        for (int j = 0; j < n; j++) printf("%-3d ", adj[i][j]);
        printf("\n");
    }
}

void print_incidence_matrix(int** inc, int n, int m, const char* title) {
    printf("%s\n", title);
    if (m == 0) { printf("Граф не содержит ребер.\n"); return; }
    printf("   ");
    for (int j = 0; j < m; j++) printf("e%-3d ", j);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("v%-2d ", i);
        for (int j = 0; j < m; j++) printf("%-4d ", inc[i][j]);
        printf("\n");
    }
}

// НЕОРИЕНТИРОВАННЫЙ

int** gen_undir(int n, int prob) {
    int** adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) adj[i] = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand() % 100 < prob) { adj[i][j] = 1; adj[j][i] = 1; }
    return adj;
}

int edges_undir(int** adj, int n) {
    int c = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (adj[i][j]) c++;
    return c;
}

void verts_undir(int** adj, int n) {
    int* deg = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[i][j]) deg[i]++;

    printf("Степени вершин: ");
    for (int i = 0; i < n; i++) printf("v%d=%d ", i, deg[i]);
    printf("\n");

    printf("Изолированные вершины: ");
    int c = 0;
    for (int i = 0; i < n; i++) if (deg[i] == 0) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Концевые вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (deg[i] == 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Доминирующие вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (deg[i] == n - 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    free(deg);
}

int** inc_undir(int** adj, int n, int m) {
    int** inc = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) inc[i] = (int*)calloc(m > 0 ? m : 1, sizeof(int));
    if (m == 0) return inc;
    int e = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (adj[i][j]) { inc[i][e] = 1; inc[j][e] = 1; e++; }
    return inc;
}

int inc_edges_undir(int** inc, int n, int m) {
    int s = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) s += inc[i][j];
    return s / 2;
}

void inc_verts_undir(int** inc, int n, int m) {
    int* deg = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) deg[i] += inc[i][j];

    printf("Степени вершин: ");
    for (int i = 0; i < n; i++) printf("v%d=%d ", i, deg[i]);
    printf("\n");

    printf("Изолированные вершины: ");
    int c = 0;
    for (int i = 0; i < n; i++) if (deg[i] == 0) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Концевые вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (deg[i] == 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Доминирующие вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (deg[i] == n - 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    free(deg);
}

// ОРИЕНТИРОВАННЫЙ

int** gen_dir(int n, int prob) {
    int** adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) adj[i] = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (rand() % 100 < prob) adj[i][j] = 1;
        }
    return adj;
}

int edges_dir(int** adj, int n) {
    int c = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[i][j]) c++;
    return c;
}

void verts_dir(int** adj, int n) {
    int* out = (int*)calloc(n, sizeof(int));
    int* in  = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[i][j]) { out[i]++; in[j]++; }

    printf("Исходящие вершины: ");
    for (int i = 0; i < n; i++) printf("v%d=%d ", i, out[i]);
    printf("\n");
    printf("Входящие вершины:  ");
    for (int i = 0; i < n; i++) printf("v%d=%d ", i, in[i]);
    printf("\n");

    printf("Изолированные вершины: ");
    int c = 0;
    for (int i = 0; i < n; i++) if (out[i] == 0 && in[i] == 0) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Концевые вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (out[i] + in[i] == 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Доминирующие вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (out[i] == n - 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    free(out); free(in);
}

int** inc_dir(int** adj, int n, int m) {
    int** inc = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) inc[i] = (int*)calloc(m > 0 ? m : 1, sizeof(int));
    if (m == 0) return inc;
    int e = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[i][j]) { inc[i][e] = 1; inc[j][e] = -1; e++; }
    return inc;
}

int inc_edges_dir(int** inc, int n, int m) {
    int s = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (inc[i][j] == 1) s++;
    return s;
}

void inc_verts_dir(int** inc, int n, int m) {
    int* out = (int*)calloc(n, sizeof(int));
    int* in  = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (inc[i][j] == 1)  out[i]++;
            if (inc[i][j] == -1) in[i]++;
        }

    printf("Исходящие вершины: ");
    for (int i = 0; i < n; i++) printf("v%d=%d ", i, out[i]);
    printf("\n");
    printf("Входящие вершины:  ");
    for (int i = 0; i < n; i++) printf("v%d=%d ", i, in[i]);
    printf("\n");

    printf("Изолированные вершины: ");
    int c = 0;
    for (int i = 0; i < n; i++) if (out[i] == 0 && in[i] == 0) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Концевые вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (out[i] + in[i] == 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    printf("Доминирующие вершины: ");
    c = 0;
    for (int i = 0; i < n; i++) if (out[i] == n - 1) { printf("%d ", i); c++; }
    if (!c) printf("нет");
    printf("\n");

    free(out); free(in);
}

int main() {
    srand((unsigned)time(NULL));

    int n, prob, type;
    printf("Кол-во вершин: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    printf("Тип графа (1 - неориент., 2 - ориент.): ");
    if (scanf("%d", &type) != 1 || (type != 1 && type != 2)) return 1;

    printf("Вероятность ребра/дуги (0..100): ");
    if (scanf("%d", &prob) != 1) return 1;
    if (prob < 0) prob = 0;
    if (prob > 100) prob = 100;

    if (type == 1) {
        printf("\n=== НЕОРИЕНТИРОВАННЫЙ ГРАФ ===\n");
        int** adj = gen_undir(n, prob);
        print_matrix(adj, n, "Матрица смежности:");

        int m = edges_undir(adj, n);
        printf("Ребер: %d\n", m);
        verts_undir(adj, n);

        int** inc = inc_undir(adj, n, m);
        print_incidence_matrix(inc, n, m, "Матрица инцидентности:");
        printf("Ребер (по инц.): %d\n", inc_edges_undir(inc, n, m));
        inc_verts_undir(inc, n, m);

        free_matrix(adj, n);
        free_matrix(inc, n);
    } else {
        printf("\n=== ОРИЕНТИРОВАННЫЙ ГРАФ ===\n");
        int** adj = gen_dir(n, prob);
        print_matrix(adj, n, "Матрица смежности:");

        int m = edges_dir(adj, n);
        printf("Дуг: %d\n", m);
        verts_dir(adj, n);

        int** inc = inc_dir(adj, n, m);
        printf("(+1 — выходит, -1 — входит)\n");
        print_incidence_matrix(inc, n, m, "Матрица инцидентности:");
        printf("Дуг (по инц.): %d\n", inc_edges_dir(inc, n, m));
        inc_verts_dir(inc, n, m);

        free_matrix(adj, n);
        free_matrix(inc, n);
    }

    return 0;
}