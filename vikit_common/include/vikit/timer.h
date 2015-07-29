#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <stdio.h>

namespace vk
{

class Timer
{
  using timeval = std::chrono::time_point<std::chrono::high_resolution_clock>;
private:
  timeval start_time_;
  double time_; // in seconds
  double accumulated_;
public:

  /// The constructor directly starts the timer.
  Timer() :
    time_(0.0),
    accumulated_(0.0)
  {
    start();
  }

  ~Timer()
  {}

  inline void start()
  {
    accumulated_ = 0.0;
    start_time_ = std::chrono::high_resolution_clock::now();
  }

  inline void resume()
  {
    start_time_ = std::chrono::high_resolution_clock::now();
  }

  inline double stop()
  {
    timeval end_time = std::chrono::high_resolution_clock::now();
    time_ = 1.e-6 * std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_).count();
    accumulated_ = time_;
    return time_;
  }

  inline double getTime() const
  {
    return time_;
  }

  inline void reset()
  {
    time_ = 0.0;
    accumulated_ = 0.0;
  }

  static double getCurrentTime()
  {
    timeval now = std::chrono::high_resolution_clock::now();
    return 1.e-6*std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
  }

  static double getCurrentSecond()
  {
    timeval now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
  }

};

} // end namespace vk

#endif
