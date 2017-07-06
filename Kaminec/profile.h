#ifndef PROFILE_H
#define PROFILE_H

#include <QString>


struct Profile
{
    Profile()=default;
    explicit Profile(QString un,
                     QString v,
                     QString gd,
                     QString jd,
                     int mn,
                     int mx,
                     int w,
                     int h);

    QString username;
    QString version;
    QString gameDir;
    QString javaDir;
    int minMem;
    int maxMem;
    int width;
    int height;
};

#endif // PROFILE_H
