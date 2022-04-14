
// #include <stdint.h>
// #include <math.h>
#include <emscripten.h>
#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>

// using emscripten::val;
using namespace emscripten;
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


class MyClass {
public:
  uint8_t* data;
  //thread_local const val document;



  MyClass(){
      data = (uint8_t*)malloc(4*480*640);
      //document = val::global("document");
  }


  int runMainProcess(uintptr_t imgData, int imgSize) {
      auto t1 = high_resolution_clock::now();  


     uint8_t* imgPtr = reinterpret_cast<uint8_t*>(imgData);
     //std::cout << imgPtr << std::endl;
    //  for (int ptr = 0; ptr < imgSize; ptr += 4) {
    //     // rgba
    //     data[ptr] = *imgPtr;
    //     imgPtr ++;
    //     data[ptr + 1] = *imgPtr;
    //     imgPtr ++;
    //     data[ptr + 2] = *imgPtr; //(255*w) / 500;
    //     imgPtr ++;
    //     data[ptr + 3] = *imgPtr; 
    //     imgPtr ++;
    // }
     std::cout << "its working" << std::endl;


     //===========================================
          //execution time....
          auto t2 = high_resolution_clock::now();
          auto ms_int = duration_cast<milliseconds>(t2 - t1);
          duration<double, std::milli> ms_double = t2 - t1;
          return ms_int.count();
  }

  static std::string getStringFromInstance(const MyClass& instance) {
    return "this function is not defined yet";
  }

  

private:
  
};

// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
  class_<MyClass>("MyClass")
    .constructor<>()
    .function("runMainProcess", &MyClass::runMainProcess)
    //.property("x", &MyClass::getX, &MyClass::setX)
    .class_function("getStringFromInstance", &MyClass::getStringFromInstance)
    ;
}