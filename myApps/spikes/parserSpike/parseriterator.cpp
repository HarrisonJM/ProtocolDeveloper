/*!
 * @brief implements a basic test for using the rapidxml iterators
 *
 * It actually doesnt' because the iterators appear to broken - I'm not fixing them now though...
 */

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
//#include "rapidxml/rapidxml_iterators.hpp"

#include <iostream>
#include <fstream>

int main()
{
    rapidxml::xml_document<> doc;    // character type defaults to char

    rapidxml::xml_node<>* root_node;
    std::cout << "gettingFile" << std::endl;
    std::ifstream xmlFile("test.xml");
    std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile))
                             , std::istreambuf_iterator<char>());
    buffer.push_back('\0');


//    rapidxml::node_iterator<char> begIt( doc.first_node());
//    rapidxml::node_iterator<> endIt;
}