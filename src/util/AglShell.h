/*
 * Copyright 2021 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __AGL_SHELL_UTIL_H
#define __AGL_SHELL_UTIL_H

enum agl_shell_surface_type {
	AGL_SHELL_TYPE_BACKGROUND,
	AGL_SHELL_TYPE_PANEL,
};

enum agl_shell_desktop_surface_type {
	AGL_SHELL_TYPE_DESKTOP,
	AGL_SHELL_TYPE_POPUP,
	AGL_SHELL_TYPE_FULLSCREEN,
	AGL_SHELL_TYPE_SPLIT_V,
	AGL_SHELL_TYPE_SPLIT_H,
	AGL_SHELL_TYPE_REMOTE
};

enum agl_shell_panel_edge {
	AGL_SHELL_PANEL_TOP,
	AGL_SHELL_PANEL_BOTTOM,
	AGL_SHELL_PANEL_LEFT,
	AGL_SHELL_PANEL_RIGHT,
};

struct agl_shell_panel {
	void to_edge(const char *edge);
	void init(const char *edge, const char *width);

	enum agl_shell_panel_edge edge;
	int width;
};

struct agl_shell_surface {
	enum agl_shell_surface_type surface_type;
	struct agl_shell_panel panel;
	std::string src;
	std::string entryPoint;
};


#endif
