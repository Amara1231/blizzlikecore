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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "Log.h"
#include "Opcodes.h"
#include "UpdateData.h"
#include "MapManager.h"
#include "Player.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    uint64 guid;
    Player* player;
    Player* plTarget;

    recvPacket >> guid;

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    player   = GetPlayer();
    plTarget = player->duel->opponent;

    if (player == player->duel->initiator || !plTarget || player == plTarget || player->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //sLog.outDebug("WORLD: Received CMSG_DUEL_ACCEPTED");
    sLog.outDebug("Player 1 is: %u (%s)", player->GetGUIDLow(), player->GetName());
    sLog.outDebug("Player 2 is: %u (%s)", plTarget->GetGUIDLow(), plTarget->GetName());

    time_t now = time(NULL);
    player->duel->startTimer   = now;
    plTarget->duel->startTimer = now;

    if (sWorld.getConfig(CONFIG_DUEL_MOD))
    {
        player->ResetAllPowers();
        plTarget->ResetAllPowers();

        if (sWorld.getConfig(CONFIG_DUEL_CD_RESET) && !player->GetMap()->IsDungeon())
            player->RemoveArenaSpellCooldowns();

        if (sWorld.getConfig(CONFIG_DUEL_CD_RESET) && !plTarget->GetMap()->IsDungeon())
            plTarget->RemoveArenaSpellCooldowns();
    }

    WorldPacket data(SMSG_DUEL_COUNTDOWN, 4);
    data << (uint32)3000;                                   // 3 seconds
    player->GetSession()->SendPacket(&data);
    plTarget->GetSession()->SendPacket(&data);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    sLog.outDebug("WORLD: received CMSG_DUEL_CANCELLED");
    uint64 guid;
    recvPacket >> guid;

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
        GetPlayer()->CombatStopWithPets(true);
        if (GetPlayer()->duel->opponent)
            GetPlayer()->duel->opponent->CombatStopWithPets(true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    // player either discarded the duel using the "discard button"
    // or used "/forfeit" before countdown reached 0
    GetPlayer()->DuelComplete(DUEL_INTERUPTED);
}
