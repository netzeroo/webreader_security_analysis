#include "MangaCtrl.h"
#include "Chapter.h"
#include "Util.h"
#include <fmt/core.h>
#include <sstream>
#include <string>

#define MAKETEMPLATE(table, rel) " manga.id IN (SELECT "#rel".manga_id FROM "#rel" JOIN "#table" ON "#table".id = "#rel"."#table"_id WHERE "#table".name IN ({}) GROUP BY "#rel".manga_id HAVING COUNT(DISTINCT "#table".name) = {} )"

static void addWithOr (
    bool& mFilter,
    std::stringstream& ss,
    const std::string& fmtstr,
    const std::vector<std::string>& vec
) {
    static constexpr auto orQuery = " AND";
    
    if (vec.size()) {
        if (mFilter) ss << orQuery;
        ss << fmt::format(fmtstr, joinVec(vec), vec.size());
        mFilter = true;
    }
}

static std::string searchQuery (
    CSR title,
    const std::vector<std::string> authors,
    const std::vector<std::string> artists,
    const std::vector<std::string> tags
) {
    static constexpr auto selectQuery = "SELECT manga.*";
    static constexpr auto fromQuery = " FROM manga";
    static constexpr auto joinQuery = " INNER JOIN title ON manga.id = title.manga_id";
    static constexpr auto whereQuery = " WHERE";
    static constexpr auto titleQueryTemplate = " title.text LIKE '%{}%'";
    static constexpr auto authorQueryTemplate = MAKETEMPLATE(person,author);
    static constexpr auto artistQueryTemplate = MAKETEMPLATE(person,artist);
    static constexpr auto tagQueryTemplate = MAKETEMPLATE(tag,manga_tag);
    
    bool mFilter{false};
    std::stringstream ss;
    ss << selectQuery << fromQuery;
    
    if (title.size()) {
        ss << joinQuery << whereQuery << fmt::format(titleQueryTemplate, title);
        mFilter = true;
    } else if (authors.size() || artists.size() || tags.size()) {
        ss << whereQuery;
    } else goto re;
    
    addWithOr(mFilter, ss, authorQueryTemplate, authors);
    addWithOr(mFilter, ss, artistQueryTemplate, artists);
    addWithOr(mFilter, ss, tagQueryTemplate, tags);
    
re: ss << ";";
    return ss.str();
}

void MangaCtrl::getSearch (
    const HttpRequestPtr& req,
    HttpCallback&& callback,
    CSR title,
    CSR authorsCSV,
    CSR artistsCSV,
    CSR tagsCSV
) {
    auto authors = splitCSV(authorsCSV);
    auto artists = splitCSV(artistsCSV);
    auto tags = splitCSV(tagsCSV);
    
    auto dbClientPtr = getDbClient();
    auto callbackPtr = std::make_shared<HttpCallback>(std::move(callback));
    dbClientPtr->execSqlAsync(
        searchQuery(title, authors, artists, tags),
        [req, callbackPtr, this](const Result &r) {
            Json::Value ret;
            for (auto& itr : r) ret.append(Manga(itr).toJson());
            return (*callbackPtr)(HttpResponse::newHttpJsonResponse(ret));
        },
        [callbackPtr](const DrogonDbException &e) {
            LOG_ERROR<<e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            return (*callbackPtr)(resp);
        });
    
}

void MangaCtrl::getFromId(const HttpRequestPtr& req, HttpCallback&& callback, long id)
{
    MangaCtrlBase::getOne(req, std::move(callback), std::move(id));
}

void MangaCtrl::getChapter(const HttpRequestPtr& req, HttpCallback&& callback, long mangaid, int ordinal)
{
    auto dbClientPtr = getDbClient();
    auto callbackPtr = std::make_shared<HttpCallback>(std::move(callback));
    auto mc = Criteria(Chapter::Cols::_manga_id,CompareOperator::EQ,mangaid);
    auto oc = Criteria(Chapter::Cols::_ordinal,CompareOperator::EQ,ordinal);
    
    drogon::orm::Mapper<Chapter> mapper(dbClientPtr);
    mapper.findOne(
        mc && oc,
        [req, callbackPtr, this](Chapter r) {
            (*callbackPtr)(HttpResponse::newHttpJsonResponse(makeJson(req, r)));
        },
        [callbackPtr](const DrogonDbException &e) {
            LOG_ERROR<<e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            (*callbackPtr)(resp);
        });
}

void MangaCtrl::getThumbnail(const HttpRequestPtr& req, HttpCallback&& callback, long mangaid)
{
    //manga = ...
    //if (!fs::file_exists(...)) make_thumbnail(...);
    //resp = ...
}
