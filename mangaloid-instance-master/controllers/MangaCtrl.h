#pragma once

#include "Types.h"
#include "Manga.h"
#include "MangaCtrlBase.h"
#include <drogon/HttpController.h>

using namespace drogon;

using namespace drogon_model::sqlite3;

class MangaCtrl: public drogon::HttpController<MangaCtrl>, public MangaCtrlBase
{
    
public:
    
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MangaCtrl::getSearch,"/manga/search?title={1}&authors={2}&artists={3}&tags={4}",Get,Options);
    ADD_METHOD_TO(MangaCtrl::getFromId,"/manga/from_id?id={1}",Get,Options);
    ADD_METHOD_TO(MangaCtrl::getChapter,"/manga/get_chapter?mangaid={1}&ordinal={2}",Get,Options);
    ADD_METHOD_TO(MangaCtrl::getThumbnail,"/manga/thumbnail?mangaid={1}",Get,Options);
    METHOD_LIST_END
    
    void getSearch(const HttpRequestPtr& req, HttpCallback&& callback, CSR title, CSR authorsCSV, CSR artistsCSV, CSR tagsCSV);
    void getFromId(const HttpRequestPtr& req, HttpCallback&& callback, long id);
    void getChapter(const HttpRequestPtr& req, HttpCallback&& callback, long mangaid, int ordinal);
    void getThumbnail(const HttpRequestPtr& req, HttpCallback&& callback, long mangaid);

};
