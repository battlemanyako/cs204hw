#include <iostream>
#include <mutex>
#include <random>
#include <time.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>

#include "HW8DynIntQueue.h"

using namespace std;

HW8DynIntQueue Queue;

mutex QueueMutex, CoutMutex;
int TotalCustomers;

int random_range(const int & min, const int & max) {
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void FunctionCustomers(const int & total_customer_count, const int & min_arrival, const int & max_arrival) {
	time_t tt;
	struct tm *ptm;
	int size;
	for(int count = 1; count < total_customer_count + 1; count++) {
		QueueMutex.lock();
		Queue.enqueue(count);
		size = Queue.getCurrentSize();
		QueueMutex.unlock();

		CoutMutex.lock();

		tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		ptm = new struct tm; 
		localtime_s(ptm, &tt);
		cout << "New customer with ID " << count << " has arrived (queue size is " << size << "): " << put_time(ptm,"%X") << endl;
		CoutMutex.unlock();
		delete ptm;
		this_thread::sleep_for(chrono::seconds(random_range(min_arrival, max_arrival)));
	}
}

void FunctionCashier(const int & cashierID, const int & total_customer_count, const int & cashier2_threshold, const int & min_checkout_time, const int & max_checkout_time) {
	time_t tt;
	struct tm *ptm;
	int size;
	this_thread::sleep_for(chrono::seconds(random_range(min_checkout_time, max_checkout_time)));
	while(TotalCustomers < total_customer_count) {
		
		if(cashierID == 1) {
			int id;
			if(!Queue.isEmpty()) {
					QueueMutex.lock();
					if(!Queue.isEmpty()){
						Queue.dequeue(id);
						TotalCustomers++;
						size = Queue.getCurrentSize();
						QueueMutex.unlock();

						CoutMutex.lock();
						tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
						ptm = new struct tm; 
						localtime_s(ptm, &tt);
						cout << "Cashier " << cashierID << " started transaction with customer "<< id << " (queue size is " << size << " ): " << put_time(ptm,"%X") << endl;

						CoutMutex.unlock();
						delete ptm;

						this_thread::sleep_for(chrono::seconds(random_range(min_checkout_time, max_checkout_time)));

						CoutMutex.lock();
						tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
						ptm = new struct tm; 
						localtime_s(ptm, &tt);
						cout << "Cashier " << cashierID << " finished transaction with customer "<< id << " " << put_time(ptm,"%X") << endl;

						CoutMutex.unlock();
						delete ptm;
				}
					else{
						QueueMutex.unlock();
					}
			}
		}
		else { // cashierID == 2
			int id;
			if(Queue.getCurrentSize() >= cashier2_threshold) {
				QueueMutex.lock();
				if(!Queue.isEmpty()) {
					Queue.dequeue(id);
					TotalCustomers++;
					size = Queue.getCurrentSize();
					QueueMutex.unlock();

					CoutMutex.lock();
					tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
					ptm = new struct tm; 
					localtime_s(ptm, &tt);
					cout << "Cashier " << cashierID << " started transaction with customer "<< id << " (queue size is " << size << " ): " << put_time(ptm,"%X") << endl;

					CoutMutex.unlock();
					delete ptm;

					this_thread::sleep_for(chrono::seconds(random_range(min_checkout_time, max_checkout_time)));

					CoutMutex.lock();
					tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
					ptm = new struct tm; 
					localtime_s(ptm, &tt);
					cout << "Cashier " << cashierID << " finished transaction with customer "<< id << " " << put_time(ptm,"%X") << endl;

					CoutMutex.unlock();
					delete ptm;
				}
				else {
					QueueMutex.unlock();
				}
			}
		}
	}
}


int main() {
	
	int total_customer_count;
	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count;
	int cashier2_threshold;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_threshold;
	int min_arrival, max_arrival;
	cout << "Please enter the inter-arrival time range between two customers:" << endl;
	cout << "Min: ";
	cin >> min_arrival;
	cout << "Max: ";
	cin >> max_arrival;
	int min_checkout_time, max_checkout_time;
	cout << "Please enter the checkout time range of cashiers:" << endl;
	cout << "Min: ";
	cin >> min_checkout_time;
	cout << "Max: ";
	cin >> max_checkout_time;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt);
	cout << "Simulation starts " << put_time(ptm,"%X") << endl;
	delete ptm;

	thread customers(FunctionCustomers,total_customer_count, min_arrival, max_arrival);
	thread cashier1(FunctionCashier, 1, total_customer_count, cashier2_threshold, min_checkout_time, max_checkout_time);
	thread cashier2(FunctionCashier, 2, total_customer_count, cashier2_threshold, min_checkout_time, max_checkout_time);

	customers.join();
	cashier1.join();
	cashier2.join();
	
	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	
	ptm = new struct tm; 
	localtime_s(ptm, &tt);
	cout << "End of the simulation ends: " << put_time(ptm,"%X") << endl;
	delete ptm;

	return 0;
}