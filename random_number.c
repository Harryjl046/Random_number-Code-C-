#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<limits.h>

#define N 256 // 定义随机数范围[0,N-1]
#define SEQUENCE_LENGTH 125000 // 随机数序列长度

int main() {
    //int范围
    printf("INT_MIN: %d\nINT_MAX: %d\n", INT_MIN, INT_MAX);

    // 初始化随机数种子
    srand(time(NULL));
    
    // 创建并打开二进制文件
    FILE *file = fopen("random_sequence.bin", "wb");
    if (file == NULL) {
        printf("无法创建文件!\n");
        return 1;
    }
    
    // 生成随机数序列并写入文件
    for (int i = 0; i < SEQUENCE_LENGTH; i++) {
        int random_num = rand() % N;
        fwrite(&random_num, sizeof(int), 1, file);
    }
    
    fclose(file);
    printf("随机数序列已成功保存到random_sequence.bin文件\n");
    
    return 0;
}