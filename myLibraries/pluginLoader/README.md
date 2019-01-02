#Library: pluginLoader

__Description__
This library is dedicated to loading and registering plugins for use by the system.

__Gotchas__
Currently will unload all previously loaded plugins when asked to re-read for new plugins, however plugins are stored 
as shared pointers and therefore should remain with any objects that still contain references to them.

__How to use__

__Method__