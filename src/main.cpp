/*
 * Title: QuadC
 * Author: Kirby
 * Description: Wrappers and testing for the generation and access of quirks
 *
 * Quirks are a collection of a text color,
 *   broad modifiers on the text,
 *   and specific substrings that are replaced in a target string after modifiers are applied.
 *
 * Quirkfiles are text files created by this program. They have the extension .qrk and contain the following:
 * R G B
 * number of modifiers
 * modifier1
 * modifier2
 * ...
 * number of replacements
 * string1 replacement1
 * string2 replacement2
 * ...
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include "quirk.hpp"

using namespace QuirkUtils;

Quirk daveCLI();

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::string message;
        std::string choice;
        std::string file;
        std::string output;
        Quirk quirk;
        std::cout << "Enter the path to your quirkfile, or -1 if you do not have one:";
        std::cin >> file;
        ignoreLine();

        if(file == "-1")
        {
            quirk = daveCLI();
        }
        else
        {
            quirk = checkFile(file);
        }

        std::cout << "Enter your message:";
        getline(std::cin, message);

        do
        {
            output = parseQuirk(message, quirk);
            std::cout << output EL;
            std::cout << "Would you like to enter another message? y/n:";
            std::cin >> choice;
            ignoreLine();
            if(choice == "y")
            {
                std::cout << "Enter your message:";
                getline(std::cin, message);
            }
        }
        while(choice != "n");

        deallocQuirk(quirk);
    }

    return 0;
}

Quirk daveCLI()
{
    Quirk quirk;

    int red{}, green{}, blue{};
    std::cout << "AUTORESPONDER: yo this be under construction just fyi" EL;
    std::cout << "DAVE: wassup we got hella work to do so let's get started" EL;
    std::cout << "DAVE: gimme your blood color's red value" EL;
    std::cout << "DAVE: should be between 0 and 255" EL;
    std::cin >> red;
    ignoreLine();
    std::cout << "DAVE: perfect now the green" EL;
    std::cin >> green;
    ignoreLine();
    std::cout << "DAVE: aight last one, blue" EL;
    std::cin >> blue;
    ignoreLine();
    quirk.color = Color(red, green, blue);

    int numModifiers{};
    std::string input;
    std::vector<std::string> modifiers;
    std::cout << "DAVE: okay now what weird stuff do you do when typing" EL;
    std::cout << "DAVE: probably best to consult the modifier list" EL;
    std::cout << "DAVE: just remember any typos here are gonna cost you later" EL;
    while(input != "-1")
    {
        std::cout << "DAVE: gimme a modifier or -1 if youre done w modifiers" EL;
        getline(std::cin, input);
        if(input != "-1")
        {
            modifiers.emplace_back(input);
            ++numModifiers;
        }
    }

    std::string str, replacement;
    std::vector<Pair> pairs;
    Pair temp;
    int numPairs{};
    std::cout << "DAVE: last one is specific letters/words you want replaced with other things" EL;
    std::cout << "DAVE: you're gonna enter some letters then a space then the replacement letters" EL;
    std::cout << "DAVE: oh and -1 -1 when youre done" EL;
    while(str != "-1")
    {
        std::cout << "DAVE: gimme your replacements" EL;
        std::cin >> str >> replacement;
        ignoreLine();
        if(str != "-1")
        {
            temp.str = str;
            temp.replacement = replacement;
            pairs.emplace_back(temp);
            ++numPairs;
        }
    }

    quirk.modifiers = new std::string[numModifiers];
    std::copy(modifiers.begin(), modifiers.end(), quirk.modifiers);
    quirk.numModifiers = numModifiers;
    quirk.replacements = new Pair[numPairs];
    std::copy(pairs.begin(), pairs.end(), quirk.replacements);
    quirk.numReplacements = numPairs;

    std::cout << "DAVE: final thing do you wanna save your quirk in a file" EL;
    std::cout << "DAVE: if you do enter the name without an extension" EL;
    std::cout << "DAVE: otherwise you know the drill by now -1 me baby" EL;
    getline(std::cin, input);
    if(input != "-1")
        writeQuirk(quirk, input.append(".qrk"));
    return quirk;
}
