#include "../Utility.hpp" 

int main() {
	util::Filekeeper file = util::Filekeeper("test.txt");
	util::Timekeeper time = util::Timekeeper();
	
	time.start();
	std::cout << "First line: " << std::endl << file.grabLine() << std::endl;
	std::cout << "First line again: " << std::endl << file.grabLine() << std::endl;
	file.nextLine();
	std::cout << "Second line: " << std::endl << file.grabLine() << std::endl;
	file.nextLine(3); 
	std::cout << "Fifth line: " << std::endl << file.grabLine() << std::endl;
	std::cout << "Fifth line again: " << std::endl << file.grabLine() << std::endl;
	file.reset();
	std::cout << "First line again: " << std::endl << file.grabLine() << std::endl;
	file.nextLine(2);
	std::cout << "Third line: " << std::endl << file.grabLine() << std::endl;
	file.backLine();
	std::cout << "Second line again: " << std::endl << file.grabLine() << std::endl;
	file.nextLine(2);
	std::cout << "Fourth line: " << std::endl << file.grabLine() << std::endl;
	file.backLine(3);
	std::cout << "First line one final time: " << std::endl << file.grabLine() << std::endl;
	time.stop();
	std::cout << "Time elapsed (auto): " << time.durationAuto() << std::endl;
	std::cout << "Time elapsed (seconds): " << time.durationSeconds() << std::endl;
	std::cout << "Time elapsed (milliseconds): " << time.durationMilliseconds() << std::endl;
	std::cout << "Time elapsed (microseconds): " << time.durationMicroseconds() << std::endl;
	std::cout << "Time elapsed (nanoseconds): " << time.durationNanoseconds() << std::endl;

}

