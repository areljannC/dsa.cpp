/*
  Data Structures | Stack (Dynamic Array)

  This stack implementation will only cover `int` data types.

  --- Time Complexities ---
  | Push           | O(1) |
  | Pop            | O(1) |
  | Peek           | O(1) |
  | Search         | O(n) |
  -------------------------
*/

#include <iostream>
#include <cassert>

class StackDynamicArray
{
private:
  typedef unsigned int uint;
  int *_arrayPtr;
  uint _size;
  uint _capacity;
  uint _initialCapacity;
  bool _shouldIncreaseCapacity() { return this->_size <= this->_capacity && this->_size + 1 > this->_capacity; }
  bool _shouldDecreaseCapacity() { return this->_size - 1 == this->_capacity / 2; }

public:
  uint size() { return this->_size; }
  bool empty() { return this->_size == 0; }

  StackDynamicArray()
  {
    this->_arrayPtr = new int[0];
    this->_size = 0;
    this->_capacity = 0;
    this->_initialCapacity = 0;
  }

  StackDynamicArray(uint capacity)
  {
    this->_arrayPtr = new int[capacity];
    this->_size = 0;
    this->_capacity = capacity;
    this->_initialCapacity = capacity;
  }

  void push(int element)
  {
    if (this->_shouldIncreaseCapacity()) this->increaseCapacity();
    this->_arrayPtr[this->_size++] = element;
  }

  int pop()
  {
    if (this->empty()) throw std::runtime_error("Stack is empty.");
    if (this->_shouldDecreaseCapacity()) this->decreaseCapacity();
    return this->_arrayPtr[this->_size-- - 1];
  }

  int top()
  {
    if (this->empty()) throw std::runtime_error("Stack is empty.");
    return this->_arrayPtr[this->_size - 1];
  }

  bool contains(int element)
  {
    if (this->empty()) throw std::runtime_error("Stack is empty.");
    for (uint i = 0; i < this->_size; i++) if (this->_arrayPtr[i] == element) return true;
    return false;
  }

  int indexOf(int element)
  {
    if (this->empty()) throw std::runtime_error("Stack is empty.");
    for (uint i = 0; i < this->_size; i++) if (this->_arrayPtr[i] == element) return i;
    return -1;
  }

  void increaseCapacity()
  {
    if (this->_capacity == 0) this->_capacity = 1;
    else this->_capacity *= 2;

    auto *tempArrayPtr = new int[this->_capacity];
    for (uint i = 0; i < this->_size; i++) tempArrayPtr[i] = this->_arrayPtr[i];

    delete[] this->_arrayPtr;
    this->_arrayPtr = tempArrayPtr;
  }

  void decreaseCapacity()
  {
    this->_capacity /= 2;
    if (this->_capacity < this->_initialCapacity) this->_capacity = this->_initialCapacity;

    auto *tempArrayPtr = new int[this->_capacity];
    for (uint i = 0; i < this->_size; i++) tempArrayPtr[i] = this->_arrayPtr[i];

    delete[] this->_arrayPtr;
    this->_arrayPtr = tempArrayPtr;
  }

  void toString()
  {
    for (uint i = 0; i < this->_size; i++)
    {
      if (i == this->_size - 1) std::cout << this->_arrayPtr[i];
      else std::cout << this->_arrayPtr[i] << " -> ";
    }
    std::cout << std::endl;
    std::cout << "Top: " << this->top() << std::endl;
    std::cout << "Size: " << this->_size << std::endl;
    std::cout << "Capacity: " << this->_capacity << std::endl;
    std::cout << "Initial Capacity: " << this->_initialCapacity << std::endl;
  }
};

int main()
{
  StackDynamicArray stack(4);

  stack.push(1);
  stack.push(2);

  assert(stack.top() == 2);
  assert(stack.size() == 2);

  stack.push(3);
  stack.push(4);

  assert(stack.top() == 4);
  assert(stack.size() == 4);

  assert(stack.pop() == 4);
  assert(stack.pop() == 3);

  assert(stack.top() == 2);
  assert(stack.size() == 2);

  assert(stack.contains(1) == true);
  assert(stack.contains(2) == true);
  assert(stack.contains(3) == false);

  assert(stack.indexOf(1) == 0);
  assert(stack.indexOf(2) == 1);
  assert(stack.indexOf(3) == -1);

  stack.toString();

  return 0;
}
