/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "/USERS/ericpoels/MakeUpTest/SimpleWebCache/headers/HTTPXMLFORMService.h"
//#include "/USERS/ericpoels/MakeUpTest/SimpleWebCache/headers/HTTPFormService.h"
#include "/USERS/ericpoels/MakeUpTest/SimpleWebCache/headers/HTTPResponseHeader.h"
#include "/USERS/ericpoels/MakeUpTest/SimpleWebCache/headers/HTTPNotFoundExceptionHandler.h"

string HTTPXMLFORMService::compose_reply(){
    string reply = "<HTMLForm>";
    reply += "<RawData>";
    // for_each iterator loop over raw_form_data with lambda function to build the first HTML table body
    for_each (raw_form_data.begin(),raw_form_data.end(),[&reply](const std::pair<string,string>& it) -> bool {
            reply += "<";
            reply += std::get<0>(it);
            reply += ">";
            reply += std::get<1>(it);
            reply += "</";
            reply += std::get<0>(it);
            reply += ">";
            return true; 
    });
    reply += "</RawData>";
    reply += "<ParsedData>";    // Second HTML Table
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
    reply += "</ParsedData>";
    reply += "</HTMLForm>";
    return reply; // return reply

}

HTTPXMLFORMService::HTTPXMLFORMService( )
        :HTTPFORMService() {} // Constructor setting data members using initialization list

bool HTTPXMLFORMService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket) {
    parse_data(p_httpRequest); // parse the request body data
    string reply = compose_reply(); // compose the HTTP reply body
    //Build and set the HTTP response Header fields.
    HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
    httpResponseHeader->setHeader("Content-Type","text/xml");
    httpResponseHeader->setHeader("Connection","close");
    httpResponseHeader->setHeader("Content-Length",to_string(reply.length()));
    httpResponseHeader->respond(); // Write back the response to the client through the TCPSocket
    // Write back the file to the client through the TCPSocket
    p_tcpSocket->writeToSocket(reply.c_str(),reply.length());
    delete (httpResponseHeader); // Delete the HTTP Response
    return true; // return true
    return true;
}

HTTPService * HTTPXMLFORMService::clone ()
{
    // Instantiate an HTTPHTMLService object and set it up with the same fileCache. 
    // Notice that the clean flag is set to false as the current object will be carrying this out.
    return new HTTPXMLFORMService();  
}
HTTPXMLFORMService::~HTTPXMLFORMService(){} // Destructor
