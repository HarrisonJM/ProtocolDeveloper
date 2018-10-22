/*
 * This file will act as an example parser
 * It was later decided to haev testcases written in XML as that appears to be a more standard approach
 * http://lisperator.net/pltut/parser/input-stream
 * http://www.mprazak.info/posts/a-simple-c-tokenizer/
 * https://www.dreamincode.net/forums/topic/110782-c-beginner-parser-class-tutorial/
 * http://www.bayfronttechnologies.com/mc_tutorial.html
 */

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_utils.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

void walk(const rapidxml::xml_node<>* node, int indent);

int main(int argc, char** argv)
{
    // https://gist.github.com/JSchaenzle/2726944
    rapidxml::xml_document<> doc;    // character type defaults to char

    rapidxml::xml_node<>* root_node;
    std::cout << "gettingFile" << std::endl;
    std::ifstream xmlFile("/home/hmarcks/CLionProjects/ProtocolDeveloper/testCaseAnalyser/sntp.xml");
    std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    //for ( auto blah : buffer )
      //std::cout << blah << std::endl;

    std::cout << "init doc" << std::endl;
    doc.parse<0>(&buffer[0]);    // 0 means default parse flags

    std::cout << "Starting" << std::endl;
    root_node = doc.first_node();
    std::cout << "Post Starting" << std::endl;

    walk(root_node, 0);

    return 0;
}

// next_sibling will get a node OR the next attribute
// https://gist.github.com/t-mat/7150417
void walk(const rapidxml::xml_node<>* node, int indent = 0)
{
    const auto ind = std::string(indent * 4, ' ');
    printf("%s", ind.c_str());

    const rapidxml::node_type t = node->type();
    switch(t)
    {
        case rapidxml::node_element:
        {
            std::cout << "node_element" << std::endl;
            printf("<%.*s", node->name_size(), node->name());
            for(const rapidxml::xml_attribute<>* a = node->first_attribute()
                ; a
                ; a = a->next_attribute()
                )
            {
                printf(" %.*s", a->name_size(), a->name());
                printf("='%.*s'", a->value_size(), a->value());
            }
            printf(">\n");

            for(const rapidxml::xml_node<>* n = node->first_node()
                ; n
                ; n = n->next_sibling()
                )
            {
                walk(n, indent+1);
            }

            printf("%s</%.*s>\n", ind.c_str(), node->name_size(), node->name());
        }
            break;

        case rapidxml::node_data:
            printf("DATA:[%.*s]\n", node->value_size(), node->value());
            break;

        default:
            printf("NODE-TYPE:%d\n", t);
            break;
    }
}
