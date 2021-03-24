/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int space_both         = 1;        /* 1 means reserve space for top and bottom bar */
static const int bar_height         = 30;
static const float rel_bar_w        = 0.5;
static const int show_bottom_title  = 0;
static const char *fonts[]          = {
	"Font Awesome 5 Free,Font Awesome 5 Free Solid:style=Solid:size=12",
	"Font Awesome 5 Free,Font Awesome 5 Free Regular:style=Regular:size=12",
	"Input:size=12",
};
static const char dmenufont[]       = "monospace:size=10";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#8b2f45";
static const char col_bred[]        = "#dd3333";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray2 },
	[SchemeSel]  = { col_gray4, col_red,   col_bred  },
};

/* tagging */
static const char *tags[] = {
	"1 ", "2 ", "3 ", "4 ", "5 ",
	"6 ", "7 ", "8 ", "9 ", "0 ", ""
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag    isfloating	isterminal  noswallow	monitor */
	{ "brave",    NULL,       NULL,       1 << 0,       0,             0,           0,			0,			-1 },
	{ "code-oss", NULL,       NULL,       1 << 1,       0,             0,           0,			0,			-1 },
	{ "Telegram", NULL,       NULL,       1 << 7,       0,             0,           0,			0,			-1 },
	{ "cantata",  NULL,       NULL,       1 << 8,       0,             0,           0,			0,			-1 },
	{ NULL, NULL, "Krita - Edit Text",    0,            0,             1,           0,			0,			-1 },
	{ "st",       NULL,       NULL,       0,            0,             0,           1,          0,          -1 },
	{ NULL, NULL, "Event Tester", 		  0,	        0, 			   0,           1,         	0,          -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

#include "patches/layouts/fibonacci.c"
#include "patches/layouts/col.c"
#include "patches/layouts/center_master.c"
#include "patches/layouts/deck.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "||=",      col },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },

 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },

	{ "=M=",      centeredmaster },
	{ "<M>",      centeredfloatingmaster },

	{ "[D]",      deck },

	{ "[]=",      tile },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_r,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_n,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_x,   ACTION##stack,  {.i = 0 } }, \
	{ MOD,  XK_u,   ACTION##stack,  {.i = 1 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>

#define XK_Return 0xff0d
#define XK_Circum 0xfe52
#define XK_ß      0xdf
#define XK_ä	  0xe4
#define XK_ö	  0xf6
#define XK_ü	  0xfc

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ Mod1Mask,                     XK_Tab,    focusstack,     {.i = PREVSEL} },
	{ MODKEY,                       XK_Tab,    zoom,           {0} },

	{ MODKEY,                       XK_a,      spawn,          SHCMD("rofi -show combi") },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("pass_menu") },
	{ MODKEY,                       XK_ä,      spawn,          SHCMD("rofi-calc") },
	{ MODKEY,                       XK_ü,      spawn,          SHCMD("yta") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("$FILE_CMD") },
	{ MODKEY,                       XK_Return, spawn,          SHCMD("$TERMINAL") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_b,      spawn,          SHCMD("polybar-msg cmd toggle") },
	{ MODKEY,                       XK_d,      setmfact,       {.f = +1.65} },
	{ MODKEY,                       XK_t,      setmfact,       {.f = +1.55} },
	{ MODKEY,                       XK_g,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_g,      incnmaster,     {.i = -1 } },
	// { Mod1Mask,                     XK_Tab,    view,           {0} }, // jumps to most recent tag

	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} }, // columns
	{ MODKEY|ShiftMask,             XK_w,      setlayout,      {.v = &layouts[7]} }, // deck
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // floating
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monocle
	{ MODKEY,                       XK_k,      setlayout,      {.v = &layouts[3]} }, // fibonacci
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} }, // centeredmaster
	{ MODKEY|ShiftMask,             XK_c,      setlayout,      {.v = &layouts[6]} }, // centeredfloatingmaster
	{ MODKEY,                       XK_i,      togglesticky,   {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	// tagging
	{ MODKEY,                       XK_Circum, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_Circum, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)

    { MODKEY,                       XK_F1,		spawn,		SHCMD("add_todo") },

	{ MODKEY,                       XK_F10,		spawn,		SHCMD("connect_hyphen") },
	{ MODKEY|ShiftMask,             XK_F10,		spawn,		SHCMD("disconnect_hyphen") },
    { MODKEY,                       XK_F11,     spawn,      SHCMD("unsplit") },
    { MODKEY|ShiftMask,             XK_F11,     spawn,      SHCMD("split_21") },
    { MODKEY,                       XK_F12,     spawn,      SHCMD("usb only") },
    { MODKEY|ShiftMask,             XK_F12,     spawn,      SHCMD("usb off") },

    { MODKEY,                       XK_Escape, killclient,     {0} },
    { MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
    { MODKEY|ShiftMask|ControlMask, XK_Escape, spawn,       SHCMD("shutdown_menu") },

	// audio player controll
	{ 0, 			XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, 			XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, 			XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, 			XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle") },
	{ 0, 			XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ ControlMask,	XF86XK_AudioPlay,		spawn,		SHCMD("mpc stop") },
	{ ControlMask,	XF86XK_AudioPrev,		spawn,		SHCMD("mpc seek -10") },
	{ ControlMask,	XF86XK_AudioNext,		spawn,		SHCMD("mpc seek +10") },
	{ ControlMask,	XK_Escape,              spawn,      SHCMD("mpc del 0") },


    { MODKEY,               XK_ß,           spawn,      SHCMD("unicode_menu emoji fontawesome math") },
    { MODKEY,	     		XK_ö,           spawn,      SHCMD("today copy") },
    { MODKEY|ShiftMask,     XK_ö,           spawn,      SHCMD("today put") },

    // volume controll
    { 0,            XF86XK_AudioMute,           spawn,      SHCMD("pamixer -t") },
    { 0,            XF86XK_AudioRaiseVolume,    spawn,      SHCMD("pamixer --allow-boost -i 5") },
    { 0,            XF86XK_AudioLowerVolume,    spawn,      SHCMD("pamixer --allow-boost -d 5") },
    { ShiftMask,    XF86XK_AudioRaiseVolume,    spawn,      SHCMD("pamixer --allow-boost -i 1") },
    { ShiftMask,    XF86XK_AudioLowerVolume,    spawn,      SHCMD("pamixer --allow-boost -d 1") },

    // Screen brightness
    { 0,            XF86XK_MonBrightnessUp,     spawn,      SHCMD("light -A 5") },
    { 0,            XF86XK_MonBrightnessDown,   spawn,      SHCMD("light -U 5") },
    { ControlMask,  XF86XK_MonBrightnessUp,     spawn,      SHCMD("light -A 1") },
    { ControlMask,  XF86XK_MonBrightnessDown,   spawn,      SHCMD("light -U 1") },

    // recording
    { 0,            XK_Print,                   spawn,      SHCMD("maim_menu") },
    { ShiftMask,    XK_Print,                   spawn,      SHCMD("dmenurecord") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	// resize with left mouse click for touch pad...
	{ ClkClientWin,         MODKEY|ControlMask,Button1,     resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
