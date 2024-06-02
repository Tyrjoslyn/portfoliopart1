/*Portfolio Project Part 1
 * 1. create class counter
 * 		create private variables for int: counter, boolean: ready condition v: cv, mutex: mtx
 * 		a. create count up method
 * 			aa:lock counter
 * 			ab: interate counter up
 * 			ac:unlock
 * 			ab: print completion notification
 * 		b. create count down method
 * 			aa:lock counter
 * 			ab: interat counter down
 * 			ac: unlock
 * 		c: main method
 * 			aa: create 2 threads for count up and count down
 * 			ab: notify end of program
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Counter {
public:
    Counter() : counter(0), ready(false) {}

    void count_up() {
        for (int i = 0; i <= 20; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            counter = i;
            std::cout << "Count Up: " << counter << std::endl;

            // Timer between counts for readability
            std::this_thread::sleep_for(std::chrono::milliseconds(300));}
        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
            std::cout << " " << std::endl;
            std::cout << "Finished counting up." << std::endl;
            std::cout << " " << std::endl;}
        cv.notify_one(); // Notify the waiting thread
    }

    void count_down() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return ready; });

        for (int i = 20; i >= 0; --i) {
            counter = i;
            std::cout << "Count Down: " << counter << std::endl;

            // Timer between counts for readability
            std::this_thread::sleep_for(std::chrono::milliseconds(300));}
    }

private:
    int counter;
    std::mutex mtx;
    std::condition_variable cv;
    bool ready;};

int main() {
    Counter counter;

    // Create threads
    std::thread t1(&Counter::count_up, &counter);
    std::thread t2(&Counter::count_down, &counter);

    // Wait for threads
    t1.join();
    t2.join();

    std::cout << "End of program." << std::endl;
    return 0;
}



