#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\SetDifficultyGlobal.ini)");

    std::string fileName(ini.GetValue("General", "sModFileName", ""));
    std::string difficultyGlobalID(ini.GetValue("FormID", "DifficultyGlobalFormID", ""));

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (!difficultyGlobalID.empty()) {
        DifficultyGlobalFormID = ParseFormID(difficultyGlobalID);
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

    logger::info("All Forms loaded");

} // Credits: Colinswrath https://github.com/colinswrath/BladeAndBlunt
