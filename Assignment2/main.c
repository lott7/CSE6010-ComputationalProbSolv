// Priority queue using a linked list

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

int main() {
	Item* mypq = Initialize();

	// test cases with empty queue
	Print(mypq);
	printf("Number of flights: %d\n",Count(mypq));
	Remove(mypq);
	printf("Number of Southwest flights: %d\n",CountAirline(mypq,'S'));

	int mypriority1 = 1225;
	printf("Number of flights earlier/later than %d: %d, %d\n",mypriority1,
		CountEarlier(mypq,mypriority1),CountLater(mypq,mypriority1));

	// test cases without errors
	int returnval;
	returnval = Add(mypq,'S',1402,2317);

	returnval = Add(mypq,'S',-1402,2317);
	if(returnval == 1) printf("Error adding to pq\n");
	returnval = Add(mypq,'S',1402,-2317);
	if(returnval == 1) printf("Error adding to pq\n");

	returnval = Add(mypq,'C',70,1043);
	returnval = Add(mypq,'S',201,500);
	returnval = Add(mypq,'D',1691,1601);

	printf("Number of flights: %d\n",Count(mypq));
	printf("Number of Southwest flights: %d\n",CountAirline(mypq,'S'));
	printf("Number of Delta flights: %d\n",CountAirline(mypq,'D'));

	int flighttest = 100;
	printf("Number of flight numbers smaller/larger than %d: %d, %d\n",flighttest,
		CountSmaller(mypq,flighttest),CountLarger(mypq,flighttest));

	int mypriority2 = 1200;
	printf("Number of flights earlier/later than %d: %d, %d\n",mypriority2,
		CountEarlier(mypq,mypriority2),CountLater(mypq,mypriority2));
	
	Print(mypq);
	Remove(mypq);
	Print(mypq); 

	Finalize(mypq);
	// Print(mypq); 
	free(mypq);

	return 0;
}
