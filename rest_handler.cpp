#include "rest_handler.h"

RESTHandler::RESTHandler(String uri) {
    this->uri = uri;
}

RESTHandler::~RESTHandler() {

}

bool RESTHandler::canHandle(HTTPMethod method, String uri) {
    if (uri.startsWith(this->uri)) {
        return true;
    }
}

bool RESTHandler::canUpload(String uri) {
    return false;
}

bool RESTHandler::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {
    #ifdef DEBUG_REST
    Serial.println(requestUri);
    Serial.print("Method: ");
    Serial.println(requestMethod);
    for (int i = 0; i < server.args(); i++) {
        Serial.print(server.argName(i));
        Serial.print(": ");
        Serial.println(server.arg(i));
    }
    #endif

    requestUri.replace(this->uri, "");

    std::vector<String>* uri = new std::vector<String>();
    int pos;
    while (requestUri.length() > 1) {
        requestUri.remove(0, 1);
        pos = requestUri.indexOf('/');
        if (pos == -1) {
            pos = requestUri.length();
        }
        uri->push_back(requestUri.substring(0, pos));
        requestUri = requestUri.substring(pos);
    }

    String error = "";
    switch (requestMethod) {
        case HTTP_GET:
            if (uri->capacity() == 0) {
                this->resource->getAll(server);
            } else if (uri->capacity() == 1) {
                this->resource->getById(server, uri->at(0));
            } else {
                error = "bad request";
            }
            break;
        case HTTP_POST:
            this->resource->create(server);
            break;
        case HTTP_PATCH:
        case HTTP_PUT:
            if (uri->capacity() == 1) {
                this->resource->updateById(server, uri->at(0));
            } else {
                error = "bad request";
            }
            break;
        case HTTP_DELETE:
            if (uri->capacity() == 1) {
                this->resource->deleteById(server, uri->at(0));
            } else {
                error = "bad request";
            }
        default:
            error = "unknown operation";
            break;
    }
    if (error != "") {
        server.send(400, "application/json", "{ \"message\": \"" + error + "\" }");
    }
}

void RESTHandler::upload(ESP8266WebServer& server, String requestUri, HTTPUpload& upload) {}

RequestHandler* RESTHandler::next() {
    return this->nextHandler;
}

void RESTHandler::next(RequestHandler* r) {
    this->nextHandler = r;
}

void RESTHandler::setResource(RESTResource* resource) {
    this->resource = resource;
}
