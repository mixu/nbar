#include <v8.h>
#include <node.h>
#include <string.h>

extern "C" {
  #include "nbar.h"
}

using namespace node;
using namespace v8;

static void EventLoop(EV_P_ struct ev_io* watcher, int revents);
ev_io watcher;

static Handle<Value> Start(const Arguments& args) {
  HandleScope scope;
  fprintf( stdout, "EIO INIT\n");

  int fd = nbar_init();
  ev_io_init(&watcher, EventLoop, fd, EV_READ);
  watcher.data = NULL;
  ev_io_start(EV_DEFAULT_ &watcher);

  return Undefined();
}

static void EventLoop(EV_P_ struct ev_io* watcher, int revents) {
  fprintf( stdout, "EIO LOOP\n");
  nbar_loop();
}

extern "C" {
  void init(Handle<Object> target) {
    HandleScope scope;

    target->Set(String::New("start"), FunctionTemplate::New(Start)->GetFunction());
  }

  NODE_MODULE(nbar, init);
}
