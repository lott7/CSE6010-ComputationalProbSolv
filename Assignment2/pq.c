// Typedef and function definitions for PQ
#include <stdio.h>
#include <stdlib.h>

typedef struct flightinfo {
	char airline; 		// use U for United, D for Delta, A for American, S for Southwest
	int flightnumber;
	int time;
} Flightinfo;

typedef struct item {
	Flightinfo flight;
	int* priority; // priority is a pointer to an int, will point to flighttime
	struct item * next; // pointer to the next item in the priority queue
} Item;


Item* Initialize() {
	// Create a dummy node
	Item* dummyNode = (Item*) malloc(sizeof(Item));

	if (dummyNode == NULL) { // memory allocation failed; return NULL
		printf("Memory allocation failed!\n");
		return NULL; 
	}

	Flightinfo dummyFlight = { // initialize the dummy node with given default values
		' ', // airline
		-1, // flightnumber
		-1 // time
	};
	dummyNode->flight = dummyFlight;
	dummyNode->priority = &(dummyNode->flight.time); // pointer to the the time field of the dummyFlight
	dummyNode->next = NULL;

	return dummyNode;
}


int Add(Item* mypq, char itemAirline, int itemFlightnumber, int itemTime) {
	if (itemFlightnumber > 0 && itemTime > 0) { // Check for invalid cases	   	
		Item* newFlight = (Item*)malloc(sizeof(Item)); // Create a new item to add to the PQ

    	if (newFlight == NULL) { // Memory allocation failed; return failure
			printf("Memory allocation failed!\n");
        	return 1; 
    	}

		// Initialize the new item with the given function values
		newFlight->flight.airline = itemAirline;
		newFlight->flight.flightnumber = itemFlightnumber;
		newFlight->flight.time = itemTime;
		newFlight->priority = &(newFlight->flight.time);
		newFlight->next = NULL;

		// Insert the new node before the head node
		if (itemTime < *(mypq->priority)) {  
			// printf("The head node has been changed!\n");
			newFlight->next = mypq;
			mypq = newFlight;
		} else {

		// Traverse the PQ to find the appropriate position for insertion
		while (mypq->next != NULL && itemTime > *(mypq->next->priority)) {
			mypq = mypq->next;
		}
		        
		// Insert the new item into the PQ
		newFlight->next = mypq->next;
		mypq->next = newFlight;
		return 0; // Successful insertion; return success
		}
	} else { // invalid case occured!
		return 1; // Unsuccessful insertion; return failure
	}
}


void Remove(Item* mypq) {
	if (mypq->next == NULL) { // priority queue is empty; return NULL
		printf("Priority queue is empty!\n");
		return; 
	} else {
		// Remove the node with the highest priority
		Item* firstNode = mypq->next; // skipping the head node
		mypq->next = mypq->next->next; // resolve the linked-list connections
		free(firstNode);
	}
}


void Print(Item* mypq) {
	if (mypq->next == NULL) {
		printf("Priority queue is empty!\n");
		return;

	} else {
		Item* current = mypq; // ->next; (skip the dummyNode) // Start with the first item
		while (current != NULL) {
			printf("Priority queue contents:\n");
			printf("%c %d %d\n",current->flight.airline, 
					current->flight.flightnumber, current->flight.time);
			current = current->next; // Move to the next item
		}
	}
}


int Count(Item* mypq) {
	Item* current = mypq; // Start with the first item
	int count = 0;

	while (current->next != NULL) {
		count++;
		current = current->next; // Move to the next item
	}
	return count;
}


int CountAirline(Item* mypq, char myairline) {
	if (mypq == NULL) { // priority queue is empty; return NULL
		return 0;
	} else {
		Item* current = mypq; // Start with the first item
		int count = 0;

		while (current != NULL) {
			if (current->flight.airline == myairline) {
				count++;
			}
			current = current->next; // Move to the next item
		}
		return count;
	}
}


int CountSmaller(Item* mypq, int itemflightnumber) {
	if (mypq == NULL) { // priority queue is empty; return NULL
		return 0;
	} else {
		Item* current = mypq->next; // Start with the first item
		int count = 0;

		while (current != NULL) {
			if (current->flight.flightnumber < itemflightnumber) {
				count++;
			}
			current = current->next; // Move to the next item
		}
		return count;
	}
}


int CountLarger(Item* mypq, int itemflightnumber) {
	if (mypq == NULL) { // priority queue is empty; return NULL
		return 0;
	} else {
		Item* current = mypq->next; // Start with the first item
		int count = 0;

		while (current != NULL) {
			if (current->flight.flightnumber > itemflightnumber) {
				count++;
			}
			current = current->next; // Move to the next item
		}
		return count;
	}
}


int CountEarlier(Item* mypq, int mypriority) {
	if (mypq == NULL) { // priority queue is empty; return NULL
	return 0;
	} else {
		Item* current = mypq->next; // Start with the first item
		int count = 0;
		
		while (current != NULL) {
			// if (*(current->priority) > mypriority) { 
			if (current->flight.time < mypriority) { // alternative way above
				count++;
			}
			current = current->next; // Move to the next item
		}
		return count;
	}
}


int CountLater(Item* mypq, int mypriority) {
	if (mypq == NULL) { // priority queue is empty; return NULL
	return 0;
	} else {
		Item* current = mypq->next; // Start with the first item
		int count = 0;

		while (current != NULL) {
			if (*(current->priority) > mypriority) { // alternative way below
			// if (current->flight.time > mypriority) {
				count++;
			}
			current = current->next; // Move to the next item
		}
		return count;
	}
}

void Finalize(Item* mypq) {
    if (mypq == NULL) {
		printf("Priority queue is empty!\n");
        return; // priority queue is empty; return
    }

	// Skipping the dummy node at the head of the linked-list
	Item* current = mypq->next;

	// Free the rest of the nodes
    while (current != NULL) {
        Item* temp = current;
        current = current->next;
		free(temp);
    }
}

