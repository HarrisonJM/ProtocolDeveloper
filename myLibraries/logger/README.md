#Library: logger

__Description__
The logging classes collection. This library is devoted to thread safe logging, complete with a handler specifically 
designed to remove as much processing away from the main running threads as physically possible.
Can output messages either to a dedicated std::filestream or to std::cout/std::cerr.

__Gotchas__

__How to use__

Components that wish to use logging should have ac opy of the log interface to write to only. Components that wish to 
log should be totally agnostic of the handler. 

__Method__