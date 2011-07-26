#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

Handle<Value> SetMinParallel(const Arguments& args) {
    HandleScope scope;
    if (args.Length() < 1 || !args[0]->IsUint32()) {
        return ThrowException(Exception::TypeError(String::New("Expected number of threads")));
    }

    eio_set_min_parallel(args[0]->Uint32Value());
    return scope.Close(Undefined());
}

Handle<Value> SetMaxParallel(const Arguments& args) {
    HandleScope scope;
    if (args.Length() < 1 || !args[0]->IsUint32()) {
        return ThrowException(Exception::TypeError(String::New("Expected number of threads")));
    }

    eio_set_max_parallel(args[0]->Uint32Value());
    return scope.Close(Undefined());
}

Handle<Value> Usage(const Arguments& args) {
    HandleScope scope;

    unsigned int io_reqs = eio_nreqs(),
        io_active = eio_nthreads(),
        io_pending = eio_npending();

    Local<Object> info = Object::New();
    info->Set(String::NewSymbol("requests"), Integer::NewFromUnsigned(io_reqs));
    info->Set(String::NewSymbol("active"), Integer::NewFromUnsigned(io_active));
    info->Set(String::NewSymbol("pending"), Integer::NewFromUnsigned(io_pending));

    return scope.Close(info);
}


extern "C" void init(Handle<Object> target) {
    NODE_SET_METHOD(target, "setMinParallel", SetMinParallel);
    NODE_SET_METHOD(target, "setMaxParallel", SetMaxParallel);
    NODE_SET_METHOD(target, "usage", Usage);
}
