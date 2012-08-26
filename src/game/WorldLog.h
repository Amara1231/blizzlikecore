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

#ifndef BLIZZLIKE_WORLDLOG_H
#define BLIZZLIKE_WORLDLOG_H

#include "Common.h"
#include "Policies/Singleton.h"
#include "Errors.h"

#include <stdarg.h>

// Log packets to a file
class WorldLog : public blizzlike::Singleton<WorldLog, blizzlike::ClassLevelLockable<WorldLog, ACE_Thread_Mutex> >
{
    friend class blizzlike::OperatorNew<WorldLog>;
    WorldLog();
    WorldLog(const WorldLog &);
    WorldLog& operator=(const WorldLog &);
    typedef blizzlike::ClassLevelLockable<WorldLog, ACE_Thread_Mutex>::Lock Guard;

    // Close the file in destructor
    ~WorldLog();

    public:
        void Initialize();
        // Is the world logger active?
        bool LogWorld(void) const { return (i_file != NULL); }
        // Log to the file
        void outLog(char const *fmt, ...);
        void outTimestampLog(char const *fmt, ...);

    private:
        FILE *i_file;

        bool m_dbWorld;
};

#define sWorldLog WorldLog::Instance()
#endif

