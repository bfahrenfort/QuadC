#include <string>
#include <iostream>
#include <unordered_map>
#include "color.h"

#ifndef QUIRKTYPER_QUIRK_HPP
#define QUIRKTYPER_QUIRK_HPP

#define EL << std::endl

namespace utils
{
    // A relation of a base substring and what it is replaced with
    struct Pair
    {
        std::string str, replacement;
    };

    // The main grouping
    struct Quirk
    {
        Color color;
        Pair* replacements;
        unsigned int numReplacements = 0, numModifiers = 0;

        std::string* modifiers;
    };

    enum Modifier
    {
        NOPUNC,
        ALLCAP,
        LOWCAP,
        ALTCP1,
        ALTCP2,
        RNDCAP,
        TTLCAP,
        ASTRSK,
        ROLPLY
    };

    static std::unordered_map<std::string, Modifier> const eMap = {
            {"NOPUNC", Modifier::NOPUNC},
            {"ALLCAP", Modifier::ALLCAP},
            {"LOWCAP", Modifier::LOWCAP},
            {"ALTCP1", Modifier::ALTCP1},
            {"ALTCP2", Modifier::ALTCP2},
            {"RNDCAP", Modifier::RNDCAP},
            {"TTLCAP", Modifier::TTLCAP},
            {"ASTRSK", Modifier::ASTRSK},
            {"ROLPLY", Modifier::ROLPLY}
    };

    // Clear the input buffer
    void ignoreLine();
    void ignoreLine(std::ifstream& stream);

    // Check if a file with a quirk exists and if so, return the quirk
    Quirk checkFile(const std::string& title);

    // Parse the effects of a quirk on a string
    std::string parseQuirk(const std::string &input, const Quirk &quirk);

    int deallocQuirk(Quirk &q);
}

#endif //QUIRKTYPER_UTIL_HPP
