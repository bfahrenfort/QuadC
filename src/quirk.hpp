#include <string>
#include <iostream>
#include <unordered_map>
#include "color.hpp"

#ifndef QUIRKTYPER_QUIRK_HPP
#define QUIRKTYPER_QUIRK_HPP

#define EL << std::endl

namespace QuirkUtils
{
    // A relation of a base substring and what it is replaced with
    struct Pair
    {
        //std::string str, replacement;
        char str[9], replacement[9]; // 8-character limit, pretty reasonable imo
    };

    // Literally just a modifier string but inside a struct so I can make it a dynamic array
    struct Modifier
    {
        char modifier[7]; // All modifier codes are 6 characters long, this limits roleplay prefixes as well
    };

    // The main grouping
    struct Quirk
    {
        Color color;
        Pair* replacements;
        unsigned int numReplacements = 0, numModifiers = 0;

        Modifier* modifiers;
    };

    enum Modifiers
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

    static std::unordered_map<std::string, Modifiers> const eMap = {
            {"NOPUNC", Modifiers::NOPUNC},
            {"ALLCAP", Modifiers::ALLCAP},
            {"LOWCAP", Modifiers::LOWCAP},
            {"ALTCP1", Modifiers::ALTCP1},
            {"ALTCP2", Modifiers::ALTCP2},
            {"RNDCAP", Modifiers::RNDCAP},
            {"TTLCAP", Modifiers::TTLCAP},
            {"ASTRSK", Modifiers::ASTRSK},
            {"ROLPLY", Modifiers::ROLPLY}
    };

    // Clear the input buffer
    void ignoreLine();
    void ignoreLine(std::ifstream& stream);

    // Check if a file with a quirk exists and if so, return the quirk
    Quirk checkFile(const std::string& title);

    // Parse the effects of a quirk on a string
    std::string parseQuirk(const std::string &input, const Quirk &quirk);

    // Create a quirkfile from the specified quirk
    int writeQuirk(const Quirk &quirk, const std::string &title);

    // Deallocate quirk's dynamic components so it can safely go out of scope
    int deallocQuirk(Quirk &q);
}

#endif //QUIRKTYPER_UTIL_HPP
