#include "Utility.hpp"
#include <sstream>
#include <cmath>

template <typename T> util::LoopingLinkedList<T>::LoopingLinkedList() {
			head = nullptr;
			tail = nullptr;
			current = nullptr;
			s = 0;
}
template <typename T> util::LoopingLinkedList<T> util::LoopingLinkedList<T>::app(T item) {
	Node* newNode = new Node;
	newNode->data = item;
	newNode->next = nullptr;
	tail = newNode;

	if (head == nullptr) {
		head = newNode;
		newNode->next = head;
		current = head;
	}
	else {
		Node* temp = head;
		while ( temp->next != head ) {
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->next = head;
	}	
	s++;
	return *this;

};

template <typename T> int util::LoopingLinkedList<T>::size() {
	return s;
}

template <typename T> T util::LoopingLinkedList<T>::grab() {
	T value = current->data;
	current = current->next;
	return value;
}

template <typename T> void util::LoopingLinkedList<T>::reset() {
	current = head;
}

util::LoopingLinkedList<int> util::getIncrements(std::vector<int>* basis, int* start) {
	LoopingLinkedList<int> inc;
	std::vector<int> wheel;
	int product = 1;
	unsigned long candidate = 1;
	bool wheelGenerated = false;
	bool pass = true;
	
	// Generate the first "turn" of the wheel
	for (int i : *basis) {
		product *= i; //The product of the basis is used to determine when the first turn is finished
	}
	while (!wheelGenerated) {
		// Starting on 2, we check every number to see if it's divisible by the
		// first handful of primes, or the basis. If it is, we don't need to check
		// it later so it's a fail.
		candidate++;
		for (int prime : *basis) {
			if (candidate % prime == 0) {
				pass = false;
			}
		}
		// If candidate is just the first element + the product, that means we've
		// already finished listing out the first "turn" and we're finished.
		// Otherwise we slap it onto the wheel and go again.
		// THE && OPERATOR SHORT CIRCUITS HERE BY DESIGN
		if (wheel.size() > 2 && candidate == wheel.front() + product) {
			wheelGenerated=true;
		} else if (pass) {
			wheel.push_back(candidate);
		}
		pass = true;
	}
	
	// We need to start at the first part of the wheel when we test, 
	// we'll recreate this process and then take it further for each number 
	// after we get the increments. 
	*start = wheel.front();

	// After the first turn, every subsequent turn is just {wheel}+(product of basis),
	// therefore elements of the wheel are spaced out according to a pattern of
	// increments, which we use our first turn to obtain now.
	for (int i = 0; i < wheel.size() - 1; i++) {
		inc.app(wheel.at(i+1) - wheel.at(i));
	}

	return inc;
}

util::Timekeeper::Timekeeper() {}

void util::Timekeeper::start() {
	begin = std::chrono::high_resolution_clock::now();
}

void util::Timekeeper::stop() {
	end = std::chrono::high_resolution_clock::now();	
}

std::string util::Timekeeper::durationSeconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
	std::ostringstream out;
	out << timeTaken.count();
	return out.str();
}

std::string util::Timekeeper::durationMilliseconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::ostringstream out;
	out << timeTaken.count();
	return out.str();
}

std::string util::Timekeeper::durationMicroseconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::ostringstream out;
	out << timeTaken.count();
	return out.str();
}

std::string util::Timekeeper::durationNanoseconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	std::ostringstream out;
	out << timeTaken.count();
	return out.str();
}

std::string util::Timekeeper::durationAuto() {
	
	std::ostringstream outNs;
	auto timeTakenNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	outNs << timeTakenNs.count();
	if (timeTakenNs.count() < 1000) {
		return outNs.str() + "ns";
	}

	std::ostringstream outUs;
	auto timeTakenUs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	outUs << timeTakenUs.count();
	if (timeTakenUs.count() < 1000) {
		return outUs.str() + "µs";
	}

	std::ostringstream outMs;
	auto timeTakenMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	outMs << timeTakenMs.count();
	if (timeTakenMs.count() < 1000) {
		return outMs.str() + "ms";
	}

	std::ostringstream outS;
	auto timeTakenS  = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
	outS << timeTakenS.count();
	return outS.str() + "s";

}



bool util::isPrimeWheel(long num, int start, std::vector<int>* basis, LoopingLinkedList<int>* increments) {	

	for (int prime : *basis) {
		if (num == prime) {
			return true;
		}

		if (num % prime == 0) {
			return false;
		}
	}
	// Minor performance optimization, a single sqrt() operation beats multiple 
	// i^2 operations when we check values of num as high as we do here	
	int sqrtNum = std::sqrt(num);
	for (long i = start; i <= sqrtNum; i += increments->grab()) {
		if (num % i == 0) {
			increments->reset();
			return false;
		}
	}
	increments->reset();
	return true;
}

bool util::isPrime(long num) {
	if (num == 2) 
		return true;
	if (num < 2 || num % 2 == 0)
		return false;
	for (int i = 3; i*i <= num; i += 2) {
		if (num % i == 0)
			return false;
	}
	return true;
}

std::vector<int> util::genPrimesTo(int max) { 
	std::vector<int> primes;
	for (int i = 2; i <= max; i++) {
		if (util::isPrime(i)) {
			primes.push_back(i);
		}
	}
	return primes;
}

std::vector<int> util::genPrimesCount(int max) {
	std::vector<int> primes;
	int count = 0;
	for (int j = 2; count < max; j++) {
		if (util::isPrime(j)) {
			primes.push_back(j);
			count++;
		}
	}
	return primes;
}

bool util::isPower(int num, int base) {
	if (num < base) {
		return false;
	}
	while (num % base == 0) {
		num = num/base;	
	}
	return num == 1;
}
