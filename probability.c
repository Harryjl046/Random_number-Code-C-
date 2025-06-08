#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 // 定义随机数范围[0,N-1]
#define TRIALS 100000 // 试验次数

// 方法1: 使用数组直接统计
void method1() {
    int counts[N] = {0};
    
    for (int i = 0; i < TRIALS; i++) {
        int x = rand() % N;
        counts[x]++;
    }
    
    printf("Method 1 - Direct counting:\n");
    printf("Num \t Percentage\n");
    printf("----\t----------\n");
    for (int i = 0; i < N; i++) {
        printf("%-3d \t %8.2f%%\n", i, (double)counts[i]/TRIALS*100);
    }
}

// 方法2: 使用哈希表结构统计
void method2() {
    struct HashNode {
        int key;
        int count;
        struct HashNode* next;
    };
    
    struct HashNode* hashTable[N] = {NULL};
    
    for (int i = 0; i < TRIALS; i++) {
        int x = rand() % N;
        
        // 查找或创建节点
        struct HashNode* node = hashTable[x];
        if (!node) {
            node = (struct HashNode*)malloc(sizeof(struct HashNode));
            node->key = x;
            node->count = 1;
            node->next = NULL;
            hashTable[x] = node;
        } else {
            node->count++;
        }
    }
    
    printf("\nMethod 2 - hash table:\n");
    printf("Num \t Percentage\n");
    printf("----\t----------\n");
    for (int i = 0; i < N; i++) {
        if (hashTable[i]) {
            printf("%-3d \t %8.2f%%\n", i, (double)hashTable[i]->count/TRIALS*100);
            free(hashTable[i]); // 释放内存
        } else {
            printf("%-3d \t %8.2f%%\n", i, 0.00);
        }
    }
}

// 方法3: 使用指针数组统计
void method3() {
    int counts[N] = {0};
    int *p[N];
    
    for (int i = 0; i < N; i++) {
        p[i] = &counts[i];
    }
    
    for (int i = 0; i < TRIALS; i++) {
        int x = rand() % N;
        (*p[x])++;
    }
    
    printf("\nMethod 3 - Pointer array:\n");
    printf("Num \t Percentage\n");
    printf("----\t----------\n");
    for (int i = 0; i < N; i++) {
        printf("%-3d \t %8.2f%%\n", i, (double)counts[i]/TRIALS*100);
    }
}

// 方法4: 使用位运算优化统计
void method4() {
    unsigned int counts[N] = {0}; // 使用无符号整数便于位操作
    
    for (int i = 0; i < TRIALS; i++) {
        int x = rand() % N;
        // 使用位运算优化计数
        counts[x] = (counts[x] & ~1) | ((counts[x] & 1) ^ 1); // 翻转最低位
        counts[x] += (counts[x] & 1) ? 0 : 2; // 如果最低位为0则加2
    }
    
    printf("\nMethod 4 - Bit operation optimized:\n");
    printf("Num \t Percentage\n");
    printf("----\t----------\n");
    for (int i = 0; i < N; i++) {
        printf("%-3d \t %8.2f%%\n", i, (double)counts[i]/TRIALS*100);
    }
}

// 方法5: 使用函数指针数组
// 递归计数函数
void recursive_count(int *count, int remaining) {
    if (remaining <= 0) return;
    (*count)++;
    recursive_count(count, remaining - 1);
}

void method5() {
    int counts[N] = {0};
    
    for (int i = 0; i < TRIALS; i++) {
        int x = rand() % N;
        recursive_count(&counts[x], 1); // 每次增加1
    }
    
    printf("\nMethod 5 - Recursive counting:\n");
    printf("Num \t Percentage\n");
    printf("----\t----------\n");
    for (int i = 0; i < N; i++) {
        printf("%-3d \t %8.2f%%\n", i, (double)counts[i]/TRIALS*100);
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