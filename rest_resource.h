#ifndef REST_RESOURCE
#define REST_RESOURCE

#include <stdio.h>
#include <string.h>
#include <ESP8266WebServer.h>


class RESTResource {
public:
    RESTResource(String name, int count);
    ~RESTResource();
    virtual void create(ESP8266WebServer& server);
    void getAll(ESP8266WebServer& server) const;
    void getById(ESP8266WebServer& server, String id) const;
    virtual void updateById(ESP8266WebServer& server, String id);
    virtual void deleteById(ESP8266WebServer& server, String id);

protected:
    String name;
    int count = 0;
    int validateId(ESP8266WebServer& server, String id) const;
    int getIntArg(ESP8266WebServer& server, String name, int min, int max) const;
    int getBoolArg(ESP8266WebServer& server, String name) const;
    String getStringArg(ESP8266WebServer& server, String name) const;
    virtual String print(int id) const = 0;
};

#endif
