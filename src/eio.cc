#include <v8.h>
#include <node.h>
#include <node_version.h>

#include <sstream>
#include <iostream>

using namespace v8;
using namespace node;

#if NODE_VERSION_AT_LEAST(0, 9, 4)
    // do nothing
#else
    #define LIBUV_HAS_EV
#endif

Handle<Value> SetMinParallel(const Arguments& args) {
    HandleScope scope;
    if (args.Length() < 1 || !args[0]->IsUint32()) {
        return ThrowException(Exception::TypeError(String::New("Expected number of threads")));
    }

#ifdef LIBUV_HAS_EV
    eio_set_min_parallel(args[0]->Uint32Value());
#else
    std::stringstream s;
    s << "node-eio has no effect with your node version (" << NODE_VERSION << ")"
      << " set UV_THREADPOOL_SIZE at startup instead";
    std::clog << s.str() << "\n";
#endif
    return scope.Close(Undefined());
}

Handle<Value> SetMaxParallel(const Arguments& args) {
    HandleScope scope;
    if (args.Length() < 1 || !args[0]->IsUint32()) {
        return ThrowException(Exception::TypeError(String::New("Expected number of threads")));
    }
#ifdef LIBUV_HAS_EV
    eio_set_max_parallel(args[0]->Uint32Value());
#else
    std::stringstream s;
    s << "node-eio has no effect with your node version (" << NODE_VERSION << ")"
      << " set UV_THREADPOOL_SIZE at startup instead";
    std::clog << s.str() << "\n";
#endif
    return scope.Close(Undefined());
}

Handle<Value> Usage(const Arguments& args) {
    HandleScope scope;

    Local<Object> info = Object::New();
#ifdef LIBUV_HAS_EV
    unsigned int io_reqs = eio_nreqs(),
        io_active = eio_nthreads(),
        io_pending = eio_npending();

    info->Set(String::NewSymbol("requests"), Integer::NewFromUnsigned(io_reqs));
    info->Set(String::NewSymbol("active"), Integer::NewFromUnsigned(io_active));
    info->Set(String::NewSymbol("pending"), Integer::NewFromUnsigned(io_pending));
#else
    info->Set(String::NewSymbol("requests"), Undefined());
    info->Set(String::NewSymbol("active"), Undefined());
    info->Set(String::NewSymbol("pending"), Undefined());
#endif

    return scope.Close(info);
}


extern "C" void init(Handle<Object> target) {
    NODE_SET_METHOD(target, "setMinParallel", SetMinParallel);
    NODE_SET_METHOD(target, "setMaxParallel", SetMaxParallel);
    NODE_SET_METHOD(target, "usage", Usage);
}

NODE_MODULE(eio, init);
