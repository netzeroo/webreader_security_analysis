#pragma once

#include <string>
#include <drogon/HttpController.h>

using HttpCallback = std::function<void(const drogon::HttpResponsePtr&)>;
using CSR = const std::string&;
