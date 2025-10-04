#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20  // Maximum number of states

char states[MAX][20];         // List of states
int n;                        // Number of states
int visited[MAX];             // Visited array for DFS

int eTransition[MAX][MAX];    // Epsilon transitions (adjacency matrix)

// Get index of a state in the states array
int getStateIndex(char *s) {
    for (int i = 0; i < n; i++)
        if (strcmp(states[i], s) == 0) return i;
    return -1;
}

// DFS to compute epsilon closure
void dfs(int state, int closure[]) {
    if (visited[state]) return;
    visited[state] = 1;
    closure[state] = 1;

    for (int i = 0; i < n; i++) {
        if (eTransition[state][i]) {
            dfs(i, closure);
        }
    }
}

// Compute and print epsilon closure for a given state
void computeEpsilonClosure(char *start) {
    int closure[MAX] = {0};
    memset(visited, 0, sizeof(visited));

    int idx = getStateIndex(start);
    if (idx == -1) {
        printf("Invalid state %s\n", start);
        return;
    }

    dfs(idx, closure);

    printf("Epsilon closure of %s = {", start);
    for (int i = 0; i < n; i++) {
        if (closure[i]) printf(" %s", states[i]);
    }
    printf(" }\n");
}

int main() {
    FILE *INPUT = fopen("input.txt", "r");
    if (!INPUT) {
        printf("Error opening input.txt\n");
        return 1;
    }

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter the states:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", states[i]);

    // Read epsilon transitions from file
    char state1[20], input[3], state2[20];
    while (fscanf(INPUT, "%s %s %s", state1, input, state2) != EOF) {
        if (strcmp(input, "e") == 0) {
            int from = getStateIndex(state1);
            int to = getStateIndex(state2);
            if (from != -1 && to != -1) eTransition[from][to] = 1;
        }
    }

    // Compute epsilon closure for each state
    for (int i = 0; i < n; i++) {
        computeEpsilonClosure(states[i]);
    }

    fclose(INPUT);
    return 0;
}