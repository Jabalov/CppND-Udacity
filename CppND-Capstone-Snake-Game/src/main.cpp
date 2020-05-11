#include <iostream>
#include <future>
#include <mutex>
#include <algorithm>
#include <thread>
#include <vector>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "logger.h"

class Msg
{
public:
  Msg(int id) : _id(id) {}
  int getID() { return _id; }

private:
  int _id;
};

class Motivate
{
public:
  Motivate() {}
  Msg pop()
  {
    std::unique_lock<std::mutex> uLock(_mutex);
    _condition.wait(uLock, [this] { return !motivation_message.empty(); });

    Msg msg = std::move(motivation_message.back());
    motivation_message.pop_back();

    return msg;
  }

  void push(Msg &&msg)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::lock_guard<std::mutex> uLock(_mutex);

    std::cout << "\n Msg: #" << msg.getID() << "Keep on playing! \n" << std::endl;
    motivation_message.push_back(std::move(msg));
    _condition.notify_one();
  }

private:
  std::mutex _mutex;
  std::condition_variable _condition;
  std::vector<Msg> motivation_message;
};

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{800};
  constexpr std::size_t kGridWidth{50};
  constexpr std::size_t kGridHeight{50};
  
  Logger logger;
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  std::shared_ptr<Motivate> queue(new Motivate);
  std::cout << "\n Activating Threads, As Messages to motivate you\n " << std::endl;
  std::vector<std::future<void>> futures;
  for (int i = 0; i < 3; ++i)
  {
    Msg m(i);
    futures.emplace_back(std::async(std::launch::async, &Motivate::push, queue, std::move(m)));
  }

  std::cout << "\n ..WARNINGS.. \n" << std::endl;
  while (true)
  {
    Msg msg = queue->pop();
    std::cout << "\n HEY!: " << msg.getID() << " KEEP YOUR EYES OPEN!\n" << std::endl;
  }

  std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
    ftr.wait();
  });

  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "\n Terminated Successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  logger.WriteToLogFile(game.GetScore(), game.GetSize());

  return 0;
}