#ifndef __QUEUE_C__
#define __QUEUE_C__

template <class T>
bool Queue<T>::isEmpty() const {
	return !count;
}

template <class T>
void Queue<T>::enqueue(T *op) {
	if (count == capacity)
		grow();
	irear = (irear + 1)%capacity;
	count++;
	array[irear] = op;
}

template <class T>
T* Queue<T>::dequeue() {
	if (isEmpty()) {
		emptyQueue e;
		throw &e;
	}
	T* op = array[ifront];
	ifront = (ifront + 1)%capacity;
	count--;
	return op;
}

template <class T>
T* Queue<T>::front() {
	if (isEmpty()) {
		emptyQueue e;
		throw &e;
	}
	return array[ifront];
}

template <class T>
T* Queue<T>::rear() {
	if (isEmpty()) {
		emptyQueue e;
		throw &e;
	}
	return array[irear];
}

template <class T>
Queue<T>::Queue(int cap)
: array(new T*[cap]), capacity(cap), count(0), ifront(0), irear(cap - 1) {}

template <class T>
Queue<T>::Queue(const Queue &q)
: array(new T*[q.capacity]), capacity(q.capacity), count(q.count), ifront(q.ifront), irear(q.irear) {
	copyAll(q);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue &q) {
	if (array != q.array) {
		removeAll();
		capacity = q.capacity;
		count = q.count;
		ifront = q.ifront;
		irear = q.irear;
		copyAll(q);
	}
	return *this;
}

template <class T>
Queue<T>::~Queue() {
	removeAll();
	delete [] array;
}

template <class T>
void Queue<T>::removeAll() {
	while (count) {
		delete array[ifront];
		ifront = (ifront + 1)%capacity;
		count--;
	}
}

template <class T>
void Queue<T>::copyAll(const Queue &q) {
	for (int i = 0; i != q.count; ++i)
		array[i] = new T(*(q.array[i]));
}

template <class T>
void Queue<T>::grow() {
	T **new_array = new T*[2*capacity];
	for (int i = 0; i != capacity; ++i) {
		new_array[i] = array[ifront];
		ifront = (ifront + 1)%capacity;
	}
	ifront = 0;
	irear = capacity - 1;
	capacity = 2*capacity;
	T **victim = array;
	array = new_array;
	delete [] victim;
}

#endif /* __QUEUE_C__ */
