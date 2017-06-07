#include "profile.h"

profile::profile(QString un, QString v, QString gd, QString jd, int mn, int mx, int w, int h):
    username(un),
    version(v),
    gameDir(gd),
    javaDir(jd),
    minMem(mn),
    maxMem(mx),
    width(w),
    height(h)
{}
