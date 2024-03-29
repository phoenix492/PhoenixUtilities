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
	return std::to_string(timeTaken.count()) + "s";
}

std::string util::Timekeeper::durationMilliseconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	return std::to_string(timeTaken.count()) + "ms";
}

std::string util::Timekeeper::durationMicroseconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	return std::to_string(timeTaken.count()) + "μs";
}

std::string util::Timekeeper::durationNanoseconds() {
	auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	return std::to_string(timeTaken.count()) + "ns";
}

std::string util::Timekeeper::durationAuto() {
	
	auto timeTakenNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	if (timeTakenNs.count() < 1000) {
		return std::to_string(timeTakenNs.count()) + "ns";
	}

	auto timeTakenUs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	if (timeTakenUs.count() < 1000) {
		return std::to_string(timeTakenUs.count()) + "µs";
	}

	auto timeTakenMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	if (timeTakenMs.count() < 1000) {
		return std::to_string(timeTakenMs.count()) + "ms";
	}

	auto timeTakenS  = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
	return std::to_string(timeTakenS.count()) + "s";

}

util::Filekeeper::Filekeeper(std::string filePath) {
	this->filePath = filePath;
	file.open(filePath);
	line = 1;
}

void util::Filekeeper::reset() {
	file.close();
	file.open(filePath);
	line = 1;
}

void util::Filekeeper::backLine(int count) {
	int targetLine = line - count;
	this->reset();
	// We're *at* the first line, so we need to skip lines up to but NOT
	// including the target line
	nextLine(targetLine - 1);
}

void util::Filekeeper::nextLine(int count) {
	for (int i = 0; i < count; i++) { 
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		line++;
	}
}

std::string util::Filekeeper::grabLine() {
	std::string grabbedLine; 
	std::getline(file, grabbedLine);
	line++;
	backLine();
	return grabbedLine;
}

char util::Filekeeper::grabNthChar(int n) {
	for (int i = 0; i < n - 1; i++) {
		file.ignore(1);
	}

	char nthChar = file.get();
	for (int i = n; i > 0; i--) {
		file.unget();
	}

	return nthChar;
}

std::string util::Filekeeper::grabCharNtoM(int n, int m) {
	for (int i = 0; i < n - 1; i++) {
		file.ignore(1);
	}

	std::string charNtoM = "";
	for (int i = n; i < m + 1; i ++) {
		charNtoM += file.get();
	}

	for (int i = m; i > 0; i--) {
		file.unget();
	}
	
	return charNtoM;
}

bool util::Filekeeper::eof() {
	return file.eof();
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
	long numSqrt = std::sqrt(num);
	for (int i = 3; i <= numSqrt; i += 2) {
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
