#include "rest_resource.h"

RESTResource::RESTResource(String name, int count) {
    this->name = name;
    this->count = count;
}

RESTResource::~RESTResource() {

}

void RESTResource::create(ESP8266WebServer& server) {
    server.send(400, "application/json", "{ \"message\": \"not implemented\" }");
}

void RESTResource::getAll(ESP8266WebServer& server) const {
    String res = "";

    res = "{ \"" + this->name + "\": [";
    for (int i = 0; i < count; i++) {
        res += print(i);
        if (i != count - 1)
        {
            res += ",";
        }
    }
    res += "]}";
    server.send(200, "application/json", res);
}

void RESTResource::getById(ESP8266WebServer& server, String id) const {
    int c;
    if ((c = validateId(server, id)) != -1) {
        server.send(200, "application/json", "{ \"fan\": " + print(c) + "}");
    }
}

void RESTResource::updateById(ESP8266WebServer& server, String id) {
    server.send(400, "application/json", "{ \"message\": \"not implemented\" }");
}

void RESTResource::deleteById(ESP8266WebServer& server, String id) {
    server.send(400, "application/json", "{ \"message\": \"not implemented\" }");
}

int RESTResource::validateId(ESP8266WebServer& server, String id) const {
    int c = id.toInt();
    if (c >= 0 && c < count) {
        return c;
    } else {
        server.send(404, "application/json", "{ \"message\": \"not found\" }");
        return -1;
    }
}

int RESTResource::getIntArg(ESP8266WebServer& server, String name, int min, int max) const {
    String argString;
    if (server.hasArg(name)) {
        int arg = server.arg(name).toInt();
        if (arg >= min && arg <= max) {
            return arg;
        }
        server.send(400, "application/json", "{ \"message\": \"" + name + " is not an integer\" }");
        // handle plain arg
    }
    return -1;
}

int RESTResource::getBoolArg(ESP8266WebServer& server, String name) const {
    if (server.hasArg(name)) {
        if (server.arg(name).equals("true")) {
            return 1;
        } else if (server.arg(name).equals("false")) {
            return 0;
        }
        server.send(400, "application/json", "{ \"message\": \"" + name + " is not a boolean\" }");
        // handle plain arg
    }
    return -1;
}

String RESTResource::getStringArg(ESP8266WebServer& server, String name) const {
    if (server.hasArg(name)) {
        return server.arg(name);
    }
    // handle plain arg
    return "";
}