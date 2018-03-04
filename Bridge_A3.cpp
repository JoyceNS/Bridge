#include <pthread.h>
#include <thread>
#include <string.h>
#include <istream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sstream>
using namespace std; 

static int max_weight;//maximum weight that can be on bridge
static int bridgeLoad;//curent load that is on bridge



/// MADE THEM "GLOBAL" AND CHANGE THE NAME OF MUTEXT FROM ACCESSS to whatever. I did the same
// and it doesn't let u use it because "access" is a reserved word for something else 
static pthread_mutex_t bridge_lock = PTHREAD_MUTEX_INITIALIZER; //create lock/bridge/mutex
static pthread_cond_t ok = PTHREAD_COND_INITIALIZER;//create condition variable

struct Vehicle{
	int cross_t;
	int load;
	int elap_t;
	string l_plate;
};

void enterBridge(int weight){
	//cout<< "enter bridge funct" <<endl;
	//while(wfree < weight)
		//notfull.wait;
	pthread_mutex_lock(&bridge_lock);
	//cout<< "before the while loop in enterbridge()"<< endl;
	while(!((weight + bridgeLoad) <= max_weight)){
		//cout<< "the while loop that could be my problem" << endl;
		pthread_cond_wait(&ok, &bridge_lock);
	}
	bridgeLoad += weight;
	//pthread_mutex_unlock(&bridge_lock);
}
void leaveBridge(int weight){
	//cout<< "enter leave bridge"<< endl;
	pthread_mutex_lock(&bridge_lock);
	bridgeLoad = bridgeLoad - weight;
	//ok.signal();
}
void *vehicle(void *arg){// should call enter and leave bridge from within this function ideally
	//int i = (int) arg;//NOT SURE ABOUT THIS LINE; WHAT IS INT?? MY arg IS A STRUCT
	//free(i);
	//cout<< "enter vehicle function" <<endl;
	Vehicle *i = (Vehicle *) arg;
	//cout << "Vehicle " << i->l_plate << " goes on bridge."<< endl;
	cout << "Vehicle " << i->l_plate << " arrives at bridge."<< endl;
	cout << "The current bridge load is " << bridgeLoad << " tons."<< endl;
	//if statement for if vehicle exceeds load UGHHH
	if(i->load <= max_weight){
		enterBridge(i->load);
		cout << "Vehicle " << i->l_plate << " goes on bridge."<< endl;
		cout << "The current bridge load is " << bridgeLoad << " tons."<< endl;
			pthread_cond_signal(&ok);
	pthread_mutex_unlock(&bridge_lock);
		sleep(i->cross_t);
		leaveBridge(i->load);
		cout << "Vehicle " << i->l_plate << " leaves the bridge."<< endl;
		cout << "The current bridge load is " << bridgeLoad << " tons."<< endl;
		pthread_cond_signal(&ok);
		pthread_mutex_unlock(&bridge_lock);

	}
	else
		cout <<"Vehicle " << i->l_plate << " exceeds the maximum bridge load" << endl;
	pthread_exit(NULL);
}//child child_thread



int main(int argc, char **argv){
	//int t = 0;
	pthread_mutex_init(&bridge_lock, NULL);
	string input, license;
	int elapsed, weight, cross_time, maxchildren;
	maxchildren = 64;
	max_weight = atoi(argv[1]);

	cout<< "Maximum bridge load is " << max_weight << " tons." << endl;
	
	pthread_t child[maxchildren];// highest will be 64
	Vehicle cars[64]; // u can switch to cars[maxchildren] again my thing didnt run it like that for some reason
	int i = 0;
	while(cin >> license){
		cin >> elapsed;
		cin >> weight;
		cin >> cross_time;

		if(i == 63)
			break;
		
		//stringstream ss(input);
		//ss >> license >> elapsed >> weight >> cross_time;

		cars[i].l_plate = license;
		cars[i].elap_t = elapsed;
		cars[i].load = weight;
		cars[i].cross_t = cross_time;

		

		sleep(cars[i].elap_t);
		//pthread_t tid;//creates thread id // UR DOING THIS TWICE DO NOT NEED
		pthread_create(&child[i], NULL, vehicle, (void *) &cars[i]); //childthread or vehicle

		i++;
		
	}
	//sleep(50);
	
	for (int j = 0; j < i; j++)
	{
		pthread_join(child[j],NULL);
	}

	cout << endl;
	cout << "Total number of vehicles: " << i << endl;


	return 0;
	//create child thread
			//Print a message "arrived at bridge"
			//Wait until it can get on the bridge
				//check if it exceeds the max weight
			//Print a message "on bridge"

			//for(i = 0; i < nchildren; i++)
			//pthread_join(child[i], NULL);
			
			//Sleep for crossing_time seconds
			//Print a message
			//Signal a vehicle has left
}

/* if bridge is full then no cars can cross 
until a car leaves the bridge based on the 
time it takes it to cross*/

/*#############################################################################################*/


/*struct Bridge{
	private static int wfree; // bridge is full when wfree == 0
	private condition notfull;// condition variable
	void *child_thread(void *arg){//////////////////////
		int i;
		i = (int) arg;				/////// is a struct needed
	}//child child_thread              //////////for this function????
	public synchronized void enterBridge(int weight){
		while(wfree < weight)
			notfull.wait;
		wfree -= weight;
	}//arrive
	void leaveBridge(int weight){
		wfree += weight;
		notfull.signal;
	}//leave
	void Bridge(int max_weight){
		wfree = max_weight;
	}//contructor?????
};// Bridge struct
*/
