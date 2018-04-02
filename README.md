# esp8266-rest-handler

REST handler for ESP8266 based on the [RequestHandler](https://github.com/esp8266/ESPWebServer/blob/master/src/detail/RequestHandler.h)

## Usage

Create a class which inherit form `RESTResource` and implement `create`, `updateById` and `deleteById` based on your needs. If you don't override this functions the API will return, that they are not defined, so that you only need to implement the functions you really use. For the GET Requests a `print` function, that return a JSON object for one element, is required.

```cpp
#include <rest_resource.h>

class SampleResource : public RESTResource {
public:
    SampleResource();

    # Definition and implementation of create, updateById and deleteById is optional
    # virtual void create(ESP8266WebServer& server);
    # virtual void updateById(ESP8266WebServer& server, String id);
    # virtual void deleteById(ESP8266WebServer& server, String id);
private:
    virtual String print(int id) const;
};

# don't forget to call the constructor of the super class
# first parameter specifies the name of the resource and the second the number of elements (can be changed later by modifying the 'count' variable)
SampleResource::SampleResource() : RESTResource("sample", 0) {

}

virtual String SampleResource::print(int id) const {
    char buffer[50];
    sprintf(buffer, "{ \"id\": %d }", id);
    return buffer;
}
```