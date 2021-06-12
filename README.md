# thread-safe-counter

Developed by Woojoong Kim (20153330).<br/>
Developed in WSL2 environment.<br/>

"Upgrade list"<br/>

##1. Create semaphore.c from copy of tscounter.c<br/>
-> Understand the structure of tscounter.c<br/>
-> Be ready to make semaphore.c file using semaphore.<br/>

##2. Edit semaphore.c to lock the thread with semaphore<br/>
-> Alternate Mutex part with Semaphore.<br/>
-> Use IPC_PRIVATE to create key.<br/>
-> Create sema_lock, sema_unlock function to lock the threads more simple.<br/>

##3. Update semaphore.c and tscounter.c can use clock function to measure the execution time<br/>
-> Use <time.h> header file and clock_t variable to measure the exection time in main function.<br/>

##Result
-> I measured the execution time for semaphore.c and tscounter.c and results are as follows.<br/>
	semaphore : 7.877sec
	tscounter : 0.022sec
	The above result is the result of setting the count to 100000 when I execute.
-> This result shows that semaphore takes longer to execute than mutex.<br/>

