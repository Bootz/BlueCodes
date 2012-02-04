//Created by Chronic 
// fixed errors by blue
#define GOSSIP_ITEM_1000       "Remove PVP Flags"

uint32 HasUnitState;
uint32 ClearUnitState;
uint32 RemoveByteFlag;



class npc_remove_pvp : public CreatureScript
{
	public: npc_remove_pvp() : CreatureScript("npc_remove_pvp"){ }

  bool OnGossipHello(Player* pPlayer, Creature* pCreature)      
  {
        if (pPlayer->isInCombat())
		{
		pCreature->MonsterWhisper("You Are In Combat!", pPlayer->GetGUID());
        pPlayer->CLOSE_GOSSIP_MENU();
        return false;
		}
        else
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1000); 
            pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
            return true;
        }
  }
		bool OnGossipSelect(Player *pPlayer, Creature *pCreature, uint32 /*uiSender*/, uint32 uiAction)
		{
        //Remove me from pvp
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1000)
        {
			pPlayer->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_CONTESTED_PVP),//contested pvp flag
			pPlayer->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_PVP),//pvp flag
			pPlayer->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP),//ffa pvp flag
			pPlayer->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_PVP),//pvp flag
			pPlayer->RemoveAura(SPELL_AURA_MOD_FACTION),
			pPlayer->ClearUnitState(UNIT_STAT_ATTACK_PLAYER),
			pPlayer->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_PVP_TIMER),
			pPlayer->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP), 
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		return true;
		}
};
void AddSC_npc_remove_pvp()
{
    new npc_remove_pvp();
}