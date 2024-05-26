#pragma once

namespace RE
{
    enum class DIFFICULTY : std::int32_t
    {
        kNovice     = 0,
        kApprentice = 1,
        kAdept      = 2,
        kExpert     = 3,
        kMaster     = 4,
        kLegendary  = 5
    };
} // namespace RE

class Settings : public Singleton<Settings>
{
public:
    void LoadSettings() noexcept;

    void LoadForms() noexcept;

    std::string    FileName;
    RE::FormID     DifficultyGlobalFormID;
    RE::TESGlobal* DifficultyGlobal;

    const std::string_view ModName = "SetDifficultyGlobal.esm";

    static RE::FormID ParseFormID(const std::string& str);

    inline static bool debug_logging{};
};
