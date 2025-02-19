#include <stdio.h>
#include <stdlib.h>

void readInputFile(const char *filename, int *numProcesses, int *numResourceTypes, int **E, int ***C, int ***R);
int detectDeadlock(int numProcesses, int numResourceTypes, int *E, int **C, int **R, int *deadlockedProcesses);

int main() {
    const char *filename = "input.txt";
    int numProcesses, numResourceTypes;
    int *E;
    int **C, **R;

    readInputFile(filename, &numProcesses, &numResourceTypes, &E, &C, &R);

    int *deadlockedProcesses = (int *)malloc(numProcesses * sizeof(int));
    int deadlockDetected = detectDeadlock(numProcesses, numResourceTypes, E, C, R, deadlockedProcesses);

    if (deadlockDetected) {
        printf("Deadlock detected. Deadlocked processes: ");
        for (int i = 0; i < numProcesses; i++) {
            if (deadlockedProcesses[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    } else {
        printf("No deadlock detected.\n");
    }

    free(E);
    for (int i = 0; i < numProcesses; i++) {
        free(C[i]);
        free(R[i]);
    }
    free(C);
    free(R);
    free(deadlockedProcesses);

    return 0;
}

void readInputFile(const char *filename, int *numProcesses, int *numResourceTypes, int **E, int ***C, int ***R) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", numProcesses, numResourceTypes);

    *E = (int *)malloc(*numResourceTypes * sizeof(int));
    for (int i = 0; i < *numResourceTypes; i++) {
        fscanf(file, "%d", &(*E)[i]);
    }

    *C = (int **)malloc(*numProcesses * sizeof(int *));
    for (int i = 0; i < *numProcesses; i++) {
        (*C)[i] = (int *)malloc(*numResourceTypes * sizeof(int));
        for (int j = 0; j < *numResourceTypes; j++) {
            fscanf(file, "%d", &(*C)[i][j]);
        }
    }

    *R = (int **)malloc(*numProcesses * sizeof(int *));
    for (int i = 0; i < *numProcesses; i++) {
        (*R)[i] = (int *)malloc(*numResourceTypes * sizeof(int));
        for (int j = 0; j < *numResourceTypes; j++) {
            fscanf(file, "%d", &(*R)[i][j]);
        }
    }

    fclose(file);
}

int detectDeadlock(int numProcesses, int numResourceTypes, int *E, int **C, int **R, int *deadlockedProcesses) {
    int *work = (int *)malloc(numResourceTypes * sizeof(int));
    int *finish = (int *)malloc(numProcesses * sizeof(int));

    for (int i = 0; i < numResourceTypes; i++) {
        work[i] = E[i];
        for (int j = 0; j < numProcesses; j++) {
            work[i] -= C[j][i];
        }
    }

    for (int i = 0; i < numProcesses; i++) {
        finish[i] = 0;
    }

    int deadlockDetected = 0;
    for (int i = 0; i < numProcesses; i++) {
        if (!finish[i]) {
            int canProceed = 1;
            for (int j = 0; j < numResourceTypes; j++) {
                if (R[i][j] > work[j]) {
                    canProceed = 0;
                    break;
                }
            }
            if (canProceed) {
                for (int j = 0; j < numResourceTypes; j++) {
                    work[j] += C[i][j];
                }
                finish[i] = 1;
                i = -1;
            }
        }
    }

    for (int i = 0; i < numProcesses; i++) {
        if (!finish[i]) {
            deadlockedProcesses[i] = 1;
            deadlockDetected = 1;
        } else {
            deadlockedProcesses[i] = 0;
        }
    }

    free(work);
    free(finish);

    return deadlockDetected;
}
