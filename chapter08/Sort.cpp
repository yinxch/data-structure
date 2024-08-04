//
// Created by 86155 on 2024/8/3.
//
// 插入排序
void insertSort(int arr[], int n) {
    int i, j, temp;
    // 注意这里是 i < n，因为  n = length
    for (i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            // 用 temp 暂存 A[i]
            temp = arr[i];
            // 检查所有前面已排好的元素
            for (j = i - 1; j >= 0 && arr[j] > temp; j--) {
                // 所有大于 temp 的元素都向后挪位
                arr[j + 1] = arr[j];
            }
            // 复制到插入位置
            arr[j + 1] = temp;
        }
    }
}

// 插入排序哨兵实现
void insertSortWithSentinel(int arr[], int n) {
    int i, j;
    // 依次将 arr[2] - arr[n] 插入到前面已排序序列
    // 注意这里是 i <= n，因为  n = length - 1
    for (i = 2; i <= n; i++) {
        // 若 arr[i] 小于其前驱，将 arr[i] 插入有序表
        if (arr[i] < arr[i - 1]) {
            // 复制为哨兵，arr[0] 不存放任何元素
            arr[0] = arr[i];
            // 从后往前查找待插入位置
            for (j = i - 1; arr[0] < arr[j]; j--) {
                // 向后挪位
                arr[j + 1] = arr[j];
            }
            // 复制到插入位置
            arr[j + 1] = arr[0];
        }
    }
}

void insertSortWithBinarySearch(int arr[], int n) {
    int i, j, low, high, mid;
    for (i = 2; i <= n; i++) {
        arr[0] = arr[i];
        low = 1;
        high = i - 1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (arr[0] >= arr[mid]) {
                low = mid + 1;
            } else if (arr[0] < arr[mid]) {
                high = mid - 1;
            }
        }
        for (j = i - 1; j >= high + 1; --j) {
            arr[j + 1] = arr[j];
        }
    }
}

// 希尔排序
void shellSort(int arr[], int n) {
    int d, i, j;
    for (d = n / 2; d >= 1; d = d / 2) {
        for (i = d + 1; i <= n; i++) {
            if (arr[i] < arr[i - d]) {
                arr[0] = arr[i];
                // 注意这里的终止条件和插入排序的区别
                for (j = i - d; j > 0 && arr[0] < arr[j]; j -= d) {
                    arr[j + d] = arr[j];
                }
                arr[j + d] = arr[0];
            }
        }
    }
}

// 冒泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = n - 1; j > i; j--) {
            bool flag = false;
            if (arr[j] < arr[j - 1]) {
                int tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
                flag = true;
            }
            if (!flag) return;
        }

    }
}

int partition(int arr[], int low, int high) {
    // 第一个元素作为枢轴
    int pivot = arr[low];
    // 用 low high 搜索枢轴的最终位置
    while (low < high) {
        while (low < high && arr[high] >= pivot) high--;
        // 比枢轴小的元素移动到左端
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) low++;
        // 比枢轴大的元素移动到右端
        arr[high] = arr[low];
    }
    // 枢轴元素存放到最终位置
    arr[low] = pivot;
    // 返回存放枢轴的最终位置
    return low;
}

void quickSort(int arr[], int low, int high) {
    // 递归跳出的条件
    if (low < high) {
        // 划分
        int pos = partition(arr, low, high);
        // 划分左子表
        quickSort(arr, low, pos - 1);
        // 划分右子表
        quickSort(arr, pos + 1, high);
    }
}

void swap(int a, int b) {}

// 选择排序
void selectSort(int arr[], int n) {
    // 一共进行 n-1 趟
    for (int i = 0; i < n - 1; ++i) {
        // 记录最小元素的位置
        int min = i;
        // 在 arr[i,...n-1] 中选择最小的元素
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) swap(arr[i], arr[min]);
    }
}

// 将以 k 为根的子树调整为大根堆
// len 是最大下标
void headAdjust(int arr[], int k, int len) {
    arr[0] = arr[k];
    // 从 k 结点的左孩子
    for (int i = 2 * k; i <= len; i *= 2) {
        // 若存在右孩子，且右孩子大于左孩子
        if (i < len && arr[i] < arr[i + 1]) i++;
        // 父结点大于最大的子结点
        if (arr[k] >= arr[i]) break;
        else {
            arr[k] = arr[i];
            k = i;
        }
        // 将被筛选结点的值放入最终位置
        arr[k] = arr[0];
    }
}

// 建立大根堆
void buildMaxHeap(int arr[], int len) {
    // 从后网球调整所有非终端结点
    for (int i = len / 2; i > 0; i--)
        headAdjust(arr, i, len);
}

void heapSort(int arr[], int len) {
    buildMaxHeap(arr, len);
    for (int i = len; i > 1; --i) {
        swap(arr[i], arr[1]);
        headAdjust(arr, 1, i - 1);
    }
}
