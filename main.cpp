#include "json/json.h"
#include <iostream>

// using namesapce std;

class JsonSerializer
{
public:
   virtual ~JsonSerializer( void ) {};
   virtual void Serialize( Json::Value& root ) =0;
   virtual void Deserialize( Json::Value& root) =0;
};


class Test : public JsonSerializer
{
public:
   Test( void );
   virtual ~Test( void );
   virtual void Serialize( Json::Value& root );
   virtual void Deserialize( Json::Value& root);
 
private:
   int           testInt;
   double        testFloat;
   std::string   testString;
   bool          testBool;
};

Test::Test(void) {
 //nothing
}

Test::~Test(void) {
 //nothing
}

void Test::Serialize( Json::Value& root )
{
   // serialize primitives
   root["testintA"] = testInt;
   root["testfloatA"] = testFloat;
   root["teststringA"] = testString;
   root["testboolA"] = testBool;
}
 
void Test::Deserialize( Json::Value& root )
{
   // deserialize primitives
   testInt = root.get("testintA",0).asInt();
   testFloat = root.get("testfloatA", 0.0).asDouble();
   testString = root.get("teststringA", "").asString();
   testBool = root.get("testboolA", false).asBool();
}


class CJsonSerializer
{
public:
   static bool Serialize( JsonSerializer* pObj, std::string& output );
   static bool Deserialize( JsonSerializer* pObj, std::string& input );
 
private:
   CJsonSerializer( void ) {};
};


bool CJsonSerializer::Serialize( JsonSerializer* pObj, std::string& output )
{
   if (pObj == NULL)
      return false;
 
   Json::Value serializeRoot;
   pObj->Serialize(serializeRoot);
 
   Json::StyledWriter writer;
   output = writer.write( serializeRoot );
 
   return true;
}
 
bool CJsonSerializer::Deserialize( JsonSerializer* pObj, std::string& input )
{
   if (pObj == NULL)
      return false;
 
   Json::Value deserializeRoot;
   Json::Reader reader;
 
   if ( !reader.parse(input, deserializeRoot) )
      return false;
 
   pObj->Deserialize(deserializeRoot);
 
   return true;
}



void output(const Json::Value & value)
{
    // querying the json object is very simple
    std::cout << value["hello"];
    std::cout << value["number"];
    std::cout << value["array"][0] << value["array"][1];
    std::cout << value["object"]["hello"];
}


int main()
{
    std::cout << "Hello World!";
    Test testClass;
std::string input = "{ \"testintA\" : 42, \"testfloatA\" : 3.14159, \"teststringA\" : \"foo\", \"testboolA\" : true }\n";
CJsonSerializer::Deserialize( &testClass, input );
 
std::cout << "Raw Json Input\n" << input << "\n\n";
 
std::string output;
CJsonSerializer::Serialize( &testClass, output);
 
std::cout << "testClass Serialized Output\n" << output << "\n\n\n";


// Json::Value fromScratch;
// Json::Value array;
// array.append("hello");
// array.append("world");
// fromScratch["hello"] = "world";
// fromScratch["number"] = 2;
// fromScratch["array"] = array;
// fromScratch["object"]["hello"] = "world";

// output(fromScratch);

// // write in a nice readible way
// Json::StyledWriter styledWriter;
// std::cout << styledWriter.write(fromScratch);

// // ---- parse from string ----

// // write in a compact way
// Json::FastWriter fastWriter;
// std::string jsonMessage = fastWriter.write(fromScratch);

// Json::Value parsedFromString;
// Json::Reader reader;
// bool parsingSuccessful = reader.parse(jsonMessage, parsedFromString);
// if (parsingSuccessful)
// {
//     std::cout << styledWriter.write(parsedFromString) << std::endl;
// }

// 	output(fromScratch);

    return 0;
}