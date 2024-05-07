#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> dataReceived(false);

void inputThread()
{
    int inputData;
    while (true)
    {
        std::cin >> inputData;
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataReceived = true;
        }
        cv.notify_one();
    }
}

void processingThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::seconds(5), []
                    { return dataReceived.load(); });
        // 开始处理接收到的整数
        if (dataReceived.load() == true)
        {
            std::cout
                << "Processing the received integer..." << std::endl;

            // 处理完成后重置标志以等待下一个输入
            dataReceived = false;
        }
        else
        {
            std::cout << "non number!!" << std::endl;
            std::cout << "main Thread exit!!" << std::endl;
            return;
        }
    }
}

int main()
{
    std::thread input(inputThread);
    std::thread processor(processingThread);

    input.join();
    processor.join();

    return 0;
}
