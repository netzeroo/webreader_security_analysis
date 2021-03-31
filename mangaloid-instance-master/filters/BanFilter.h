#pragma once

#include <drogon/HttpFilter.h>

using namespace drogon;

class GlobalBanFilter : public drogon::HttpFilter<GlobalBanFilter> {
public:
    virtual void doFilter (const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback&& fccb);
};
