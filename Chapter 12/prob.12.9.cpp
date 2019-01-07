/*
 *
 * Smart Pointer: Write a smart pointer class. A smart pointer is a data type, usually implemented with
 * templates, that simulates a pointer while also providing automatic garbage collection. It automatically
 * counts the number of references to a SmartPointer<T*> object and frees the object of type
 * T when the reference count hits zero.
 */

#include <stdio.h>
#include <stdlib.h>

/* A smart pointer class to simulate pointers with automatic garbage collection. */
/* The SmartPointer class does not allocate the inner pointer (it is passed through the constructor)*/
/* However, it de-allocates (and runs the desctructor) one the inner pointer when its ref count get to 0 */
/* If users desire, they can change this allocation behavior (and change the API accordingly) */
template<class T> class SmartPointer
{
private:
    T* inner_pointer;
    int * ref_count;
public:
    SmartPointer() {inner_pointer = NULL; ref_count = NULL;}
    SmartPointer(T * t){inner_pointer = t;ref_count = new int; *ref_count = 1; }
    
    SmartPointer& operator= (const SmartPointer &args)
    {
        if (this != &args)
        {
			inner_pointer = args.inner_pointer;
            ref_count = args.ref_count;
            (*ref_count)++;
        }
        return * this;
    }
    T& operator* ()
    {
        return *this->inner_pointer;
    }

    T * operator->()
    {
        return this->inner_pointer;
    }
    
    ~SmartPointer()
    {
        if (!ref_count)
        {
            return;
        }
        (* ref_count) --;
        if (*ref_count == 0)
        {
            delete inner_pointer;
            delete ref_count;
			printf("deleted the inner pointer and the ref_count mem.\n");
        }
    }
};

class test_class
{
private:
	int private_int;
public:
	test_class() {}
	~test_class(){printf("in the destructor for the test class.\n");}
	int public_int;
	void print(){printf("public int is %d; private int is %d.\n", public_int, private_int);}
	void set_public_int(int new_value) {public_int = new_value;}
	void set_private_int(int new_value) {private_int = new_value;}
};

void test_integer_pointer();
void test_class_type();

int main()
{
	test_integer_pointer();
	test_class_type();
	return 0;
}

void test_integer_pointer()
{
	int * int_test = new int;
	*int_test = 10;
	SmartPointer<int> sp_int = SmartPointer<int>(int_test);
	/* test getting the value from inner pointer */
	printf("inner pointer value is: %d.\n", *sp_int);
	/* test setting the value into the inner pointer */
	*sp_int = 100;
	printf("check the value written onto the integer: %d.\n", *int_test);
	
	/* test the assignment operator */
	SmartPointer<int> u, v, t;
	u = sp_int;
	v = u;
	t = v;
	
	/* test getting the vaue from inner pointer after assignment */
	printf("inner pointer value is: %d.\n", *t);
	
	/* test setting the value into the inner pointer after assignment */
	*t = 1000;
	printf("check the value written onto the integer: %d.\n", *int_test);
	
	/* now the we fall off the function, the destructor for all SmartPointers should */
	/* run and int_test should be deleted only once. */
}

void test_class_type()
{
	test_class * tc = new test_class();
	tc->public_int = 1;
	SmartPointer<test_class> sp = SmartPointer<test_class>(tc);
	
	/* test accessing the public members of t via the SmartPointer */
	printf("accessing the public integer via SmartPointer shows %d.\n", sp->public_int);
	printf("test assignment operator\n");
	SmartPointer<test_class> t, u, v;
	t = sp;
	u = t;
	v = u;

	printf("calling the set methods and print methods via different SmartPointer should change the same inner pointer:\n\t");
	t->set_private_int(10);
	u->set_public_int(100);
	v->print();
	
	sp->public_int = 200;
	printf("set the public field via the SmartPointer shows %d.\n", sp->public_int);
	
	printf("now the destructors for all the SmartPointers are run. The destructor for the inner pointer should run only once.\n");
}
