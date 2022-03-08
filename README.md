# SharedMemoryExample

Server.cpp
- Create shared memory **Output** and **Feedback**
- write **1 - 100** incrementally in memory **Output** in a while loop (overwrites previous value on every write)
- Reads **Feedback** memory continously in while loop
- Breaks while loop when finds some data available in **Feedback** memory and print timestamp

Client.cpp
- Read shared memory **Output** in while loop
- When finds value **98** in memory **Output** breaks while loop write value **1** in memory **Feedback** and print timestamp

Compiler
- g++
