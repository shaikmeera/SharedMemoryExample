#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <cstring>
#include <chrono>

int main ()
{
    int value;
   using namespace boost::interprocess;
   using Clock = std::chrono::high_resolution_clock;
   
   try{
    while(1){
        //Open already created shared memory object.
        shared_memory_object shm (open_only, "shared_memory", read_only);
        shared_memory_object shm_feedback (open_only, "feedback", read_write);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_only);
        mapped_region region_fd(shm_feedback, read_write);

        //Check that memory was initialized to 1
        const char *mem = static_cast<char*>(region.get_address());
        for(std::size_t i = 0; i < region.get_size(); ++i){
            value = *mem;
            //  if(*mem++ != 1){
            //     std::cout << "Error checking memory!" << std::endl;               
            //     return 1;
            //  }
        }
        if(value == 98)
            {
                constexpr auto num = Clock::period::num;
                constexpr auto den = Clock::period::den;
                std::cout << "Read from shared memory!" << std::endl;
                std::memset(region_fd.get_address(), 1, region_fd.get_size());
                std::cout << Clock::now().time_since_epoch().count()
                << " [" << num << '/' << den << "] units since epoch\n";
                std::cout << "Feedback memory written!" << std::endl;
                break;
            }
        }
   }
   catch(interprocess_exception &ex){
      std::cout << "Unexpected exception: " << ex.what() << std::endl;
      shared_memory_object::remove("shared_memory");
      return 1;
   }

//    shared_memory_object::remove("shared_memory");
   return 0;
}