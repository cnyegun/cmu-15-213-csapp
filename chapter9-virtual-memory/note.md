# Why virtual memory exist
- For UX: easier for developer to reason about memory by providing a simplified model of memory
- For safety: processess don't accidentally edit a memory segment of another process and created buggy mess

# Physical and virtual addressing

1. Physical address
- The main memory of a computer system is a array of bytes, each has its own address, started from 0.
- The CPU send down physical address to the memory over memory bus and then get the data back.
- Early PCs and microcontroller still work with physical address.

2. Virtual address
- The CPU access the memory through virtual address, which need to be converted to physical address
and then sent down to the main memory to get the data back.
- The process is called address translation. The system have a unit for doing that called MMU.

# Address spaces
- Is the ordered set of address available.
- Eg: on 32bit system, the address spaces are {0, 1, ..., 2^32 - 1}.

# VM as a tool for caching
VM act as a cache for data that sits on disk. 

