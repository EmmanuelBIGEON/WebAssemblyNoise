#include "Chrono.h"

#include <chrono>
#include <iostream>

Chrono::Chrono()
{
}

Chrono::~Chrono()
{
}

void Chrono::Start()
{
  m_startTime = std::chrono::system_clock::now();
  started = true;
}

void Chrono::Stop()
{
  if(started)
  {
    m_stopTime = std::chrono::system_clock::now();
    finished = true;
  }
}

void Chrono::Reset()
{
  started = false;
  finished = false;
}

float Chrono::GetElapsedTime()
{
  if(!finished) return -1;
  std::chrono::duration<float> elapsed = m_stopTime - m_startTime;
  return elapsed.count();
}

float Chrono::GetCurrentDuration()
{
  std::chrono::duration<float> elapsed = std::chrono::system_clock::now() - m_startTime;
  return elapsed.count();
}

void Chrono::PrintElapsedTime()
{
  std::chrono::duration<float> elapsed = m_stopTime - m_startTime;
  std::cout << elapsed.count() << " seconds.." << std::endl;
}