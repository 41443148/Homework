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
