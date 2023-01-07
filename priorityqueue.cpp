#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) : nodes_(max_size + 1, KeyValuePair()),
                                                     max_size_(max_size),
                                                     size_(0)
{
}

void PriorityQueue::insert(Key k)
{
    insert(std::make_pair(k, std::make_pair(0, 0)));
}
// This function inserts a KeyValuePair, overloaded function.
void PriorityQueue::insert(KeyValuePair kv)
{
    // TODO: complete this function
    nodes_[++size_] = kv; // add KeyValuePair at the end of the heap.
    heapifyUp(size_);     // then heapify up because the KeyValuePair is added at the end.
}
// This is a helper function to get the max size of heap.
size_t PriorityQueue::getMaxSize() const // getter function to get the value of maxHeapSize.
{
    return max_size_; // return max size of heap.
}
// This function returns the minimum value.
KeyValuePair PriorityQueue::min()
{
    // TODO: complete this function
    KeyValuePair minimum;
    minimum = nodes_[1]; // the first node is the minimum as it is min heap.
    return minimum;      // return the minimum.
}
// This function removes the minimum node and then returns it.
KeyValuePair PriorityQueue::removeMin()
{
    // TODO: complete this function
    KeyValuePair retMinimum = min(); // save the min before popping.
    removeNode(1);                   // then remove the first node as it is the minimum.
    return retMinimum;               // return the minimum.
}
// This function returns if the priority queue is empty or not.
bool PriorityQueue::isEmpty() const
{
    // TODO: complete this function
    bool empty = (size_ == 0); // empty is true if size is or else it is false.
    return empty;           // returns whether the priority queue is empty or not.
}
// This function determines the size of the Priority Queue.
size_t PriorityQueue::size() const
{
    // TODO: complete this function
    return size_; // return size.
}

nlohmann::json PriorityQueue::JSON() const
{
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++)
    {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT)
        {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_)
        {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_)
        {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}
// This function heapifies up.
void PriorityQueue::heapifyUp(size_t i)
{
    // TODO: complete this function
    //
    size_t minimum = i, parent = i / 2; // the parent node of node i is at node i/2 and the minimum node is node i.
    if (minimum > 0)                    // As long as minimum is not 0 it will have a parent.
        if (getKey(minimum) < getKey(parent))
        {                                          // if the key at the minimum node is lesser than the key of the parent node.
            swap(nodes_[minimum], nodes_[parent]); // then swap the minimum node and the parent node such the heap is a min heap(parent node < minimum node).
            heapifyUp(parent);                     // then check if the new parent node is correctly placed.
        }
}
// This function heapifies down.
void PriorityQueue::heapifyDown(size_t i)
{
    // TODO: complete this function
    size_t minimum = i, leftChild = 2 * minimum, rightChild = 2 * minimum + 1;
    if (getKey(minimum) > getKey(leftChild) && leftChild < size_ + 1)
    {                        // if minimum node's key is greater than left child's key and if left child is in the heap
        minimum = leftChild; // make the left child the minimum.
    }
    if (getKey(minimum) > getKey(rightChild) && rightChild < size_ + 1)
    {                         // if minimum node's key is greater than right child's key and if right child is in the heap
        minimum = rightChild; // make the right child the minimum.
    }
    if (minimum == rightChild || minimum == leftChild)
    {                                     // if minimum has changed
        swap(nodes_[i], nodes_[minimum]); // then swap the minimum node and node i.
        heapifyDown(minimum);             // then heapify down the minimum until it is correctly placed.
    }
}
// This function removes the node at the ith place.
void PriorityQueue::removeNode(size_t i)
{
    // TODO: complete this function
    size_t minimum = i, parent = i / 2;        // the parent node of node i is at node i/2 and the minimum node is node i.
    swap(nodes_[minimum], nodes_[size_]);      // swap node i and the last node.
    size_--;                                   // decrease the size by as 1 node is removed.
    if (getKey(minimum) < getKey(parent))      // if the key of the minimum node is less than the key of its parent
        heapifyUp(minimum);                    // then heapify up.
    else if (getKey(minimum) > getKey(parent)) // if the key of the minimum node is greater than the key of its parent
        heapifyDown(minimum);                  // then heapify down.
}
// This function gets the key of the ith node.
Key PriorityQueue::getKey(size_t i)
{
    // TODO: complete this function
    Key nodeKey = nodes_[i].first; // getter to get the key of node i where i is
    return nodeKey;
}
