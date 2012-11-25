#ifndef __QUEUE_C__
#define __QUEUE_C__

template <class T>
bool Queue<T>::isEmpty() const
{
	return (!count);
}

template <class T>
void Queue<T>::enqueue(T *op)//check NULL????????????????????
{
	if (op!=NULL)
	{
		if (count==capacity)
		{
			grow();
		}
		count=count+1;
		irear=(irear+1)%capacity;
		*(array+irear)=op;
	}
}

template <class T>
T* Queue<T>::dequeue()
{
	if (isEmpty())
	{
		emptyQueue queueisempty;
		throw queueisempty;
	}
	count=count-1;
	T* a=*(array+ifront);//???????????????don't change array??????????????????
	ifront=(ifront+1)%capacity;
	return a;
}

template <class T>
T* Queue<T>::front()
{
	if (isEmpty())
	{
		emptyQueue queueisempty;
		throw queueisempty;
	}
	return *(array+ifront);
}

template <class T>
T* Queue<T>::rear()
{
	if (isEmpty())
	{
		emptyQueue queueisempty;
		throw queueisempty;
	}
	return *(array+irear);
}

template <class T>
Queue<T>::Queue(int cap):
array(new T*[cap]), capacity(cap), count(0), ifront(0), irear(cap-1)
{
}

template <class T>
Queue<T>::Queue(const Queue &q)
{
	capacity=q.capacity;
	count=q.count;
	ifront=q.ifront;
	irear=q.irear;
	array=new T*[q.capacity];
	copyAll(q);
}

template <class T>
Queue<T>& Queue<T>::operator= (const Queue &q)
{
	removeAll();
	capacity=q.capacity;
	count=q.count;
	ifront=q.ifront;
	irear=q.irear;
	copyAll(q);
	return *this;
}

template <class T>
Queue<T>::~Queue()
{
	removeAll();
	delete[] array;
}

template <class T>
void Queue<T>::removeAll()
{
	while (count!=0)
	{
		delete array[ifront];
		ifront=(ifront+1)%capacity;
		count--;
	}
}

template <class T>
void Queue<T>::copyAll(const Queue &q)//?????assignment
{
	//int i=q.count;
	for (int i=0;i<q.count;i++)
	{
		array[i]=new T(*q.array[i]);
	}
}

template <class T>
void Queue<T>::grow()
{
	T** nextarray=new T*[capacity*2];
	for (int i=0;i<capacity;i++)
	{
		nextarray[i]=array[i];
	}
	irear=capacity-1;
	capacity=capacity*2;
	T** de=array;
	array=nextarray;
	delete [] de;
}



#endif /*__QUEUE_H__*/
