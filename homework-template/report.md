# 41443148

作業一

## 解題說明

Ackermann 函數 $A(m,n)$ 是一個典型的雙變數非原始遞迴函數（Non-primitive recursive function）
當 $m = 0$ 時，結果為 $n + 1$。
當 $n = 0$ 時，結果等同於 $A(m - 1, 1)$
其餘情況下，結果為 $A(m - 1, A(m, n - 1))$

### 解題策略

1.遞迴函式設計：
根據 Ackermann 函數的數學定義進行遞迴拆解：
n+1 if m=0
A(m-1,1) if n=0
A(m-1,A(m,n-1)) otherwise
2.由於 Ackermann 函數遞迴深度極深，容易造成系統堆疊溢位（Stack Overflow），且受限於僅能使用 <iostream> 標頭檔，本程式採用自定義靜態陣列模擬堆疊（Stack）的方式，以 while 迴圈迭代取代直接的函式遞迴。  
3. 主程式提供介面讓使用者輸入 $m$ 與 $n$，並分別呼叫遞迴與非遞迴版本進行計算與結果比對。

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
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
