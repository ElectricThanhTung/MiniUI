
#ifndef __MINIUI_FONT_LIST_H
#define __MINIUI_FONT_LIST_H

#ifndef MINIUI_FONT_DEFAULT
    #define MINIUI_FONT_DEFAULT        TimesNewRoman
    #include "time_new_roman.h"
#endif /* MINIUI_FONT_DEFAULT */

#if __has_include("flint_user_fonts.h")
    #include "flint_user_fonts.h"
#endif

#endif /* __MINIUI_FONT_LIST_H */
