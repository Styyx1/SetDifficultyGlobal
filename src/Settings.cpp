#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\SetDifficultyGlobal.ini)");

    std::string fileName(ini.GetValue("General", "sModFileName", ""));
    std::string difficultyGlobalID(ini.GetValue("FormID", "DifficultyGlobalFormID", ""));
    std::string lootChanceGlobalID(ini.GetValue("FormID", "LootChanceGlobalFormID", ""));
    std::string reverselootChanceGlobalID(ini.GetValue("FormID", "ReverseLootChanceGlobalID", ""));

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (!difficultyGlobalID.empty()) {
        DifficultyGlobalFormID = ParseFormID(difficultyGlobalID);
    }
    if (!lootChanceGlobalID.empty()) {
        LootChanceGlobalFormID = ParseFormID(lootChanceGlobalID);
    }
    if (!reverselootChanceGlobalID.empty()) {
        ReverseChanceGlobalFormID = ParseFormID(reverselootChanceGlobalID);
    }

    if (debug_logging) {
        spdlog::get("Global")->set_level(spdlog::level::level_enum::debug);
        logger::debug("Debug logging enabled");
    };
    // Load settings
    FileName = fileName;
    logger::info("Loaded settings");
};

RE::FormID Settings::ParseFormID(const std::string& str)
{
    RE::FormID         result;
    std::istringstream ss{ str };
    ss >> std::hex >> result;
    return result;
}

void Settings::LoadForms() noexcept
{
    auto dataHandler = RE::TESDataHandler::GetSingleton();

    logger::info("Loading forms");

    if (DifficultyGlobalFormID) {
        DifficultyGlobal = skyrim_cast<RE::TESGlobal*>(dataHandler->LookupForm(DifficultyGlobalFormID, FileName));
        _debug("Global variable found. Global is {} with a value of {}", DifficultyGlobal->GetFormEditorID(), DifficultyGlobal->value);
    }
    if (LootChanceGlobalFormID) {
        LootChanceGlobal = skyrim_cast<RE::TESGlobal*>(dataHandler->LookupForm(LootChanceGlobalFormID, FileName));
        _debug("Global variable found. Global is {} with a value of {}", LootChanceGlobal->GetFormEditorID(), LootChanceGlobal->value);
    }
    if (ReverseChanceGlobalFormID) {
        ReverseLootChanceGlobal = skyrim_cast<RE::TESGlobal*>(dataHandler->LookupForm(ReverseChanceGlobalFormID, FileName));
        _debug("Global variable found. Global is {} with a value of {}", ReverseLootChanceGlobal->GetFormEditorID(), ReverseLootChanceGlobal->value);
    }

    logger::info("All Forms loaded");

} // Credits: Colinswrath https://github.com/colinswrath/BladeAndBlunt
