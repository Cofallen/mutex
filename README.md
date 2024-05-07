## 多线程整理

目录

* [1.std::this_thread](#stdthis_thread-用法举例)
* [2.stdchrono](#stdchrono-用法举例)
* [3.stdcondition_variable](#stdcondition_variable-用法举例)

### `std::this_thread` 用法举例

`std::this_thread` 是 C++ 标准库中的命名空间，提供了与当前线程相关的功能。以下是一些 `std::this_thread` 命名空间中常用的功能和用法：

1. **std::this_thread::get_id()**
   * 用于获取当前线程的 ID。

   ```cpp
   #include <iostream>
   #include <thread>

   int main()
   {
       std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
       return 0;
   }
   ```

2. **std::this_thread::sleep_for()**
   * 用于使当前线程休眠一段时间。

   ```cpp
   #include <iostream>
   #include <thread>
   #include <chrono>

   int main()
   {
       std::cout << "Start sleeping..." << std::endl;
       std::this_thread::sleep_for(std::chrono::seconds(3));
       std::cout << "Awake after 3 seconds." << std::endl;
       return 0;
   }
   ```

3. **std::this_thread::yield()**
   * 用于提示调度器允许其他线程运行，当前线程可能会暂时放弃 CPU 时间片。

   ```cpp
   #include <iostream>
   #include <thread>

   int main()
   {
       std::cout << "Before yielding..." << std::endl;
       std::this_thread::yield();
       std::cout << "After yielding..." << std::endl;
       return 0;
   }
   ```

这些是 `std::this_thread` 命名空间中的一些常用方法。你可以根据需要，在程序中使用这些函数来处理线程相关的操作。

### `std::chrono` 用法举例

当您使用`std::chrono`库时，可以方便地处理时间点和持续时间。下面是一个简单的示例，展示了如何使用`std::chrono`来测量程序运行时间：

```cpp
#include <iostream>
#include <chrono>

int main() {
    // 获取程序开始时间点
    auto start = std::chrono::high_resolution_clock::now();

    // 模拟程序运行
    for (int i = 0; i < 1000000; ++i) {
        // do something
    }

    // 获取程序结束时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算程序运行时间
    std::chrono::duration<double> duration = end - start;
    std::cout << "程序运行时间: " << duration.count() << " 秒" << std::endl;

    return 0;
}
```

在上面的示例中，我们首先使用`std::chrono::high_resolution_clock::now()`获取程序开始时间点`start`，然后执行一些模拟的任务。接着，我们获取程序结束时间点`end`，并计算程序运行时间。最后，我们将程序运行时间输出到控制台。

`std::chrono::duration`是一个模板类，它表示时间段。在示例中，我们使用`std::chrono::duration<double>`来表示持续时间，并通过`count()`方法获取持续时间的秒数。

通过使用`std::chrono`库，您可以方便地测量程序执行时间、处理时间间隔等时间相关操作。

### `std::condition_variable` 用法举例

`std::condition_variable` 是 C++ 标准库中用于多线程编程的类之一，它通常与 `std::mutex` 一起使用来实现线程间的同步和通信。以下是它的常见用法：

1. **等待条件变量的通知：** 线程可以通过调用 `wait()` 函数来等待条件变量的通知。在等待过程中，线程会释放与 `std::unique_lock<std::mutex>` 相关联的互斥锁，并暂时阻塞。当其他线程调用了 `notify_one()` 或 `notify_all()` 发送了通知时，等待的线程将被唤醒继续执行。

2. **在特定条件下等待：** 通常情况下，`wait()` 函数会接受一个 lambda 函数作为参数，用于指定在收到通知前线程应该等待的特定条件。例如：

   ```cpp
   std::condition_variable cv;
   std::mutex mtx;
   bool someCondition = false;

   // ...

   std::unique_lock<std::mutex> lock(mtx);
   cv.wait(lock, []{ return someCondition; });

   // 等待结束后，继续执行操作
   ```

3. **发送通知：** 可以调用 `notify_one()` 或 `notify_all()` 函数来发送通知给等待的线程，唤醒一个或多个等待的线程。这通常是在持有相同互斥锁的情况下进行的，以确保线程间的正确同步。

总的来说，`std::condition_variable` 可以帮助协调多个线程之间的操作，确保在某个特定情况满足时线程能够安全地等待或唤醒。
