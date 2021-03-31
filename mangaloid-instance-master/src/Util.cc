#include "Util.h"

#include <ImageMagick-7/MagickWand/MagickWand.h>

struct Rect
{
    int w, h;
};

static Rect shrinkRect(int w, int h, int max)
{
    Rect rect { max, max };

    if (w <= max && h <= max) rect = { w, h };

    else if (w > h) {
        float ratio = (float)h / w;
        rect.h *= ratio;
    }
    
    else if (h > w) {
        float ratio = (float)w / h;
        rect.w *= ratio;
    }

    return rect;
}

bool makeThumbnail(CSR name, const drogon::HttpFile& httpFile)
{
    MagickWandGenesis();
    auto* wand = NewMagickWand();
    const void* data = (const void*)(httpFile.fileData());
    auto status = MagickReadImageBlob(wand, data, httpFile.fileLength());

    if (!status) return status;

    MagickResetIterator(wand);
    while (MagickNextImage(wand) != MagickFalse) {
        auto width = MagickGetImageWidth(wand);
        auto height = MagickGetImageHeight(wand);
        Rect rect = shrinkRect(width, height, 250);
        MagickThumbnailImage(wand, rect.w, rect.h);
    }
    MagickWriteImage(wand, (drogon::app().getUploadPath()+"/"+name).c_str());

    wand = DestroyMagickWand(wand);
    MagickWandTerminus();
    
    return true;
}

std::vector<std::string> splitCSV(const std::string& str)
{
    std::vector<std::string> ret {};
    std::stringstream ss{str};
    
    while (ss.good()) {
        std::string temp;
        std::getline(ss, temp, ',');
        if (!temp.empty()) ret.emplace_back(temp);
    }
    
    return ret;
}

std::string joinVec(const std::vector<std::string>& vec)
{
    std::stringstream ss;
    for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
        ss << "'" << *itr << "'";
        if (itr != std::prev(vec.end())) ss << ",";
    }
    return ss.str();
}
