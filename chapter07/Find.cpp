//
// Created by 86155 on 2024/7/20.
//
typedef struct {
    // 动态数组基址
    int *elem;
    int tableLen;
} SSTable;

int searchSeq(SSTable ssTable, int key) {
    int i = 0;
    for (; ssTable.elem[i] != key && i < ssTable.tableLen; i++);
    // 查找成功则返回元素下标，失败则返回 -1
    return i == ssTable.tableLen ? -1 : i;
}

int searchSeqWithSentinel(SSTable ssTable, int key) {
    // 0 号位置存放哨兵，数据从下标 1 开始存
    ssTable.elem[0] = key;
    int i = ssTable.tableLen;
    for (; ssTable.elem[i] != key; i--);
    // 查找成功则返回元素下标，失败则返回 0
    return i;
}
