#include "quirk.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>

namespace utils
{
    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void ignoreLine(std::ifstream& stream)
    {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Quirk checkFile(const std::string& title)
    {
        std::cout << "Reading quirkfile " << title EL;

        Quirk quirk;
        std::ifstream fin(title.c_str());

        if(fin)
        {
            Pair* pairs;
            std::string* modifiers;
            std::string input;
            std::string str, replacement;
            int red{}, green{}, blue{};
            unsigned int numReplacements{};
            unsigned int numModifiers{};

            // Get the color
            fin >> red >> green >> blue;
            ignoreLine(fin); // I LOVE this function
            quirk.color = Color(red, green, blue);
            std::cout << "Color found..." EL;

            // Get the modifiers
            // TODO: Input validation
            fin >> numModifiers;
            ignoreLine(fin);
            std::cout << (numModifiers > 0 ? "Number of modifiers found..." : "Skipping modifiers...") EL;
            if(numModifiers > 0)
            {
                modifiers = new std::string[numModifiers];

                for(unsigned int i = 0; i < numModifiers; ++i)
                {
                    std::getline(fin, input);
                    modifiers[i] = input;
                }

            }
            else
            {
                modifiers = nullptr; // Check for this please
            }

            // Get the replacements
            fin >> numReplacements;
            ignoreLine(fin);
            std::cout << (numReplacements > 0 ? "Number of replacements found..." : "Skipping replacements...") EL;
            if(numReplacements > 0)
            {
                pairs = new Pair[numReplacements];
                for(unsigned int i = 0; i < numReplacements; ++i)
                {
                    std::getline(fin, str, ' ');
                    pairs[i].str = str;
                    std::getline(fin, replacement);
                    pairs[i].replacement = replacement;
                }
            }
            else
            {
                pairs = nullptr; // Check this too
            }

            std::cout << "Successfully read quirkfile" EL;

            fin.close();


            quirk.replacements = pairs;
            quirk.modifiers = modifiers;
            quirk.numModifiers = numModifiers;
            quirk.numReplacements = numReplacements;
        }
        else
        {
            std::cout << "File not found." EL;
        }

        return quirk;
    }

    std::string parseQuirk(const std::string &input, const Quirk &quirk)
    {
        std::string output = input;

        if(quirk.modifiers)
        {
            for(unsigned int i = 0; i < quirk.numModifiers; ++i)
            {
                Modifier mod;
                auto it = eMap.find(quirk.modifiers[i]);
                if(it != eMap.end())
                {
                    mod = it->second;
                    switch(mod)
                    {
                        case NOPUNC:
                        {
                            std::cout << "Nopunc modifier applying" EL;
                            std::stringstream stringStream(output);
                            std::string line;
                            std::string temp;
                            while(std::getline(stringStream, line))
                            {
                                std::size_t prev = 0, pos;
                                while ((pos = line.find_first_of(".',", prev)) != std::string::npos)
                                {
                                    if (pos > prev)
                                        temp.append(line.substr(prev, pos-prev));
                                    prev = pos+1;
                                }
                                if (prev < line.length())
                                    temp.append(line.substr(prev, std::string::npos));
                            }
                            output = temp;
                            break;
                        }
                        case ALLCAP:
                        {
                            std::cout << "Allcap modifier applying" EL;
                            for(auto &c : output)
                            {
                                c = toupper(c);
                            }
                            break;
                        }

                        case LOWCAP:
                        {
                            std::cout << "Lowcap modifier applying" EL;
                            for(auto &c : output)
                            {
                                c = tolower(c);
                            }
                            break;
                        }

                        case ALTCP1:
                        {
                            std::cout << "Altcap1 modifier applying" EL;
                            int k = 0;
                            for(auto &c : output){
                                c = k % 2 == 0 ? toupper(c) : tolower(c);
                                ++k;
                            }
                            break;
                        }

                        case ALTCP2:
                        {
                            std::cout << "Altcap2 modifier applying" EL;
                            int k = 0;
                            for(auto &c : output)
                            {
                                c = k % 2 == 0 ? tolower(c) : toupper(c);
                                ++k;
                            }
                            break;
                        }

                        case RNDCAP:
                        {
                            std::cout << "Randcap modifier applying" EL;
                            int k = 0;
                            for (auto &c : output)
                            {
                                c = std::rand() % 2 == 0 ? tolower(c) : toupper(c);
                                ++k;
                            }
                            break;
                        }

                        case TTLCAP:
                        {
                            std::cout << "Titlecap modifier applying" EL;
                            std::string token;
                            std::string temp;
                            std::istringstream is(output);
                            while(getline(is, token, ' '))
                            {
                                token[0] = toupper(token[0]);
                                temp += token.append(" ");
                            }
                            output = temp;
                            break;
                        }

                        case ASTRSK:
                        {
                            std::cout << "Asterisk modifier applying" EL;
                            output = std::string("*").append(output).append(std::string("*"));
                            break;
                        }

                        case ROLPLY:
                        {
                            std::cout << "Roleplay modifier applying" EL;
                            output = std::string(quirk.modifiers[i + 1]).append(" ").append(output);
                            ++i; // Ignore the roleplay prefix
                            break;
                        }
                    }
                }
            }
        }

        // I'm very proud of this one
        if(quirk.replacements)
        {
            for(unsigned int i = 0; i < quirk.numReplacements; ++i)
            {
                std::cout << "Applying replacement " << quirk.replacements[i].str << "-" << quirk.replacements[i].replacement EL;
                size_t pos;
                std::string token;
                std::string temp;
                while((pos = output.find(quirk.replacements[i].str)) != std::string::npos)
                {
                    token = output.substr(0, pos);
                    temp += token;
                    temp += quirk.replacements[i].replacement;
                    output.erase(0, pos + quirk.replacements[i].str.length());
                }
                temp += output; // Append the last nonreplacement token
                output = temp;
            }
        }

        return output;
    }
}

