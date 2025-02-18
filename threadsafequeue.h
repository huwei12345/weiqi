#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE
#include <QMutex>
#include <QQueue>
#include <QMutexLocker>

template<typename T>
class ThreadSafeQueue {
private:
    QQueue<T> queue;
    mutable QMutex mutex;

public:
    ThreadSafeQueue() {}

    void enqueue(const T& item) {
        QMutexLocker locker(&mutex);
        queue.enqueue(item);
    }

    bool dequeue(T& item) {
        QMutexLocker locker(&mutex);
        if (queue.isEmpty()) {
            return false;
        }
        item = queue.dequeue();
        return true;
    }

    bool isEmpty() const {
        QMutexLocker locker(&mutex);
        return queue.isEmpty();
    }

    int size() const {
        QMutexLocker locker(&mutex);  // 加锁以保证线程安全
        return queue.size();
    }

    void clear() {
        T t;
        while (!isEmpty()) {
            dequeue(t);
        }
    }
};
#endif
