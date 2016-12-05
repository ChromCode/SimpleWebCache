#include "HTTPFORMXMLService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"

// compose the reply body from the maps built up of the form field. The reply body is a HTML stream containing to HTML tables.
// The first table presents the HTML form fields in their raw format and the second table presents the HTML form fields after URL decoding them
string HTTPFORMXMLService::compose_reply()
{
    // The reply string contains the HTML stream. We compose it step by step
    string reply = "<HTMLForm>";
     // for_each iterator loop over form_data with lambda function to build the second HTML table body    
    for_each (form_data.begin(),form_data.end(),[&reply](const std::pair<string,string>& it) -> bool {
            reply += "<";
            reply += std::get<0>(it);
            reply += ">";
            reply += std::get<1>(it);
            reply += "</";
            reply += std::get<0>(it);
            reply += ">";
            return true; 
    });
    reply += "</HTMLForm>";
    return reply; // return reply

}
HTTPFORMXMLService::HTTPFORMXMLService( )
        :HTTPFORMService() {} // Constructor setting data members using initialization list

// Execute  the HTTPFORM service 
bool HTTPFORMXMLService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)
{
    parse_data(p_httpRequest); // parse the request body data
    string reply = compose_reply(); // compose the HTTP reply body
    //Build and set the HTTP response Header fields.
    HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
    httpResponseHeader->setHeader("Content-Type","application/xml");
    httpResponseHeader->setHeader("Connection","close");
    httpResponseHeader->setHeader("Content-Length",to_string(reply.length()));
    httpResponseHeader->respond(); // Write back the response to the client through the TCPSocket
    // Write back the file to the client through the TCPSocket
    p_tcpSocket->writeToSocket(reply.c_str(),reply.length());
    delete (httpResponseHeader); // Delete the HTTP Response
    return true; // return true
}
// Clone a new identical object and return it to the caller
HTTPService * HTTPFORMXMLService::clone ()
{
    // Instantiate an HTTPHTMLService object and set it up with the same fileCache. 
    // Notice that the clean flag is set to false as the current object will be carrying this out.
    return new HTTPFORMXMLService();  
}
HTTPFORMXMLService::~HTTPFORMXMLService(){} // Destructor
