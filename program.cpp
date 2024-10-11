#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <climits>
using namespace std;

int findMin(int array[], int s, int e) {
    int min = INT_MAX; 
    for (int i = s; i < e; i++) {
        if (array[i] < min){

            min= array[i];
        }
           
    }
    return min;
}


int main() {
    srand(time(0));  
    int size = 20;
    int array[size];
    
    
    for(int i = 0; i < size; i++) {
        array[i] = rand() % 1000; 
        cout << array[i] << endl; 
    }
    
    pid_t processPointer = fork();  // Create a child process using fork

    if (processPointer == 0) {
        // This is the child process
        int Min = findMin(array, size / 2, size); 
        cout << "Child Process (PID: " << getpid() << "): Min value in the second half = " << Min << endl;
        exit(Min);  // Exit with the minimum value as the exit status
    } else if (processPointer > 0) {
        // This is the parent process
        int pmin = findMin(array, 0, size / 2);
        cout << "Parent Process (PID: " << getpid() << "): Min value in the first half = " << pmin << endl;

        // Wait for the child process
        int status;
        wait(&status);

        // Get exit status
        int cMin = WEXITSTATUS(status);


        // Print the overall minimum value
        cout << "Minimum value in array = " << ((cMin < pmin)? cMin : pmin) << endl;
    }


}
