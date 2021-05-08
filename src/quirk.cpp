#include "quirk.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>

namespace QuirkUtils
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
            Modifier* modifiers;
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
            fin >> numModifiers;
            ignoreLine(fin);
            std::cout << (numModifiers > 0 ? "Number of modifiers found..." : "Skipping modifiers...") EL;
            if(numModifiers > 0)
            {
                modifiers = new Modifier[numModifiers];

                for(unsigned int i = 0; i < numModifiers; ++i)
                {
                    getline(fin, input);
                    strcpy_s(modifiers[i].modifier, 7, input.c_str());
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
                    getline(fin, str, ' ');
                    strcpy_s(pairs[i].str, 9, str.c_str());
                    //pairs[i].str = str;
                    getline(fin, replacement);
                    strcpy_s(pairs[i].replacement, 9, replacement.c_str());
                    //pairs[i].replacement = replacement;
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
                Modifiers mod;
                auto it = eMap.find(quirk.modifiers[i].modifier);
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
                            output = std::string(quirk.modifiers[i + 1].modifier).append(" ").append(output);
                            ++i; // Ignore the roleplay prefix
                            break;
                        }
                    }
                }
                else
                {
                    std::cout << "WARNING: Typo in modifier found, please check your quirkfile" EL;
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
                    output.erase(0, pos + strlen(quirk.replacements[i].str));
                    //output.erase(0, pos + quirk.replacements[i].str.size());
                }
                temp += output; // Append the last nonreplacement token
                output = temp;
            }
        }

        return output;
    }

    int writeQuirk(const Quirk &quirk, const std::string &title)
    {
        std::ofstream fout(title);
        if(fout)
        {
            fout << quirk.color.toString() EL;

            fout << quirk.numModifiers EL;
            for(unsigned int i = 0; i < quirk.numModifiers; ++i)
            {
                fout << quirk.modifiers[i].modifier EL;
            }

            fout << quirk.numReplacements EL;
            for(unsigned int i = 0; i < quirk.numReplacements; ++i)
            {
                fout << quirk.replacements[i].str << " " << quirk.replacements[i].replacement EL;
            }

            fout.close();
            return 0;
        }
        else
        {
            return -1;
        }
    }

    int destructQuirk(Quirk &q)
    {
        delete[] q.modifiers;
        delete[] q.replacements;
        return 0;
    }
}

