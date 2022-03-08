#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <cstring>
#include <chrono>

int main ()
{
    int count = 0,exit_cnt = 0;
   using namespace boost::interprocess;
   using Clock = std::chrono::high_resolution_clock;
   try{
        //Erase previous shared memory
        shared_memory_object::remove("shared_memory");
        shared_memory_object::remove("feedback");

        //Create a shared memory object.
        shared_memory_object shm (create_only, "shared_memory", read_write);
        shared_memory_object shm_feedback (create_only, "feedback", read_write);
        
        //Set size
        shm.truncate(1000);
        //Set size
        shm_feedback.truncate(1000);

        //Map the whole shared memory in this process
        mapped_region region(shm, read_write);
        mapped_region region_fd(shm_feedback, read_write);
        std::cout << "Mapped Shared memory... wait for feedback" << std::endl;
        while(1)
        {
            shared_memory_object shm (open_only, "feedback", read_only);
            const char *mem = static_cast<char*>(region_fd.get_address());
            for(std::size_t i = 0; i < region.get_size(); ++i){
            //Write all the memory to 1
            std::memset(region.get_address(), count, region.get_size());
            }
            count ++;
            if(count  > 99)
            {
                count = 0;
                exit_cnt++;
                
            }
            if(*mem  != NULL)
            {
                constexpr auto num = Clock::period::num;
                constexpr auto den = Clock::period::den;
                std::cout << Clock::now().time_since_epoch().count()
                << " [" << num << '/' << den << "] units since epoch\n";
                std::cout << "Feedback memory read" << std::endl;
                break;
            }
        }
        
   }
   catch(interprocess_exception &ex){
      shared_memory_object::remove("shared_memory");
      std::cout << ex.what() << std::endl;
      return 1;
   }
   return 0;
}