#include <vector>
#include <chrono>
#include <iostream>

#ifndef UTILITY_H
#define UTILITY_H

namespace util {

	template <typename T>
	class LoopingLinkedList { 
		struct Node {
			T data;
			Node* next;
		};
		private:
			Node* head;
			Node* tail;
			Node* current;
			int s;
		public:
			LoopingLinkedList();
			LoopingLinkedList app(T);
			T grab();
			int size();
			void reset();
	};

	class Timekeeper {
		private:
			std::chrono::system_clock::time_point begin;
			std::chrono::system_clock::time_point end;
		public: 
			Timekeeper();
			void start();
			void stop();
			void printDurationSeconds();
			void printDurationMilliseconds();
			void printDurationMicroseconds();
			void printDurationNanoseconds();
	};


	LoopingLinkedList<int>* getIncrements(std::vector<int>*, int*);

	bool isPrimeWheel(long, int, std::vector<int>*, LoopingLinkedList<int>*);

	bool isPrime(long);

	std::vector<int>* genPrimesTo(int);

	std::vector<int>* genPrimesCount(int);

	bool isPower(int num, int base);

}

#endif
