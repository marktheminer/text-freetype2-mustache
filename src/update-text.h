#ifndef DATETIME_H
#define DATETIME_H

#ifdef __cplusplus
#define MODULE_EXPORT extern "C" EXPORT
#define MODULE_EXTERN extern "C"
#else
#define MODULE_EXPORT EXPORT
#define MODULE_EXTERN extern
#endif

#include "text-freetype2.h"

MODULE_EXPORT void update_text_to_render(struct ft2_source *srcdata);

#endif