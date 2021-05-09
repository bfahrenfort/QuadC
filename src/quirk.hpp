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
        unsigned int numReplacements, numModifiers;

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

    std::unordered_map<std::string, Modifiers> const eMap = {
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
    void IgnoreLine();
    void IgnoreLine(std::ifstream &stream);

    // Check if a file with a quirk exists and if so, return the quirk
    int CheckFile(const std::string &title, Quirk &q);

    // Parse the effects of a quirk on a string
    std::string ParseQuirk(const std::string &input, const Quirk &quirk);

    // Create a quirkfile from the specified quirk
    int WriteQuirk(const Quirk &quirk, const std::string &title);

    // Deallocate quirk's dynamic components so it can safely go out of scope
    int DestructQuirk(Quirk &q);
}

#endif //QUIRKTYPER_UTIL_HPP
