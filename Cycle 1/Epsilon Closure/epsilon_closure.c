#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char result[20][20]; // To store the closure result 
char copy[3];        // Holds the current state being processed
char states[20][20]; // To store the states data

void addState(char a[20], int i) {
	strcpy(result[i], a);
}

void display(int n) {
    int k = 0;
    
    printf("\nEpsilon closure of %s = {", copy);
    while (k < n) {
        printf(" %s", result[k]);
        k++;
    }
    printf(" }\n");
}

int main() {
	FILE *INPUT;
    INPUT = fopen("input.txt", "r");
    	
    // File reading variables
    char state1[3]; // Source state
    char input[3];  // Transition Element
    char state2[3]; // Destination state
    	
    char state[3];  // Store Current Processing State
	int n;          // No. of States
	
	printf("\nEnter The Number of States: ");
	scanf("%d", &n);
	
	printf("\nEnter The States: \n");
	for (int k = 0; k < n; k++){
    		scanf("%s", states[k]);
	}
	
	for (int k = 0; k < n; k++) {
		int i = 0; 		    // Counter for states in epsilon closure for each variable
    	strcpy(state, states[k]);   // Mark current processing state
    	strcpy(copy, state);	    // Mark current processing state for displaying
    	addState(state, i++);
    		
    	while (1) {
    		int end = fscanf(INPUT, "%s %s %s", state1, input, state2);
    		if (end == EOF) break;
    			
    		if ((strcmp(state, state1) == 0) && (strcmp(input, "e") == 0)){
                		addState(state2, i++);
                		strcpy(state, state2);  // Move on to check epsilon transitions from new state
            	}
    	}
    		
    	display(i);
    	rewind(INPUT);
    }
	
	fclose(INPUT);
	return 0;
}


/*
Enter The Number of States: 3

Enter The States: 
q0
q1
q2

Epsilon closure of q0 = { q0 q1 q2 }

Epsilon closure of q1 = { q1 q2 }

Epsilon closure of q2 = { q2 }

*/
