/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 07/04/19
 */

#include <magic.h>
#include <boost/filesystem.hpp>
#include <boost/range.hpp>
#include <iostream>

using namespace boost;
namespace fs = filesystem;

int main()
{
    // /home/hmarcks/src/builds/protDev-debug/myLibraries/helloWorldProtocol/libhelloWorldProtocol.so
    auto handle = ::magic_open(MAGIC_NONE | MAGIC_COMPRESS);
    ::magic_load(handle
                 , nullptr);

    for (fs::directory_entry const&
            x : make_iterator_range(fs::directory_iterator("/home/hmarcks/src/builds/protDev-debug/myLibraries/helloWorldProtocol")
                                    , {}))
    {
        auto type = ::magic_file(handle
                                 , x.path().native().c_str());
        std::cout << x.path() << "\t" << (type ? type : "UNKOWN") << "\n";
    }
}

