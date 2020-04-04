#ifndef __Request_Gadget__
#define __Request_Gadget__

// External Imports
#include <ArduinoJson.h>
#include <cstring>
#include <utility>
#include <IPAddress.h>
#include <WiFi.h>

// Other Imports
#include "../system_settings.h"
#include "../console_logger.h"

enum REQUEST_TYPE {
  REQ_UNKNOWN, REQ_HTTP_GET, REQ_HTTP_POST, REQ_HTTP_PUT, REQ_HTTP_DELETE, RES_HTTP, REQ_MQTT, REQ_SERIAL
};

class Request {
private:
  REQUEST_TYPE type;
  char body[REQUEST_BODY_LEN_MAX]{};
  char path[REQUEST_PATH_LEN_MAX]{};
  std::function<void(Request *)> send_answer;

protected:

  bool can_respond;

  virtual Request *createResponse(const char *res_path, const char *res_body) = 0;

public:
  Request(REQUEST_TYPE req_type, const char *req_path, const char *req_body) :
    type(req_type),
    can_respond(false) {
    Serial.println("Creating Request Gadget");
    strncpy(path, req_path, REQUEST_PATH_LEN_MAX);
    strncpy(body, req_body, REQUEST_BODY_LEN_MAX);
    Serial.println(path);
    Serial.println(body);
  }

  Request(REQUEST_TYPE req_type, const char *req_path, const char *req_body, std::function<void(Request *request)> answer_method) :
    type(req_type),
    can_respond(true) {
    Serial.println("Creating Request Gadget 2");
    strncpy(path, req_path, REQUEST_PATH_LEN_MAX);
    strncpy(body, req_body, REQUEST_BODY_LEN_MAX);
    send_answer = answer_method;
  }

  virtual ~Request() {
    Serial.println("Default Destructor");
  };

  bool respond(const char *res_path, const char *res_body) {
    if (!can_respond)
      return false;
    send_answer(createResponse(res_path, res_body));
    Serial.println("responded");
    return true;
  }

  REQUEST_TYPE getType() {
    return type;
  }

  const char *getPath() {
    return &path[0];
  }

  const char *getBody() {
    return &body[0];
  }


};

class Request_Gadget {
protected:
  bool request_gadget_is_ready;

  QueueHandle_t in_request_queue;

  QueueHandle_t out_request_queue;

  void addIncomingRequest(Request *request) {
    xQueueSend(in_request_queue, request, portMAX_DELAY);
  };

  virtual void executeRequestSending(Request *req) = 0;

  void sendQueuedItems() {
    if (!request_gadget_is_ready) {
      return;
    }
    if (uxQueueMessagesWaiting(out_request_queue) > 0) {
      Request *buf_req;
      xQueueReceive(out_request_queue, &buf_req, portMAX_DELAY);
      Serial.println(buf_req->getPath());
      executeRequestSending(buf_req);
      delete buf_req;
    }
  }

public:
  Request_Gadget() :
    request_gadget_is_ready(false) {
    in_request_queue = xQueueCreate(REQUEST_QUEUE_LEN, sizeof(Request *));
    out_request_queue = xQueueCreate(REQUEST_QUEUE_LEN, sizeof(Request *));
  }

  explicit Request_Gadget(JsonObject data) :
    request_gadget_is_ready(false) {
    in_request_queue = xQueueCreate(REQUEST_QUEUE_LEN, sizeof(Request *));
    out_request_queue = xQueueCreate(REQUEST_QUEUE_LEN, sizeof(Request *));
  }

  bool requestGadgetIsReady() {
    return request_gadget_is_ready;
  }

  bool hasRequest() {
    return uxQueueMessagesWaiting(in_request_queue) > 0;
  }

  Request *getRequest() {
    Request *buf_req;
    xQueueReceive(in_request_queue, &buf_req, portMAX_DELAY);
    return buf_req;
  }

  void sendRequest(Request *request) {
    Serial.println("queue");
    xQueueSend(out_request_queue, request, portMAX_DELAY);
  };

  virtual void refresh() = 0;
};

#endif //__Request_Gadget__