#include <node.h>

using namespace v8;
namespace demo
{
  int32_t fpow(int32_t a,int32_t n,int32_t mod)
  {
    int64_t sum=1,base=a;
    while(n!=0)
    {
      if(n%2)sum=sum*base%mod;
      base=base*base%mod;
      n/=2;
    }
    return sum;
  }

  void Method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if(args.Length()!=3){
      isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,"wdnmd!").ToLocalChecked()));
      return;
    }
    int32_t a = args[0]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    int32_t n = args[1]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    int32_t mod = args[2]->IntegerValue(isolate->GetCurrentContext()).ToChecked();
    args.GetReturnValue().Set(fpow(a,n,mod));
  }


  void Init(Local<Object> exports) {
    NODE_SET_METHOD(exports,"fpow",Method);
  }

  NODE_MODULE(hello, Init)
  
}
