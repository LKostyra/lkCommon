#include <gtest/gtest.h>

#include <lkCommon/Utils/ThreadPool.hpp>

using namespace lkCommon::Utils;

const uint64_t TASK_COUNT_UNTIL_VALUE = 400'000'000;
const uint64_t TASK_COUNT_UNTIL_VALUE_SMALL = 100'000;


TEST(ThreadPool, Constructor)
{
    ThreadPool tp;
    EXPECT_EQ(lkCommon::System::Info::GetCPUCount(), tp.GetWorkerThreadCount());
}

TEST(ThreadPool, ConstructorSingleThread)
{
    ThreadPool tp(1);
    EXPECT_EQ(1, tp.GetWorkerThreadCount());
}

TEST(ThreadPool, AddTasksSimple)
{
    auto task = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE)
            i++;
    };

    ThreadPool tp(3);

    tp.AddTask(task);
    tp.AddTask(task);
    tp.AddTask(task);
}

TEST(ThreadPool, AddTasksSimpleSingleThread)
{
    auto task = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE)
            i++;
    };

    ThreadPool tp(1);

    tp.AddTask(task);
    tp.AddTask(task);
    tp.AddTask(task);
}

TEST(ThreadPool, AddTasksComplex)
{
    auto task = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE)
            i++;
    };

    auto taskDouble = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE * 2)
            i++;
    };

    auto taskHalf = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE / 2)
            i++;
    };

    // init pool
    ThreadPool tp(3);

    // add first tasks
    tp.AddTask(task);
    tp.AddTask(taskDouble);
    tp.AddTask(taskHalf);

    // synchronization point
    tp.WaitForTasks();

    // add more tasks
    tp.AddTask(task);
    tp.AddTask(taskDouble);
    tp.AddTask(taskDouble);
    tp.AddTask(taskHalf);
    tp.AddTask(taskHalf);
    tp.AddTask(task);
}

TEST(ThreadPool, AddTasksDoubleThreadCount)
{
    auto task = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE)
            i++;
    };

    auto taskDouble = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE * 2)
            i++;
    };

    auto taskHalf = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE / 2)
            i++;
    };

    size_t cpuCount = lkCommon::System::Info::GetCPUCount() * 2;

    // init pool
    ThreadPool tp(cpuCount);

    size_t taskSelector = 0;
    const size_t taskCollectionCount = 3;

    for (size_t i = 0; i < cpuCount * 2; ++i)
    {
        taskSelector = i % taskCollectionCount;
        switch (taskSelector)
        {
        case 0: tp.AddTask(task); break;
        case 1: tp.AddTask(taskDouble); break;
        case 2: tp.AddTask(taskHalf); break;
        default: break;
        }
    }
}

TEST(ThreadPool, StressTest)
{
    auto task = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE_SMALL)
            i++;
    };

    auto taskDouble = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE_SMALL * 2)
            i++;
    };

    auto taskHalf = []() {
        volatile uint64_t i = 0;
        while (i != TASK_COUNT_UNTIL_VALUE_SMALL / 2)
            i++;
    };

    const size_t taskCount = 200;

    // init pool
    ThreadPool tp;

    size_t taskSelector = 0;
    const size_t taskCollectionCount = 3;

    for (size_t j = 0; j < 30; ++j)
    {
        for (size_t i = 0; i < taskCount; ++i)
        {
            taskSelector = i % taskCollectionCount;
            switch (taskSelector)
            {
            case 0: tp.AddTask(task); break;
            case 1: tp.AddTask(taskDouble); break;
            case 2: tp.AddTask(taskHalf); break;
            default: break;
            }
        }

        tp.WaitForTasks();
    }
}
