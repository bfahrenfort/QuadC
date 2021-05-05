/*
 * Title: Homestuck Quirk Typer
 * Author: Kirby
 * Description: takes any strings inputted and edits them to exhibit a typing quirk.
 *
 * Quirks are a collection of a text color,
 *   broad modifiers on the text,
 *   and specific substrings that are replaced in a target string.
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
#include "quirk.hpp"

using namespace utils;

Quirk daveCLI()
{
    Quirk quirk;
    int red{}, green{}, blue{};
    std::string str, replacement;

    std::cout << "DAVE: yo this be under construction but we can try it" EL;
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

    std::cout << "DAVE: okay now what weird stuff do you do when typing" EL;
    std::cout << "DAVE: ill just assume nothing ok" EL;
    return quirk;
}

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
    }

    return 0;
}
