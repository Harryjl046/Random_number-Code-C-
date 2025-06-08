#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 // 定义随机数范围[0,N-1]
#define TRIALS 100000 // 试验次数
#define MAX_GAP 100 // 最大间隔统计范围

// 方法1: 使用数组记录上次出现位置
void method1() {
    int last_pos[N] = {0};
    int gap_counts[N][MAX_GAP] = {0};
    
    for (int i = 1; i <= TRIALS; i++) {
        int x = rand() % N;
        int gap = i - last_pos[x];
        if (last_pos[x] != 0 && gap < MAX_GAP) {
            gap_counts[x][gap]++;
        }
        last_pos[x] = i;
    }
    
    printf("\nMethod 1 - Last position tracking:\n");
    printf("Number | Gap Distribution (1-10)\n");
    printf("------ | -----------------------\n");
    for (int i = 0; i < N; i++) {
        printf("%5d | ", i);
        for (int j = 1; j <= 10; j++) {
            printf("%5d ", gap_counts[i][j]);
        }
        printf("\n");
    }
}

// 方法2: 使用链表记录所有出现位置
typedef struct Node {
    int pos;
    struct Node* next;
} Node;

void method2() {
    Node* heads[N] = {NULL};
    int gap_counts[N][MAX_GAP] = {0};
    
    for (int i = 1; i <= TRIALS; i++) {
        int x = rand() % N;
        
        // 创建新节点并插入链表头部
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->pos = i;
        new_node->next = heads[x];
        heads[x] = new_node;
        
        // 计算与前一个位置的间隔
        if (new_node->next != NULL) {
            int gap = new_node->pos - new_node->next->pos;
            if (gap < MAX_GAP) {
                gap_counts[x][gap]++;
            }
        }
    }
    
    printf("\nMethod 2 - Linked list tracking:\n");
    printf("Number | Gap Distribution (1-10)\n");
    printf("------ | -----------------------\n");
    for (int i = 0; i < N; i++) {
        printf("%5d | ", i);
        for (int j = 1; j <= 10; j++) {
            printf("%5d ", gap_counts[i][j]);
        }
        printf("\n");
        
        // 释放链表内存
        Node* current = heads[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// 方法3: 使用二维数组记录所有位置
void method3() {
    int* positions[N];
    int counts[N] = {0};
    int gap_counts[N][MAX_GAP] = {0};
    
    // 为每个数字分配位置数组
    for (int i = 0; i < N; i++) {
        positions[i] = (int*)malloc(TRIALS * sizeof(int));
    }
    
    for (int i = 1; i <= TRIALS; i++) {
        int x = rand() % N;
        
        if (counts[x] > 0) {
            int gap = i - positions[x][counts[x]-1];
            if (gap < MAX_GAP) {
                gap_counts[x][gap]++;
            }
        }
        
        positions[x][counts[x]++] = i;
    }
    
    printf("\nMethod 3 - 2D array tracking:\n");
    printf("Number | Gap Distribution (1-10)\n");
    printf("------ | -----------------------\n");
    for (int i = 0; i < N; i++) {
        printf("%5d | ", i);
        for (int j = 1; j <= 10; j++) {
            printf("%5d ", gap_counts[i][j]);
        }
        printf("\n");
        free(positions[i]); // 释放内存
    }
}

// 方法4: 使用位域压缩存储
void method4() {
    unsigned int last_pos[N] = {0};
    unsigned short gap_counts[N][MAX_GAP] = {0};
    
    for (unsigned int i = 1; i <= TRIALS; i++) {
        int x = rand() % N;
        unsigned int gap = i - last_pos[x];
        if (last_pos[x] != 0 && gap < MAX_GAP) {
            gap_counts[x][gap]++;
        }
        last_pos[x] = i;
    }
    
    printf("\nMethod 4 - Bit field optimized:\n");
    for (int i = 0; i < N; i++) {
        printf("%5d | ", i);
        for (int j = 1; j <= 10; j++) {
            printf("%5d ", gap_counts[i][j]);
        }
        printf("\n");
    }
}

// 方法5: 使用函数指针
void record_gap(int (*gap_counts)[MAX_GAP], int x, int gap) {
    if (gap < MAX_GAP) {
        gap_counts[x][gap]++;
    }
}

void method5() {
    int last_pos[N] = {0};
    int gap_counts[N][MAX_GAP] = {0};
    void (*recorder)(int (*)[MAX_GAP], int, int) = record_gap;
    
    for (int i = 1; i <= TRIALS; i++) {
        int x = rand() % N;
        int gap = i - last_pos[x];
        if (last_pos[x] != 0) {
            recorder(gap_counts, x, gap);
        }
        last_pos[x] = i;
    }
    
    printf("\nMethod 5 - Function pointer:\n");
    for (int i = 0; i < N; i++) {
        printf("%5d | ", i);
        for (int j = 1; j <= 10; j++) {
            printf("%5d ", gap_counts[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // 初始化随机数种子
    
    method1();
    method2();
    method3();
    method4();
    method5();
    
    return 0;
}