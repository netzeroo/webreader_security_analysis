#pragma once

#include <drogon/HttpFilter.h>
#include <unordered_map>
#include <ctime>

using namespace drogon;

class TimeFilter : public drogon::HttpFilter<TimeFilter> {
    static constexpr int minTime = 1;
    std::unordered_map<std::string, time_t> lastPostReq;
public:
    virtual void doFilter (const HttpRequestPtr& req, FilterCallback&& fcb, FilterChainCallback&& fccb);
};
