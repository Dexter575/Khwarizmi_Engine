#include "stop_watch/stop_watch.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout<<"[KE:: Initializing.....]"<<std::endl;

	ke::StopWatch stop_watch;
    stop_watch.start();

	while(1) {
		std::cout<<"Setup: "<<stop_watch.elapsed(ke::StopWatch::DurationTypeEnum::MILLI_SECONDS) * 1e-3f<<std::endl;
	}

	std::cout<<"[KE:: Initializing.....]"<<std::endl;
	return 0;
}