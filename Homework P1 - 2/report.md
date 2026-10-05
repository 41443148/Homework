# 41443148

作業二

## 解題說明

這道題目的核心概念是集合的冪集（Powerset），要求寫出一個遞歸函數來計算所有可能的子集。

### 解題策略

1. 問題定義與數學原理冪集定義：若 $S$ 是一個包含 $n$ 個元素的集合，則 $S$ 的冪集為所有可能子集構成的集合。若集合大小為 $n$，其總子集數量會是 $2^n$ 個（包含空集合與集合本身）。

核心思維（二選一法）：對於集合中的每一個元素，我們都有兩種選擇：

(1. ) 不放入當前子集。

(2. ) 放入當前子集。透過遞歸完整走訪這兩種選擇，就能不重複、不遺漏地產生所有子集。

2.遞歸設計邏輯（演算法步驟）這是一個經典的回溯/遞歸設計，主要包含兩個條件：遞歸終止條件（Base Case）：
當我們考慮完集合中的每一個元素（即索引 index 等於集合大小 n）時，代表已經決定好一個完整的子集，此時即可直接輸出或儲存該子集。   
遞歸推進與分支（Recursive Step）：針對當前索引的元素 S[index]：

(1. )分支一（不選）：直接進入下一個元素的遞歸 index + 1，當前子集內容不變。

(2. )分支二（選）：將 S[index] 加入當前子集中，然後進入下一個元素的遞歸 index + 1；在遞歸返回後，將該元素移除（回溯），以便乾淨地進行下一個分支。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

long long ackermannRecursive(long long m, long long n) {
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    }
    else {
        return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
    }
}

long long ackermannNonRecursive(long long m, long long n) {

    const int MAX_STACK = 100000;
    long long stack[MAX_STACK];
    int top = -1;

    stack[++top] = m;

    while (top >= 0) {
        m = stack[top--];

        if (m == 0) {
            n = n + 1;
        }
        else if (n == 0) {
            n = 1;
            stack[++top] = m - 1;
        }
        else {
            stack[++top] = m - 1;
            stack[++top] = m;
            n = n - 1;
        }
    }
    return n;
}

int main() {
    long long m, n;
    cout << " input m and n: ";
    if (std::cin >> m >> n) {
        std::cout << endl << "output" << std::endl;

        long long resultRec = ackermannRecursive(m, n);
        std::cout << "Recursive A(" << m << ", " << n << ") = " << resultRec << std::endl;

        long long resultNonRec = ackermannNonRecursive(m, n);
        std::cout << "NonRecursive A(" << m << ", " << n << ") = " << resultNonRec << std::endl;
    }

    return 0;
}
```

## 效能分析

1. 時間複雜度：Ackermann 函數的增長速度極快，其時間複雜度會隨著 $m$ 和 $n$ 的增加呈超指数級成長（Hyper-exponential）。
2. 空間複雜度：遞迴版本：空間複雜度主要取決於系統呼叫堆疊（Call Stack），在深度過大時空間開銷極高。非遞迴版本：空間複雜度為 $O(K)$（$K$ 為自定義陣列大小 MAX_STACK），能有效預防系統堆疊崩潰。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $(m,n)$ | 預期輸出 | 遞迴實際輸出 | 非遞迴實際輸出 |
|----------|--------------|----------|----------|----------|
| 測試一   | $m = 0, n = 0$      | 1        | 1        | 1        |
| 測試二   | $m = 1, n = 2$      | 4        | 4        | 4        |
| 測試三   | $m = 2, n = 2$      | 7        | 7        | 7        |
| 測試四   | $m = 3, n = 3$      | 61       | 61       | 61        |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o ackermann ackermann.cpp
$ ./ackermann
請輸入 m 與 n 的值 (例如 2 2): 2 2

--- 計算結果 ---
遞迴版本 A(2, 2) = 7
非遞迴版本 A(2, 2) = 7
```

### 結論

1. 程式成功同時實現了 Ackermann 函數的遞迴與非遞迴兩種計算方式。
2. 非遞迴版本在僅使用 <iostream> 標頭檔的限制下，利用陣列手動模擬 Stack，達到了與遞迴相同的運算結果。
3. 測試案例驗證了兩種實作方式在小數值輸入下的正確性與一致性。

## 申論及開發報告

### 遞迴的結論

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. 遞迴版本的直覺性

遞迴的寫法能夠直接對應數學定義式，邏輯簡單、易於編寫與驗證，特別適合用來理解 Ackermann 函數的結構。

### 非遞迴的結論

非遞迴版本的必要性（突破限制與防範 Overflow）由於 Ackermann 函數的數值與成長速度極快，系統堆疊深度往往無法負荷較大的 $m$ 與 $n$。透過手動維護陣列堆疊來改寫為非遞迴版本，不僅符合作業僅允許使用 <iostream> 的限制，更能避免系統堆疊溢位（Stack Overflow）的問題。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
