#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10 // 定义随机数范围[0,N-1]
#define TRIALS 100000 // 试验次数

// 生成[0,N-1]均匀分布的随机数
int uniform_random() {
    // 使用整数除法计算bucket_size
    const int bucket_size = (RAND_MAX + 1) / N;  // 避免整数除法截断
    const int max_valid = bucket_size * N;
    
    int value;
    do {
        value = rand();
    } while (value >= max_valid);
    
    // 使用纯整数运算避免精度损失
    return value / bucket_size;
}

// 生成正态分布的随机数(Box-Muller变换)
double normal_random(double mean, double stddev) {
    static double n2 = 0.0;
    static int n2_cached = 0;
    
    if (!n2_cached) {
        double x, y, r;
        do {
            x = 2.0 * rand() / RAND_MAX - 1;
            y = 2.0 * rand() / RAND_MAX - 1;
            r = x*x + y*y;
        } while (r == 0.0 || r > 1.0);
        
        double d = sqrt(-2.0 * log(r) / r);
        double n1 = x * d;
        n2 = y * d;
        
        n2_cached = 1;
        return mean + stddev * n1;
    } else {
        n2_cached = 0;
        return mean + stddev * n2;
    }
}

// 测试均匀分布
void test_uniform() {
    int counts[N] = {0};
    
    for (int i = 0; i < TRIALS; i++) {
        int x = uniform_random();
        counts[x]++;
    }
    
    printf("Uniform distribution test (N=%d):\n", N);
    // 边界值验证
    int min_val = 0, max_val = 0;
    for (int i = 0; i < N; i++) {
        if (counts[i] < counts[min_val]) min_val = i;
        if (counts[i] > counts[max_val]) max_val = i;
    }
    
    // 计算最大计数用于缩放
    int max_count = counts[max_val];
    
    // 打印ASCII直方图
    printf("\nValue | Percentage | Histogram\n");
    printf("----- | ---------- | ---------\n");
    for (int i = 0; i < N; i++) {
        double percentage = (double)counts[i]/TRIALS*100;
        printf("%5d | %9.2f%% | ", i, percentage);
        
        // 绘制直方图条
        int bar_length = (int)((double)counts[i]/max_count * 50);
        for (int j = 0; j < bar_length; j++) {
            printf("#");
        }
        printf("\n");
    }
}

// 测试正态分布
void test_normal() {
    double mean = (N-1)/2.0;
    double stddev = (N-1)/6.0; // 覆盖99.7%的范围
    
    int counts[N] = {0};
    
    for (int i = 0; i < TRIALS; i++) {
        double x = normal_random(mean, stddev);
        int idx = (int)(x + 0.5); // 四舍五入
        if (idx >= 0 && idx < N) {
            counts[idx]++;
        }
    }
    
    printf("\nNormal distribution test (mean=%.1f, stddev=%.1f):\n", mean, stddev);
    
    // 计算最大计数用于缩放
    int max_count = 0;
    for (int i = 0; i < N; i++) {
        if (counts[i] > max_count) max_count = counts[i];
    }
    
    // 打印ASCII直方图
    printf("\nValue | Percentage | Histogram\n");
    printf("----- | ---------- | ---------\n");
    for (int i = 0; i < N; i++) {
        double percentage = (double)counts[i]/TRIALS*100;
        printf("%5d | %9.2f%% | ", i, percentage);
        
        // 绘制直方图条
        int bar_length = (int)((double)counts[i]/max_count * 50);
        for (int j = 0; j < bar_length; j++) {
            printf("#");
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // 初始化随机数种子
    
    test_uniform();
    test_normal();
    
    return 0;
}