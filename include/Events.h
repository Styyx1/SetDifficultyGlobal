#pragma once
#include "Cache.h"
#include "Settings.h"

#define continueEvent RE::BSEventNotifyControl::kContinue

class MenuManager : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
{
    static MenuManager* GetSingleton()
    {
        static MenuManager singleton;
        return &singleton;
    }

    RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override
    {
        if (!a_event) {
            return continueEvent;
        }
        if (a_event->opening) {
            return continueEvent;
        }
        if (a_event->menuName == RE::JournalMenu::MENU_NAME && !a_event->opening) {
            ChangeDiffGlobal();
        }
    }

public:
    static void ChangeDiffGlobal()
    {
        RE::PlayerCharacter* player            = Cache::GetPlayerSingleton();
        Settings*            settings          = Settings::GetSingleton();
        RE::TESGlobal*       diff_global       = settings->DifficultyGlobal;
        RE::TESGlobal*       loot_global       = settings->LootChanceGlobal;
        RE::TESGlobal*       reverseLootGlobal = settings->ReverseLootChanceGlobal;
        switch (static_cast<RE::DIFFICULTY>(player->GetGameStatsData().difficulty)) {
        case RE::DIFFICULTY::kNovice:
            diff_global->value = 1.0;
            logGlobal(diff_global);
            loot_global->value = 0.0;
            logGlobal(loot_global);
            reverseLootGlobal->value = 100.0;
            logGlobal(reverseLootGlobal);
            break;
        case RE::DIFFICULTY::kApprentice:
            diff_global->value = 2.0;
            logGlobal(diff_global);
            loot_global->value = 20.0;
            logGlobal(loot_global);
            reverseLootGlobal->value = 80.0;
            logGlobal(reverseLootGlobal);
        case RE::DIFFICULTY::kAdept:
            diff_global->value = 3.0;
            logGlobal(diff_global);
            loot_global->value = 40.0;
            logGlobal(loot_global);
            reverseLootGlobal->value = 60.0;
            logGlobal(reverseLootGlobal);
            break;
        case RE::DIFFICULTY::kExpert:
            diff_global->value = 4.0;
            logGlobal(diff_global);
            loot_global->value = 60.0;
            logGlobal(loot_global);
            reverseLootGlobal->value = 40.0;
            logGlobal(reverseLootGlobal);
            break;
        case RE::DIFFICULTY::kMaster:
            diff_global->value = 5.0;
            logGlobal(diff_global);
            loot_global->value = 80.0;
            logGlobal(loot_global);
            reverseLootGlobal->value = 20.0;
            logGlobal(reverseLootGlobal);
            break;
        case RE::DIFFICULTY::kLegendary:
            diff_global->value = 6.0;
            logGlobal(diff_global);
            loot_global->value = 100.0;
            logGlobal(loot_global);
            reverseLootGlobal->value = 0.0;
            logGlobal(reverseLootGlobal);
            break;
        }
    }

    static void logGlobal(RE::TESGlobal* use_glob) { _debug("Changed Global {} to {}", use_glob->GetFormEditorID(), use_glob->value); }

    static void Register()
    {
        auto* eventSink = MenuManager::GetSingleton();
        RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(eventSink);
        logger::info("Registered Menu");
    }
};
