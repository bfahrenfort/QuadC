/*
 * Title: QuadC
 * Author: Kirby
 * Description: Wrappers and testing for the generation and access of quirks
 * Now with efficient storage!
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

#include "cmd_line.h"
#include <iostream>
#include <string>
#include <vector>
#include "quirk.hpp"

#include <windows.h>
#include <stdio.h>

using namespace QuirkUtils;

static Quirk DaveCmdLine();

static void PrintUsage(char **argv);

int CmdLine (int argc, char **argv)
{
    switch(argc)
    {
        case 2:
        {
            if(strcmp(argv[1], "-nowindow") == 0)
            {
                std::string message;
                    std::string choice;
                    std::string file;
                    std::string output;
                    Quirk quirk;
                    int result{};

                    std::cout << "Enter the path to your quirkfile, or -1 if you do not have one:" EL;
                    std::cin >> file;
                    IgnoreLine();

                    if(file == "-1")
                    {
                        quirk = DaveCmdLine();
                    } else
                    {
                        result = CheckFile(file, quirk);
                    }

                    if(result == 0)
                    {
                        std::cout << "Enter your message:" EL;
                        getline(std::cin, message);

                        do
                        {
                            output = ParseQuirk(message, quirk);
                            std::cout << output EL;
                            std::cout << "Would you like to enter another message? y/n:" EL;
                            std::cin >> choice;
                            IgnoreLine();
                            if(choice == "y")
                            {
                                std::cout << "Enter your message:";
                                getline(std::cin, message);
                            }
                        } while(choice != "n");

                        DestructQuirk(quirk);
                    } else
                    {
                        std::cout << "DAVE: you done goofed" EL;
                        return -1;
                }
            }
            break;
        }
        case 3:
        {
            std::string path(argv[1]);
            std::string msg(argv[2]);
            std::string output;
            Quirk quirk;
            int result;

            if((path.size() > 4) && (path.compare(path.size() - 4, 4, ".qrk") == 0))
            {
                result = CheckFile(path, quirk);

                if(result == 0)
                {
                    output = ParseQuirk(msg, quirk);
                    std::cout << output;
                }
            }
            break;
        }
        default:
        {
            PrintUsage(argv);
        }
    }

    return 0;
}

static Quirk DaveCmdLine()
{
    Quirk quirk;

    int red{}, green{}, blue{};
    std::cout << "AUTORESPONDER: yo this be under construction just fyi" EL;
    std::cout << "DAVE: wassup we got hella work to do so let's get started" EL;
    std::cout << "DAVE: gimme your blood color's red value" EL;
    std::cout << "DAVE: should be between 0 and 255" EL;
    std::cin >> red;
    IgnoreLine();
    std::cout << "DAVE: perfect now the green" EL;
    std::cin >> green;
    IgnoreLine();
    std::cout << "DAVE: aight last one, blue" EL;
    std::cin >> blue;
    IgnoreLine();
    quirk.color = Color(red, green, blue);

    int numModifiers{};
    std::string input;
    std::vector<Modifier> modifiers;
    Modifier tmod{};
    std::cout << "DAVE: okay now what weird stuff do you do when typing" EL;
    std::cout << "DAVE: probably best to consult the modifier list" EL;
    std::cout << "DAVE: just remember any typos here are gonna cost you later" EL;
    while(input != "-1")
    {
        std::cout << "DAVE: gimme a modifier or -1 if youre done w modifiers" EL;
        getline(std::cin, input);
        if((input != "-1") && (input.size() <= 6))
        {
            strcpy_s(tmod.modifier, 7, input.c_str());
            modifiers.emplace_back(tmod);
            ++numModifiers;
        }
        else if(input.size() > 6)
        {
            std::cout << "DAVE: pretty obvious typo bud" EL;
            std::cout << "DAVE: lets do that again" EL;
        }
    }

    std::string str, replacement;
    std::vector<Pair> pairs;
    Pair tpair{};
    int numPairs{};
    std::cout << "DAVE: last one is specific letters/words you want replaced with other things" EL;
    std::cout << "DAVE: you're gonna enter some letters then a space then the replacement letters" EL;
    std::cout << "DAVE: there is an 8 char limit here tho" EL;
    std::cout << "DAVE: oh and -1 -1 when youre done" EL;
    while(str != "-1")
    {
        std::cout << "DAVE: gimme your replacements" EL;
        std::cin >> str >> replacement;
        IgnoreLine();
        if((str != "-1") && (str.size() <= 8) && (str.size() <= 8))
        {
            strcpy_s(tpair.str, 9, str.c_str());
            strcpy_s(tpair.replacement, 9, replacement.c_str());
            //tpair.str = str;
            //tpair.replacement = replacement;
            pairs.emplace_back(tpair);
            ++numPairs;
        }
        else if((str.size() > 8) || (str.size() > 8))
        {
            std::cout << "DAVE: whoa there little too many characters" EL;
            std::cout << "DAVE: lets do that again" EL;
        }
    }

    quirk.modifiers = new Modifier[numModifiers];
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
        WriteQuirk(quirk, input.append(".qrk"));
    return quirk;
}

static void PrintUsage(char **argv)
{
    std::cout << "\nusage:\n\t" << argv[0] << ": opens the GUI" EL;
    std::cout << "\t" << argv[0] << " quirkfile_path \"message\": parses the message inside the quotes according to the quirk and prints the output" EL;
    std::cout << "\t" << argv[0] << " -cli: opens a command-line interface tool for parsing messages and creating quirkfiles" EL;
}
