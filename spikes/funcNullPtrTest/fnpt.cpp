
#include <iostream>
#include <functional>

void doNothing();

int main()
{
  std::function<void()> func = nullptr;


  if(func)
    std::cout << "I didn't explode!" << std::endl;
  else
    std::cout << "I'm a nullptr! " << std::endl;

  func = doNothing;

  if(func)
    func();
  else
    std::cout << "I'm a nullptr! " << std::endl;
}

void doNothing()
{
    std::cout << "I'm doing nothing! " << std::endl;  
}

