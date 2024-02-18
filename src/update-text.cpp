#include <string>

#include "update-text.h"
#include "text.h"
#include "text-freetype2.h"

using namespace std;

extern "C" void update_text_to_render(struct ft2_source *srcdata)
{
	if (srcdata->text == NULL) {
		return;
	}

	wstring text_to_render(srcdata->text);
	text_to_render = evaluateConditionals(text_to_render);
	text_to_render = replaceVariables(text_to_render);
	text_to_render = replaceDateTimes(text_to_render);
	if (srcdata->text_to_render != NULL) {
		bfree(srcdata->text_to_render);
	}
	srcdata->text_to_render = bwstrdup(text_to_render.c_str());
	if (srcdata->font_face) {
		cache_glyphs(srcdata, srcdata->text_to_render);
		set_up_vertex_buffer(srcdata);
	}
	//	obs_source_video_render(srcdata->src);
}
