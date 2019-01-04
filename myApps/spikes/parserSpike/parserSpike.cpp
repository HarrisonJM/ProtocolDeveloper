/*
 * This file will act as an example parser
 * It was later decided to haev testcases written in XML as that appears to be a more standard approach
 * http://lisperator.net/pltut/parser/input-stream
 * http://www.mprazak.info/posts/a-simple-c-tokenizer/
 * https://www.dreamincode.net/forums/topic/110782-c-beginner-parser-class-tutorial/
 * http://www.bayfronttechnologies.com/mc_tutorial.html
 * http://www.setnode.com/blog/quick-notes-on-how-to-use-rapidxml/
 * https://stackoverflow.com/questions/5443073/read-a-line-from-xml-file-using-c/5443512#5443512
 *
 */

#include <rapidxml/rapidxml.hpp>
//#include <rapidxml/rapidxml_utils.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

void walk(const rapidxml::xml_node<>* node
          , int indent);

void BuildString(char* startError // Where the error is, the middle point
                 , std::string& out
                 , std::vector<char> const& buffer)
{
    /* Get the index */
    unsigned long errorPosition = startError - buffer.data();
    unsigned long bufferSize = buffer.size();
    unsigned long readFrom = errorPosition - 12;
    /* overflow */
    if (readFrom > errorPosition)
    {
        readFrom = 0;
    }

    unsigned long readUpto = errorPosition + 12;
    /* out of range */
    if (readUpto > bufferSize)
    {
        readUpto = bufferSize - 1;
    }

    for (int i = readFrom; i < readUpto; ++i)
    {
        out += buffer[i];
    }
}

int main(int argc
         , char** argv)
{
    // https://gist.github.com/JSchaenzle/2726944
    rapidxml::xml_document<> doc;    // character type defaults to char

    rapidxml::xml_node<>* root_node;
    std::cout << "gettingFile" << std::endl;
    std::ifstream xmlFile("/home/hmarcks/src/ProtocolDeveloper/myApps/spikes/parserSpike/test.xml");
    std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile))
                             , std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    //for ( auto blah : buffer )
    //std::cout << blah << std::endl;

    std::cout << "init doc" << std::endl;
    try
    {
        doc.parse<0>(&buffer[0]);    // 0 i the template means default parse flags
    } catch (rapidxml::parse_error& p)
    {
        std::cout << "What: " << p.what() << std::endl;

        std::string place;
        std::cout << "Where addr: " << p.where<char>() << std::endl;
        BuildString(p.where<char>()
                    , place
                    , buffer);

        std::cout << "Where: " << place << std::endl;
        exit(1);
    }

    std::cout << "Starting" << std::endl;
    root_node = doc.first_node();
    std::cout << "Post Starting" << std::endl;

    walk(root_node
         , 0);

    return 0;
}

// next_sibling will get a node OR the next attribute
// https://gist.github.com/t-mat/7150417
void walk(const rapidxml::xml_node<>* node
          , int indent = 0)
{
    const auto ind_s = std::string(indent*4
                                   , ' ');
    printf("%s"
           , ind_s.c_str());

    const rapidxml::node_type t = node->type();

    switch (t)
    {
        case rapidxml::node_element:
        {
            std::cout << "node_element" << std::endl;
            printf("<%.*s"
                   , node->name_size()
                   , node->name());
            for (const rapidxml::xml_attribute<>* a = node->first_attribute(); a; a = a->next_attribute()
                )
            {
                printf(" %.*s"
                       , a->name_size()
                       , a->name());
                printf("='%.*s'"
                       , a->value_size()
                       , a->value());
            }
            printf(">\n");

            for (const rapidxml::xml_node<>* n = node->first_node(); n; n = n->next_sibling()
                )
            {
                walk(n
                     , indent + 1);
            }

            printf("%s</%.*s>\n"
                   , ind_s.c_str()
                   , node->name_size()
                   , node->name());
        }
            break;

        case rapidxml::node_data:
            printf("DATA:[%.*s]\n"
                   , node->value_size()
                   , node->value());
            break;

        default:
            printf("NODE-TYPE:%d\n"
                   , t);
            break;
    }
}
