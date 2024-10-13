#include "stop_watch/stop_watch.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout<<"[KE:: Initializing.....]"<<std::endl;



	ke::StopWatch swGlobal;

    swGlobal.start();

while(1) {

std::cout<<"Setup: "<<swGlobal.elapsed(ke::StopWatch::DurationTypeEnum::MILLI_SECONDS) * 1e-3f<<std::endl;
    
}
	   

	return 0;
}