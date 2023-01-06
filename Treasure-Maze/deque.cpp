/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
/* YOUR CODE HERE! */
n1 = 0; // left
n2 = 0; // right
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    /**
     * @todo Your code here!
     */
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    /**
     * @todo Your code here! 
     */

    // case where cannot pop becuase deque is empty
    if (n1 == n2) return T();

    T temp = data[n1];
    n1 += 1;

    int size = n2 - n1;

    if (size <= n1) {
         vector<T> new_data;
        int index = n1; 
        for (int i = 0; i < size; i++) {
            T next = data[index]; // causes seg fault!!! why yellow braket? Fault on first iteration
            new_data.push_back(next); 
            index++;
        }
        n1 = 0;
        n2 = size;
        data = new_data;
    }

    return temp;
}

/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    if (isEmpty()) return T();

    n2 -= 1;
    T temp = data[n2];
    data.pop_back();

    int size = n2 - n1;
    if (size <= n1) {
        vector<T> new_data;
        int index = n1;
        for (int i = 0; i < size; i++) {
            new_data.push_back(data[index]); // works? 
            index++;
        }
        n1 = 0;
        n2 = size;
        data = new_data;
    }
    return temp;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */
    if (isEmpty()) return T();
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
     */
    if (n2 == 0 || isEmpty()) return T();
    int index = n2-1;
    return data[index];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
     */
    return n1 == n2;
}
