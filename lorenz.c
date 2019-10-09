#include <stdio.h>
#include <thread>
#include <sched.h>
#include <stdio.h>
#include <sys/sysinfo.h>
// #define _GNU_SOURCE



using namespace std;


// int numCPU = sysconf(_SC_NPROCESSORS_ONLN);


int gNumThreads = 8;


float varA = 10.0;
  float varB = 28.0;
  float varC = 8.0 / 3.0;
  float varT = 0.01;

/******************************************************************************/
int runIt(int tid){
  float varX = 1.0;
  float varY = 3.1;
  float varZ = 0; 
   

  for(int i=0; i<100000000; i++){
    // varB = (varX*varX)/(tid+varY);

    float varXvarT = varX + varT * varA * (varY - varX);

      float varYvarT = varY + varT * (varX * (varB - varZ) - varY);

      float varZvarT = varZ + varT * (varX * varY - varC * varZ);

      varX = varXvarT;

      varY = varYvarT;

      varZ = varZvarT;

    // printf("x: %f y: %f  z: %f\n", varX, varY, varZ);

  }
  return 0;
  
}

/******************************************************************************/
int main(int argc, char* argv[]){

  int MULTITHREAD = 1; // set default
  if(argc == 2){
    MULTITHREAD = atof(argv[1]);
  }

  time_t theStart, theEnd;
  time(&theStart);

  int loop = 0;
  unsigned int numberOfCores = std::thread::hardware_concurrency();
  printf("This machine has %d cores\n", numberOfCores);

  // cpu_set_t mask;
  // CPU_ZERO(&mask);

  // while(loop < numberOfCores) {
  //   CPU_SET(loop, $mask);
  //   loop++;
  // }

  if(MULTITHREAD){
    thread zThreads[gNumThreads];
    for(int tid=0; tid < gNumThreads-1; tid++){
      zThreads[tid] = thread(runIt, tid);
    }

    runIt(gNumThreads-1);
    for(int tid=0; tid<gNumThreads-1; tid++){
      zThreads[tid].join();
     // zThreads[tid].detach(); // OR USE THIS TO DETACH THE THREAD(S)
    }
  }

  else{
      for(int tid=0; tid<8; tid++){
        runIt(tid);
        }
  }

  time(&theEnd);
  if(MULTITHREAD)
    printf("MULTITHREADING seconds used: %ld\n", theEnd - theStart);
  else
    printf("NOT THREADING seconds used: %ld\n", theEnd - theStart);
  return 0;
}
/******************************************************************************/
