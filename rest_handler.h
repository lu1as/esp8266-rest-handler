#ifndef RESTHANDLER_H
#define RESTHANDLER_H

#include <stdio.h>
#include <string.h>
#include <ESP8266WebServer.h>

#include <rest_resource.h>

//#define DEBUG_REST

class RESTHandler : public RequestHandler {
public:
    RESTHandler(String uri);
    ~RESTHandler();
    bool canHandle(HTTPMethod method, String uri);
    bool canUpload(String uri);
    bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri);
    void upload(ESP8266WebServer& server, String requestUri, HTTPUpload& upload);

    RequestHandler* next();
    void next(RequestHandler* r);
    void setResource(RESTResource* resource);

private:
    RequestHandler* nextHandler = nullptr;
    String uri;
    RESTResource* resource;
};

#endif
