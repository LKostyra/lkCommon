#pragma once
#define _LKCOMMON_UTILS_STACK_HPP_

#include "lkCommon/lkCommon.hpp"


namespace lkCommon {
namespace Utils {

/**
 * A LIFO stack implementation allocating memory once on heap.
 *
 * @warning For performance, this stack does not perform any checks on
 *          Release code. All error checks are done with asserts.
 */
template <typename T, size_t N>
class Stack
{
    T* mStack;
    size_t mStackPointer;

public:
    /**
     * Constructs and initializes stack.
     */
    Stack();

    /**
     * Destructs stack and frees its allocated memory.
     */
    ~Stack();

    /**
     * Push existing element on top of stack.
     *
     * @p[in] element Element to be pushed on top of stack.
     *
     * @note Exceptional situations (like exceeding stack's size) are detected
     *       only with debug assertions.
     */
    void Push(const T& element);

    /**
     * Construct in-place element on top of stack.
     *
     * @p[in] args Arguments passed to element's constructor.
     *
     * @note Exceptional situations (like exceeding stack's size) are detected
     *       only with debug assertions.
     */
    template <typename... Args>
    void Emplace(Args&&... args);

    /**
     * Get stack element on top.
     *
     * @return Top element from stack. Element is considered as non-existent
     *         on stack after this call (meaning, subsequent Push calls can
     *         overwrite it).
     *
     * @note Popping on an empty stack is detected with assertion only in Debug
     *       build.
     */
    T Pop();

    /**
     * Acquire stack's max possible size.
     */
    constexpr size_t Capacity() const
    {
        return N;
    }

    /**
     * Acquire amount of elements already on Stack.
     */
    LKCOMMON_INLINE size_t Size() const
    {
        return mStackPointer;
    }
};

} // namespace Utils
} // namespace lkCommon

#include "StackImpl.hpp"
