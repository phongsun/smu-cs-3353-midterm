/**
    CS 3353 Midterm
    main.cpp
    @brief : Performance comparison between FBVector and std:Vector on push_back and erase operations
    @author Peter Sun - sunsound777@gmail.com
    @version 1.0 
    @date 4/1/2021 
*/
#include <folly/FbVector.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/**
 This function test latency of push_back function for fbvector
 @param n number of elements that need to be push_back into the fbvector
 @return execution tine in microseconds
*/
double fbvector_push_back_test(int n, ofstream &output)
{
  double time_taken;
  auto start = chrono::high_resolution_clock::now();
  folly::fbvector<int> numbers;
  for (int i = 0; i < n; i++)
  {
    numbers.push_back(i);
  }

  auto end = chrono::high_resolution_clock::now();
  time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count();
  return time_taken;
}

/**
 This function test latency of push_back function for std::vector
 @param n number of elements that need to be push_back into the std::vector
 @return execution tine in microseconds
*/
double stdvector_push_back_test(int n, ofstream &output)
{
  double time_taken;
  auto start = chrono::high_resolution_clock::now();
  std::vector<int> numbers;
  for (int i = 0; i < n; i++)
  {
    numbers.push_back(i);
  }

  auto end = chrono::high_resolution_clock::now();
  time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count();
  return time_taken;
}

/**
 This function test latency of erase function for fbvector
 @param n number of elements of the fbvector to measure erase operation
 @return execution tine in microseconds
*/
double fbvector_erase_test(int n, ofstream &output)
{
  folly::fbvector<int> numbers;
  for (int i = 0; i < n; i++)
  {
    numbers.push_back(i);
  }
  double time_taken;
  auto start = chrono::high_resolution_clock::now();
  // erase even numbers from the fbvector
  folly::erase_if(numbers, [](const auto &x) { return x % 2 == 0; });
  auto end = chrono::high_resolution_clock::now();
  time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count();
  return time_taken;
}

/**
 This function test latency of erase function for std::vector
 @param n number of elements of the std::vector to measure erase operation
 @return execution tine in microseconds
*/
double stdvector_erase_test(int n, ofstream &output)
{
  std::vector<int> numbers;
  for (int i = 0; i < n; i++)
  {
    numbers.push_back(i);
  }

  double time_taken;
  auto start = chrono::high_resolution_clock::now();
  // erase even numbers from the std::vector
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](const int &x) { return x % 2 == 0; }), numbers.end());
  auto end = chrono::high_resolution_clock::now();

  time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count();
  return time_taken;
}

/**
 This program measures latency of push_back and erase operation of FBVector and std:vector with different vector sizes.
*/
int main()
{
  int size[6] = {100, 1000, 10000, 100000, 1000000, 10000000}; // sizes of testing datasets
  ofstream output("output.csv");
  output << "size,data_structure,operation,latency" << std::endl;

  double fb_time_taken = 0;
  double std_time_taken = 0;
  // comparison runs on push_back on different sizes
  for (int j = 0; j < 6; j++)
  {
    // run test functions 6 times to get stable results
    // alternate order of execution to reduce bias
    fb_time_taken = 0;
    std_time_taken = 0;
    for (int i = 0; i < 6; i++)
    {
      if (i % 2 == 0) // test std vector first in even number runs
      {
        std_time_taken = std_time_taken + stdvector_push_back_test(size[j], output);
        fb_time_taken = fb_time_taken + fbvector_push_back_test(size[j], output);
      }
      else // test fbvector first in odd number runs
      {
        fb_time_taken = fb_time_taken + fbvector_push_back_test(size[j], output);
        std_time_taken = std_time_taken + stdvector_push_back_test(size[j], output);
      }
    }
    output << size[j] << ",vector,push_back," << (std_time_taken/6) << std::endl;
    output << size[j] << ",fbvector,push_back," << (fb_time_taken/6) << std::endl;
  }

  // comparison runs on erase on different sizes
  for (int j = 0; j < 6; j++)
  {
    // run test functions 6 times to get stable results
    // alternate order of execution to reduce bias
    fb_time_taken = 0;
    std_time_taken = 0;
    for (int i = 0; i < 6; i++)
    {
      if (i % 2 == 0) // test std vector first in even number runs
      {
        std_time_taken = std_time_taken + stdvector_erase_test(size[j], output);
        fb_time_taken = fb_time_taken + fbvector_erase_test(size[j], output);
      }
      else // test fbvector first in odd number runs
      {
        fb_time_taken = fb_time_taken + fbvector_erase_test(size[j], output);
        std_time_taken = std_time_taken + stdvector_erase_test(size[j], output);
      }
    }
    output << size[j] << ",vector,erase," << (std_time_taken/6) << std::endl;
    output << size[j] << ",fbvector,erase," << (fb_time_taken/6) << std::endl;
  }
  output.close();
}