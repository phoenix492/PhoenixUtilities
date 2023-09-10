#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>

#pragma once

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
			std::string durationSeconds();
			std::string durationMilliseconds();
			std::string durationMicroseconds();
			std::string durationNanoseconds();
			std::string durationAuto();
	};

	// Filekeeper manages an ifstream to make it behave more like a "point and
	// select" type tool, advancing lines and characters manually then get()ing 
	// desired text and moving back in the stream to before the get().
	class Filekeeper {
		private:
			std::ifstream file;
			std::string filePath;
			int line;
		public:
			Filekeeper(std::string);
			void reset();
			void backLine(int = 1);
			void nextLine(int = 1);
			std::string grabLine();
			char grabNthChar(int);
			std::string grabCharNtoM(int, int);
			bool eof();
	};


	LoopingLinkedList<int> getIncrements(std::vector<int>*, int*);

	bool isPrimeWheel(long, int, std::vector<int>*, LoopingLinkedList<int>*);

	bool isPrime(long);

	std::vector<int> genPrimesTo(int);

	std::vector<int> genPrimesCount(int);

	bool isPower(int num, int base);

}
