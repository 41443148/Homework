#include <iostream>

using namespace std;

void generateSubsets(const char S[], int n, int index, char current[], int currentSize) {
    if (index == n) {
        cout << "(";
        for (int i = 0; i < currentSize; ++i) {
            cout << current[i];
            if (i + 1 < currentSize) {
                cout << ",";
            }
        }
        cout << "), ";
        return;
    }

    generateSubsets(S, n, index + 1, current, currentSize);

    current[currentSize] = S[index];
    generateSubsets(S, n, index + 1, current, currentSize + 1);
}

int main() {
    char S[] = {'a', 'b', 'c'};
    int n = 3;

  
    char current[3];

    cout << "powerset(S) = { ";
    generateSubsets(S, n, 0, current, 0);
    cout << "}" << endl;

    return 0;
}
