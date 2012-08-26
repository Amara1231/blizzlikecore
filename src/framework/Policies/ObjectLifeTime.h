/*
 * Copyright (C) 2011-2012 BlizzLikeCore <http://blizzlike.servegame.com/>
 * Please, read the credits file.
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BLIZZLIKE_OBJECTLIFETIME_H
#define BLIZZLIKE_OBJECTLIFETIME_H

#include <stdexcept>
#include "Platform/Define.h"

typedef void (* Destroyer)(void);

namespace blizzlike
{
    void at_exit( void (*func)() );

    template <class T>
        class ObjectLifeTime
    {
        public:
            static void ScheduleCall(void (*destroyer)() )
            {
                at_exit( destroyer );
            }

            DECLSPEC_NORETURN static void OnDeadReference(void) ATTR_NORETURN;

    };

    template <class T>
        void ObjectLifeTime<T>::OnDeadReference(void)// We don't handle Dead Reference for now
    {
        throw std::runtime_error("Dead Reference");
    }
}
#endif

