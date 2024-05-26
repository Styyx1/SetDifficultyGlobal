#pragma once
#include "Cache.h"
#include "Settings.h"

#define continueEvent RE::BSEventNotifyControl::kContinue
#define logIt         logger::debug("Changed Global {} to {}", global->GetFormEditorID(), global->value);

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
        RE::PlayerCharacter* player   = Cache::GetPlayerSingleton();
        Settings*            settings = Settings::GetSingleton();
        RE::TESGlobal*       global   = settings->DifficultyGlobal;
        switch (static_cast<RE::DIFFICULTY>(player->GetGameStatsData().difficulty)) {
        case RE::DIFFICULTY::kNovice:
            global->value = 1.0;
            logIt;
            break;
        case RE::DIFFICULTY::kApprentice:
            global->value = 2.0;
            logIt;
            break;
        case RE::DIFFICULTY::kAdept:
            global->value = 3.0;
            logIt;
            break;
        case RE::DIFFICULTY::kExpert:
            global->value = 4.0;
            logIt;
            break;
        case RE::DIFFICULTY::kMaster:
            global->value = 5.0;
            logIt;
            break;
        case RE::DIFFICULTY::kLegendary:
            global->value = 6.0;
            logIt;
            break;
        }
    }

    static void Register()
    {
        auto* eventSink = MenuManager::GetSingleton();
        RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(eventSink);
        logger::info("Registered Menu");
    }
};
