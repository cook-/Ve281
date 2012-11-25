#ifndef __QUEUE_H__
#define __QUEUE_H__

class emptyQueue
{
    // OVERVIEW: an exception class
};

template <class T>
class Queue
{
    // OVERVIEW: queue based on a circular array.
    // The queue stores pointers-to-T.

public:

    // Operational methods

    bool isEmpty() const;
    // EFFECTS: return true if the queue is empty, false otherwise

    void enqueue(T *op);
    // MODIFIES: this
    // EFFECTS: put op at the rear of the queue
    
    T *dequeue();
    // MODIFIES: this
    // EFFECTS: remove the front of the queue and return the removed
    //          element. Throw an instance of emptyQueue if empty.

    T *front();
    // EFFECTS: return the front element of the queue.
    //          Throw an instance of emptyQueue if empty.

    T *rear();
    // EFFECTS: return the rear element of the queue.
    //          Throw an instance of emptyQueue if empty.

    // Maintenance methods

    Queue(int cap = 1);                        // constructor
    Queue(const Queue &q);                     // copy constructor
    Queue &operator=(const Queue &q);          // assignment operator
    ~Queue();                                  // destructor

private:
    T **array;      // A dynamic array storing T*
    int capacity;   // The capacity of the dynamic array
    int count;      // The number of elements in the queue
    int ifront;     // The index of the first element in the queue
    int irear;      // The index of the last element in the queue

    // Utility methods

    void removeAll();
    // MODIFIES: this
    // EFFECTS: called by destructor/operator= to remove and destroy
    //          all the elements in the queue.

    void copyAll(const Queue &q);
    // MODIFIES: this
    // EFFECTS: called by copy constructor/operator= to copy elements
    //          from a source instance s to this instance.

    void grow();
    // MODIFIES: this
    // EFFECTS: called by the enqueue function to double the size of
    //          the array when the array is full. The pointers stored
    //          in the old array are copied to the new array.
};

#endif /* __QUEUE_H__ */
