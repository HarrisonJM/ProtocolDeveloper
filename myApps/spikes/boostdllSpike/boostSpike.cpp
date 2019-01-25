/*!
 * @brief Testing how to use the boost.dll stuff
 *
 * @author hmarcks
 *
 * @addtogroup spikes
 *
 * @date 16/01/19
 */

#include <boost/dll/int mainshared_library.hpp>         // for shared_library
#include <boost/dll/runtime_symbol_info.hpp>    // for program_location()
#include "static_plugin.hpp"                    // without this headers some compilers may optimize out the `create_plugin` symbol
#include <boost/function.hpp>
#include <iostream>

namespace dll = boost::dll;

int main()
{
    dll::shared_library self(dll::program_location());

    std::cout << "Call function" << std::endl;
    boost::function<boost::shared_ptr<my_plugin_api>()> creator
        = self.get_alias<boost::shared_ptr<my_plugin_api>()>("create_plugin");

    std::cout << "Computed Value: " << creator()->calculate(2
                                                            , 2) << std::endl;
}
 
 

