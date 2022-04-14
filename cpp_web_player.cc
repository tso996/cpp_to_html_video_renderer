

#include <emscripten/bind.h>
#include <emscripten/val.h>

using emscripten::val;
using namespace emscripten;


class MyClass {
public:
  uint8* data;
  thread_local const val document;



  MyClass(){
      data = (uint8*)malloc(4*480*640);
      document = val::global("document");
  }


  std::string runMainProcess(uintptr_t imgData, int imgSize) {
     uint8* imgPtr = reinterpret_cast<uint8*>(imgData);
    

    return "runMainProcess ok";
  }

  static std::string getStringFromInstance(const MyClass& instance) {
    return "instance.y";
  }

  

private:
  
};

// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
  class_<MyClass>("MyClass")
    .constructor<int, std::string>()
    .function("runMainProcess", &MyClass::runMainProcess)
    //.property("x", &MyClass::getX, &MyClass::setX)
    .class_function("getStringFromInstance", &MyClass::getStringFromInstance)
    ;
}