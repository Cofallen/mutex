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


### 析构互斥锁区别

1. `std::lock_guard` 和 `std::unique_lock` 都是用于管理互斥锁的RAII（资源获取即初始化）类，但它们之间有一些重要的区别：
   - `std::lock_guard` 是一个轻量级的互斥锁封装，一旦被构造就会锁住互斥锁，并在其生命周期结束时自动释放互斥锁。`std::lock_guard` 适用于需要在同一作用域内锁住互斥锁的简单情况。
   - `std::unique_lock` 提供了更多的灵活性，它可以手动锁定和解锁互斥锁，并且可以延迟锁定。`std::unique_lock` 还支持条件变量的等待操作。因此，如果需要更多的控制权和灵活性，可以选择使用 `std::unique_lock`。

   在同一个作用域内，不建议混用 `std::lock_guard` 和 `std::unique_lock`，因为它们的行为可能会相互干扰，导致意外的行为发生。

2. 在使用互斥锁时，`mtx` 是全局变量，可以在任何地方使用，包括在 `std::lock_guard` 或 `std::unique_lock` 中。这是因为 `mtx` 是一个全局变量，可以在整个程序中访问。

3. `cv.notify_one()` 必须在互斥锁被锁定的情况下调用，以避免出现竞争条件。唤醒条件变量的操作通常需要与互斥锁一起使用，以确保线程安全。因此，一般情况下，`cv.notify_one()` 应该在已经锁定互斥锁的情况下调用。如果在没有锁定互斥锁的情况下调用 `cv.notify_one()`，可能会导致竞争条件和意外行为。1. `std::lock_guard` 和 `std::unique_lock` 都是用于管理互斥锁的RAII（资源获取即初始化）类，但它们之间有一些重要的区别：
   - `std::lock_guard` 是一个轻量级的互斥锁封装，一旦被构造就会锁住互斥锁，并在其生命周期结束时自动释放互斥锁。`std::lock_guard` 适用于需要在同一作用域内锁住互斥锁的简单情况。
   - `std::unique_lock` 提供了更多的灵活性，它可以手动锁定和解锁互斥锁，并且可以延迟锁定。`std::unique_lock` 还支持条件变量的等待操作。因此，如果需要更多的控制权和灵活性，可以选择使用 `std::unique_lock`。

   在同一个作用域内，不建议混用 `std::lock_guard` 和 `std::unique_lock`，因为它们的行为可能会相互干扰，导致意外的行为发生。

2. 在使用互斥锁时，`mtx` 是全局变量，可以在任何地方使用，包括在 `std::lock_guard` 或 `std::unique_lock` 中。这是因为 `mtx` 是一个全局变量，可以在整个程序中访问。

3. `cv.notify_one()` 必须在互斥锁被锁定的情况下调用，以避免出现竞争条件。唤醒条件变量的操作通常需要与互斥锁一起使用，以确保线程安全。因此，一般情况下，`cv.notify_one()` 应该在已经锁定互斥锁的情况下调用。如果在没有锁定互斥锁的情况下调用 `cv.notify_one()`，可能会导致竞争条件和意外行为。


### 同锁与不同锁区别

使用相同的 `std::mutex` 和不同的 `std::mutex` 之间有一些重要区别，这些区别可以影响代码的正确性和性能。让我详细说明一下：

### 相同的 std::mutex vs. 不同的 std::mutex

#### 相同的 std::mutex
- **示例**：在多个线程中共享相同的资源时，你可以使用相同的 `std::mutex` 来确保对这个资源的互斥访问。
- **优点**：
  - 简单：只需一个互斥量来管理对共享资源的访问。
  - 避免竞态条件：由于同一资源的互斥保护，避免了竞态条件。
- **缺点**：
  - 性能：如果一个线程正在使用互斥量锁定资源，其他线程就无法同时访问任何受该互斥量保护的资源，可能会导致性能瓶颈。

#### 不同的 std::mutex
- **示例**：当有多个独立的资源需要并行访问时，你可以为每个资源创建不同的 `std::mutex`。
- **优点**：
  - 并行性：不同的资源可以并行处理，因为它们有各自的互斥量。
  - 性能：避免了单一互斥量成为性能瓶颈的情况。
- **缺点**：
  - 复杂性：需要管理多个互斥量，可能需要更复杂的逻辑来确保正确的锁定顺序以避免死锁。

### 不同的互斥量之间是否可以通过条件变量联系？

是的，不同的互斥量之间可以通过条件变量联系。条件变量允许线程等待某个条件得到满足，并且在条件满足时通知其他线程。条件变量通常与互斥量一起使用，以便在线程等待条件变量时能够安全地释放互斥锁。

例如，在多生产者-消费者问题中，可以为每个生产者和消费者线程分配一个独立的互斥量，并使用条件变量来实现线程间的通信。当生产者生产了数据时，它可以通知消费者线程来获取数据；反之，当消费者消费完数据时，它可以通知生产者线程来生产新的数据。

总之，条件变量提供了一种方式，使得不同的互斥量之间的线程可以进行有效的协调和通信。


