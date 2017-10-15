#ifndef MUPDF_OUTLINE_P_H
#define MUPDF_OUTLINE_P_H

extern "C" {
#include <mupdf/fitz.h>
}

namespace MuPDF
{

class DocumentPrivate;
class Link;

class OutlinePrivate
{
public:
    OutlinePrivate(DocumentPrivate *dp, fz_outline *o);
    ~OutlinePrivate();

    void deleteData()
    {
        if (outline) {
            fz_drop_outline(context, outline);
            outline = NULL;
        }
    }

    DocumentPrivate *documentp;
    fz_context *context;
    fz_outline *outline;
};

class OutlineItemPrivate
{
public:
    OutlineItemPrivate(fz_outline *o);
    ~OutlineItemPrivate();

    fz_outline *outline;
    Link *link;
};

}

#endif // end MUPDF_OUTLINE_P_H
