/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PROJECTILEHELPER_H__
#define __PROJECTILEHELPER_H__

#include "../types/Projectile.h"

#include "../link/Link.h"

class ProjectileHelper {
    public :
        static ProjectileHelper* getInstance();

        void addProjectile(TypeProjectile type, int x, int y, Direction dir, bool expo = false);
        void addProjectile(TypeProjectile type, int x, int y, double dx, double dy, BoundingBox* box = 0, bool fromLink = false);
        void addProjectile(TypeProjectile type, int x, int y, Link* link, bool locked = false, BoundingBox* box = 0);

    private :
        ProjectileHelper();
        ~ProjectileHelper();

        static ProjectileHelper instance;

};

#endif  // ProjectileHelper.h
