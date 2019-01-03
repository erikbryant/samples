//
// Code sample taken from:
// http://codexpert.ro/blog/2013/03/01/cpp11-concurrency-condition-variables/
//

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <random>
#include <chrono>

using std::cout;
using std::endl;

std::mutex g_lockprint;
std::mutex g_lockqueue;
std::condition_variable g_queuecheck;
std::queue<int> g_codes;
bool g_done;
bool g_notified;
bool g_loggerReady;

void workerfunc(int id, std::mt19937& generator)
{
  // print a starting message
  {
    std::unique_lock<std::mutex> locker(g_lockprint);
    cout << "[worker " << id << "]\trunning..." << endl;
  }

  // simulate work
  std::this_thread::sleep_for(std::chrono::seconds(1 + generator() % 5));

  // simulate error
  int errorcode = id*100+1;
  {
    std::unique_lock<std::mutex> locker(g_lockprint);
    cout << "[worker " << id << "]\tan error occurred: " << errorcode << endl;
  }

  // notify error to be logged
  {
    std::unique_lock<std::mutex> locker(g_lockqueue);
    g_codes.push(errorcode);
    g_notified = true;
    g_queuecheck.notify_one();
  }
}

void loggerfunc()
{
  std::this_thread::sleep_for(std::chrono::seconds(5));

  // print a starting message
  {
    std::unique_lock<std::mutex> locker(g_lockprint);
    cout << "[logger]\trunning..." << endl;
  }

  g_loggerReady = true;

  // loop until end is signaled
  while(!g_done)
    {
      std::unique_lock<std::mutex> locker(g_lockqueue);

      while(!g_notified)   // used to avoid spurious wakeups
        {
          g_queuecheck.wait_for(locker, std::chrono::milliseconds(500));
        }

      // if there are error codes in the queue process them
      while(!g_codes.empty())
        {
          std::unique_lock<std::mutex> locker(g_lockprint);
          cout << "[logger]\tprocessing error: " << g_codes.front() << endl;
          g_codes.pop();
        }

      g_notified = false;
    }
}

int main()
{
  // initialize a random generator
  std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

  // start the logger
  g_loggerReady = false;
  std::thread loggerthread(loggerfunc);
  while ( !g_loggerReady )
    {
      cout << "Sleeping to wait for logger..." << endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      cout << "...done sleeping" << endl;
    }

  // start the worker threads
  std::vector<std::thread> threads;
  for(int i = 0; i < 5; ++i)
    {
      threads.push_back(std::thread(workerfunc, i+1, std::ref(generator)));
    }

  // wait for the workers to finish
  for(auto& t : threads)
    {
      t.join();
    }

  // notify the logger to finish and wait for it
  g_done = true;
  loggerthread.join();

  return 0;
}
