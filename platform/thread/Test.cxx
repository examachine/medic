//
//
// C++ Implementation for module: Test
//
// Description: 
//
//
// Author: exa
//
//


#include "Thread.hxx"
#include "Mutex.hxx"
#include "Semaphore.hxx"
//#include "Monitor.hxx"
//#include "Critical_Region.hxx"
#include "Condition.hxx"
#include "Shared_Queue.hxx"
#include "Integral.hxx"

class MyThread : public Thread
{
public:
  MyThread() {
    cout << "Thread created" << endl;    
  }
  void run() {
    cout << "Here I am!" << endl;
  }
};

void wait_key() {
  cout << "Press enter" << endl;

  cin.get();
}

void test_thread() {
  MyThread t;
  wait_key();
}

void test_mutex() {
  Mutex mutex;
}

void test_semaphore() {
  //Semaphore sem(1);
}


const int n = 10;

class Products : public Monitor_Base
{
public:
  Products() : count(0), full(this), empty(this), Monitor_Base("Products") {
    srand(time(0));
  }

  void produce() {
    soft_enter();
    if (count==n) full.wait();
    count++;
    cout << "Producer: count = " << count << endl;
    if (count==1) empty.signal();
    leave();
  }

  void consume() {
    soft_enter();
    if (count==0) empty.wait();
    count--;
    cout << "Consumer: count = " << count << endl;
    if (count==n-1) full.signal();
    leave();
  }

  Condition full, empty;
  int count;
};

Products products;

class Producer : public Thread {
public:
  Producer() {
    cout << "Producer thread created" << endl;
    count=0;
  }
  
  int count;

  void run() {
    do {
      products.produce();
      count++;
    } while (count<700);
    cout << "Producer thread terminated" << endl;
  }
};

class Consumer : public Thread {
public:
  Consumer() {
    cout << "Consumer thread created" << endl;
  }

  void run() {
    do {
      products.consume();
    } while (1);
    cout << "Consumer thread terminated" << endl;
  }
};

void test_producer_consumer()
{
  cout << "Creating a producer and a consumer thread" << endl;

  cout << "First creating a producer" << endl;
  Producer producer;

  cout << "Then creating a consumer" << endl;
  Consumer consumer;

  cout << "Waiting for threads to terminate" << endl;
  //Thread::wait(consumer);

  Thread::wait(producer);
  cout << "Test completed" << endl;
  return;
}

void test_queue()
{
  static Shared_Queue<int> queue(10);

  class Producer : public Thread {
  public:
    Producer() {
      cout << "Producer thread created with id " << sel_thread_id()
	   << endl;
      count = 0;
    }

    int count;

    void run() {
      do {
	queue.push(rand() % 10);
	cerr << "Produced: Size of the thing is " << queue.size()
	     << endl;
	count++;
      } while (count < 20);
      cout << "Producer thread terminated" << endl;
    }
  };

  class Consumer : public Thread {
  public:
    Consumer() {
      cout << "Consumer thread created with id " << sel_thread_id() << endl;
    }

    void run() {
      do {
	cout << "Consumer thread started" << endl;
	queue.pop();
	cerr << "Consumed: Size of the thing is " << queue.size() << endl;
      } while (1);
      cout << "Consumer thread terminated" << endl;
    }
  };

  cerr << "Main thread [" << pthread_self() << "] "<< endl;

  Producer producer;
  Consumer consumer;

  cout << "Waiting for threads to terminate" << endl;
  cout << "Test completed" << endl;

}

struct fun
{
  fun() {}
  double operator() (double x) {
    return 4.0 / (1 + x*x);
  }
};

struct simple_fun
{
  simple_fun() {}
  double operator() (double x) {
    return x*x;
  }
};

void test_integral()
{
  Integral<simple_fun> integral(0,10);
  cerr << "Computing integral of x*x over (0,10)" << endl;
  double result = integral.approximate(5e-5);
  cerr << "Approximated: " << result << endl;
  //cerr << "Approximations: " << Integral<simple_fun>::count << endl;

  Integral<fun> integral1(0,50);
  cerr << "Computing integral 1 over (0,50)" << endl;
  result = integral1.approximate(5e-5);
  cerr << "Approximated: " << result << endl;
}
