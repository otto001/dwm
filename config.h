/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#0d4b82";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor   center*/
	{ "jetbrains", "jetbrains", "win0", 0, 1, -1, 1 },
};

static const DynamicGroupingRule dynamic_grouping_rules[] = {
        {"jetbrains-clion", 20000},
        {"jetbrains-webstorm", 20000},
        {"jetbrains-py", 20000}
};

/* layout(s) */
static const float mfact     = 0.55f; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress,    MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress,    MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress,    MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress,    MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_desktop", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-F", "-i", NULL };
static const char *dmenucmdsudo[] = { "dmenu_run_sudo", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-F", "-i", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const char *upvol[]   = { "daudio", "-cmd", "inc", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-sb", col_cyan, NULL };
static const char *downvol[] = { "daudio", "-cmd", "dec", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-sb", col_cyan, NULL };
static const char *mutevol[] = { "daudio", "-cmd", "toggle", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-sb", col_cyan, NULL };
static const char *interactive[] = { "daudio", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-sb", col_cyan,  NULL };

static const char *player_playpause[] = { "playerctl", "play-pause",  NULL };
static const char *player_next[] = { "playerctl", "next",  NULL };
static const char *player_prev[] = { "playerctl", "previous",  NULL };


static const char *brightnessUp[]   = { "dlight", "-cmd", "inc", "-m", dmenumon, "-nb", col_gray1, "-nf", col_cyan, NULL };
static const char *brightnessDown[]   = { "dlight", "-cmd", "dec", "-m", dmenumon,  "-nb", col_gray1, "-nf", col_cyan, NULL };


static const char *dpowercmd[] = { "dpower", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dblue[] = { "dblue", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static const char *scrot[] = { "scrot", "Pictures/%F_%H-%M-%S.png", "-s", NULL };

static const char *slock[] = { "slock", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */

    // audio keys
	{ KeyPress,    0,                            XF86XK_AudioLowerVolume,     spawn,          {.v = downvol } },
	{ KeyPress,    0,                            XF86XK_AudioRaiseVolume,     spawn,          {.v = upvol   } },
    { KeyPress,    0,                            XF86XK_AudioMute,            spawn,          {.v = mutevol } },
    { KeyPress,    MODKEY,                       XK_a,                        spawn,          {.v = interactive } },
    { KeyPress,    0,                            XF86XK_AudioPlay,            spawn,          {.v = player_playpause } },
    { KeyPress,    0,                            XF86XK_AudioNext,            spawn,          {.v = player_next } },
    { KeyPress,    0,                            XF86XK_AudioPrev,            spawn,          {.v = player_prev } },

    // brightness keys
    { KeyPress,    0,                            XF86XK_MonBrightnessUp,      spawn,          {.v = brightnessUp } },
    { KeyPress,    0,                            XF86XK_MonBrightnessDown,    spawn,          {.v = brightnessDown } },
        
    { KeyPress,    MODKEY,                       XK_space,                    spawn,          {.v = dmenucmd } },
    { KeyPress,    MODKEY|ShiftMask,             XK_space,                    spawn,          {.v = dmenucmdsudo } },
	{ KeyPress,    MODKEY|ShiftMask,             XK_Return,                   spawn,          {.v = termcmd } },

    { KeyPress,    MODKEY|ShiftMask,             XK_p,                        spawn,          {.v = dpowercmd} },
    { KeyPress,    MODKEY,                       XK_b,                        spawn,          {.v = dblue} },
    { KeyPress,    MODKEY|ShiftMask,             XK_l,                        spawn,          {.v = slock} },

    { KeyRelease,  MODKEY|ShiftMask,             XK_s,                        spawn,          {.v = scrot} },
    
    //predefined
    //{ KeyPress,    MODKEY,                       XK_b,                       togglebar,      {0} },
	{ KeyPress,    MODKEY,                       XK_j,                        focusstack,     {.i = +1 } },
	{ KeyPress,    MODKEY,                       XK_k,                        focusstack,     {.i = -1 } },
	{ KeyPress,    MODKEY,                       XK_i,                        incnmaster,     {.i = +1 } },
	{ KeyPress,    MODKEY,                       XK_d,                        incnmaster,     {.i = -1 } },
	{ KeyPress,    MODKEY,                       XK_h,                        setmfact,       {.f = -0.05} },
	{ KeyPress,    MODKEY,                       XK_l,                        setmfact,       {.f = +0.05} },
	{ KeyPress,    MODKEY,                       XK_Return,                   zoom,           {0} },
	{ KeyPress,    MODKEY,                       XK_Tab,                      view,           {0} },
	{ KeyPress,    MODKEY|ShiftMask,             XK_c,                        killclient,     {0} },
	{ KeyPress,    MODKEY|ShiftMask,             XK_t,                        setlayout,      {.v = &layouts[0]} },
	{ KeyPress,    MODKEY|ShiftMask,             XK_f,                        setlayout,      {.v = &layouts[1]} },
	{ KeyPress,    MODKEY|ShiftMask,             XK_m,                        setlayout,      {.v = &layouts[2]} },
	//{ KeyPress,    MODKEY,                       XK_space,                    setlayout,      {0} },
	{ KeyPress,    MODKEY,                        XK_f,                       togglefloating, {0} },
	{ KeyPress,    MODKEY,                       XK_0,                        view,           {.ui = ~0 } },
	{ KeyPress,    MODKEY|ShiftMask,             XK_0,                        tag,            {.ui = ~0 } },
	{ KeyPress,    MODKEY,                       XK_comma,                    focusmon,       {.i = -1 } },
	{ KeyPress,    MODKEY,                       XK_period,                   focusmon,       {.i = +1 } },
	{ KeyPress,    MODKEY|ShiftMask,             XK_comma,                    tagmon,         {.i = -1 } },
	{ KeyPress,    MODKEY|ShiftMask,             XK_period,                   tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ KeyPress,    MODKEY|ShiftMask|ControlMask, XK_q,                        quit,           {0} },
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
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

