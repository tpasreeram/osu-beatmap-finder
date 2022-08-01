#include "BeatmapListing.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>

bool checkValidInteger(std::string in) //checks if the string is an int
{
    try
    {
        int temp;
        temp = stoi(in);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cout << "Please enter a valid input\n";
        return false;
    }
}

bool inRange(int test, int low, int high) //checks if an integer is within a certain range
{
    if (test >= low && test <= high)
    {
        return true;
    }
    return false;
}

bool isinList(std::string a, BeatmapListing b) //check if a is a node in the Adjacency List
{
    if (b.list.getNode(a) != nullptr)
    {
        return true;
    }
    return false;
}

bool isinEList(std::string a, BeatmapListing b) //check if a is a node in the Edge List
{
    if (b.elist.getNode(a) != nullptr)
    {
        return true;
    }
    return false;
}

void printPages(std::vector<std::string> disp, BeatmapListing frame, int dso) //prints the beatmaps
{
    int pagenum = 1;
    std::string in;
    bool run1 = true;
    while (run1)
    {
        int pages = (int)ceil((float)disp.size() / 15.0f); 
        std::cout << "Page " << pagenum << " of " << pages << '\n';
        for (int i = (pagenum - 1) * 15; i < ((pagenum - 1) * 15) + 15 && i < disp.size(); ++i) //prints the output in pages so you dont have one long list
        {
            Beatmap* out;
            if (dso == 0)
            {
                out = frame.list.getNode(disp[i])->getBeatmap();
            }
            else
            {
                out = frame.elist.getNode(disp[i])->getBeatmap();
            }
            //formatting
            std::cout << std::setw(10) << disp[i] << std::left << std::setw(0) << " " << out->artist << " - " << out->title << " [" << out->diffName << "] (" << out->mapper << " | ";
            std::cout << std::fixed << std::setprecision(2) << out->starRating << "*)" <<std::endl;
        }
        std::cout << "\nEnter a page number, or type 0 to exit\n";
        std::cin >> in;
        
        if (!checkValidInteger(in)) //menu checking
        {
            continue;
        }
        pagenum = stoi(in);
        if(!inRange(pagenum, 0, pages))
        {
            std::cout << "Please enter a valid menu option\n";
            continue;
        }


        switch(pagenum)
        {
            case 0:
                run1 = false;
                break;
            default:
                break;
        }
    }
}
void printSearch(std::set<std::string> disp, int remove) //prints all elements in a set
{
    int pagenum = 1;
    std::string in;
    bool run = true;
    while(run)
    {
        int pages = (int)ceil((float)disp.size() / 15.0f);
        std::cout << "Page " << pagenum << " of " << pages << '\n';
        auto it = disp.begin();
        for (int i = 0; i < (pagenum - 1) * 15; ++i) //sets the iterator to the start of the selected page
        {
            it++;
        }
        for (int i = ((pagenum - 1) * 15); i < ((pagenum - 1)* 15) + 15 && i < disp.size(); ++i) //displays only 15 elements (a page)
        {
            std::string manip = *it;
            std::cout << manip.substr(0, manip.length() - remove) << std::endl;
            it++;
        }
        std::cout << "\nEnter a page number, or type 0 to exit\n";
        std::cin >> in;
        if (!checkValidInteger(in)) //menu checking
        {
            continue;
        }
        pagenum = stoi(in);
        if(!inRange(pagenum, 0, pages))
        {
            std::cout << "Please enter a valid menu option\n";
            continue;
        }
        switch(pagenum)
        {
            case 0:
                run = false;
                break;
            default:
                break;
        }
    }
}

int main()
{
    std::cout << "Loading...." << std::endl; //fun loading statement
    BeatmapListing frame = BeatmapListing();
    frame.readFile("metadata.csv");
    Beatmap* a = new Beatmap;
    
    std::cout << "\nWelcome to the osu! beatmap finder!" << std::endl;
    std::cout << "Pick a menu option to get started" << std::endl; 
    //initializing vars
    bool run = true; 
    std::string in = "";
    int menu;
    std::set<std::string> tagdisp;
    std::set<std::string> sourcedisp;
    std::set<std::string> mapperdisp;
    std::vector<std::string> disp;
    bool run6, run4, run4n, run1;
    std::string in4, in6, in4n, in6n, in1;
    int submenu6, submenu4, submenu4n;
    std::string title, mapper, artist, tag, source;
    int tagsize, sourcesize, mappersize;
    int pagenum;


    std::string gamemodes[4] = {"osu!", "osu!taiko", "osu!catch", "osu!mania"};
    std::string ds[2] = {"Adjacency List", "Edge List"};
    int dso = 0;
    
    
    std::string arr[24] = {"user", "", "" ,"", "", "", "", "", "", "0", "0", "90", "3.8", "160", "4", "4", "4", "4", "10", "0", "0", "0", "0", "727"};
    Beatmap* userPref = new Beatmap(arr);
    
    while (run)
    {
        menu = 0;
        std::cout << "1. Display a list of beatmaps\n";
        std::cout << "2. Change the star difficulty\n";
        std::cout << "3. Change Difficulty settings (CS, OD, AR, HP)\n";
        std::cout << "4. Change modes\n";
        std::cout << "5. Search for a map!\n";
        std::cout << "6. Display extended information about a beatmap\n";
        std::cout << "7. Help\n";
        std::cout << "8. Change data structure used. (Current structure: " << ds[dso] <<")\n";
        std::cout << "9. Exit\n";
        std::cin >> in;
        if (!checkValidInteger(in)) //menu checking
        {
            continue;
        }
        menu = stoi(in);

        if (menu == 727) //easter egg
        {
            std::cout << "WYSI" << std::endl;
            run = false;
            break;
        }
        else if(!inRange(menu, 1, 9))
        {
            std::cout << "Please enter a valid menu option\n";
            continue;
        }
        
        switch(menu)
        {
            case 1:
                run1 = true;
                disp = frame.getMaps(userPref, gamemodes[userPref->mode]); //use getMaps to find best fit maps
                pagenum = 1;
                printPages(disp, frame, dso);
                break;
            case 2:
                //change star rating
                std::cout << "Current star difficulty: " << userPref->starRating << '\n';
                std::cout << "Enter new difficulty: \n";
                std::cin >> userPref->starRating;
                std::cout << "New difficulty: " << userPref->starRating << '\n';
                break;
            case 3:
                //change difficulty settings
                std::cout << "Current Settings: CS = "  << userPref->cs << " AR = " << userPref->ar << " OD = " << userPref->od << " HP = " << userPref->hp << '\n';
                std::cout << "Enter new settings: \n";
                std::cout << "CS = ";
                std::cin >> userPref->cs;
                std::cout << "AR = ";
                std::cin >> userPref->ar;
                std::cout << "OD = ";
                std::cin >> userPref->od;
                std::cout << "HP = ";
                std::cin >> userPref->hp;
                std::cout << "New Settings: CS = "  << userPref->cs << " AR = " << userPref->ar << " OD = " << userPref->od << " HP = " << userPref->hp << '\n';
                break;
            case 4:
                run4n = true;
                while(run4n) //change gamemode (changes the pool from where the beatmaps come from)
                {
                    std::cout << "Current gamemode: " << gamemodes[userPref->mode] << '\n';
                    std::cout << "Enter a number 0 - 3\n";
                    std::cout << "0: osu!    1: osu!taiko    2: osu!catch    3: osu!mania\n";
                    std::cin >> in4n;
                    if (!checkValidInteger(in4n))
                    {
                        continue;
                    }
                    submenu4n = stoi(in4n);
                    if(!inRange(submenu4n, 0, 3))
                    {
                        std::cout << "Please enter a valid menu option\n";
                        continue;
                    }
                    userPref->mode = submenu4n;
                    std::cout << "New gamemode: " << gamemodes[userPref->mode] << '\n';
                    run4n = false;
                    break;
                }
                break;
            case 5:
                run4 = true;
                while(run4)
                {
                    std::cout << "\n1. Search by title\n";
                    std::cout << "2. Search by artist\n";
                    std::cout << "3. Search by tag\n";
                    std::cout << "4. Search by mapper\n";
                    std::cout << "5. Search by source\n";
                    std::cout << "6. Go back\n";
                    std::cin >> in4;
                    if (!checkValidInteger(in4))
                    {
                        continue;
                    }
                    submenu4 = stoi(in4);
                    if(!inRange(submenu4, 1, 6))
                    {
                        std::cout << "Please enter a valid menu option\n";
                        continue;
                    }
                    switch(submenu4)
                    {
                        case 1:
                            std::cout << "Please enter the title: " << std::endl;
                            std::getline(std::cin, title);
                            std::getline(std::cin, title);
                            title += "title";
                            //search if given title is in graph
                            if (!isinList(title, frame) && dso == 0)
                            {
                                std::cout << "Sorry, the title you are looking for is not in the list.";
                            }
                            if(!isinEList(title, frame) && dso != 0)
                            {
                                std::cout << "Sorry, the title you are looking for is not in the list.";
                            }
                            else
                            {
                                //display maps using print method, also ordered due to getMaps function
                                std::cout << "Here's what we found.\n";
                                disp = frame.getMaps(userPref, title);
                                printPages(disp, frame, dso);
                            }
                            break;
                        case 2:
                            std::cout << "Please enter the artist name: " << std::endl;
                            std::getline(std::cin, artist);
                            std::getline(std::cin, artist);
                            artist += "artist";
                            if (!isinList(artist, frame) && dso == 0)
                            {
                                std::cout << "Sorry, the artist you are looking for is not in the list.";
                            }
                            if(!isinEList(artist, frame) && dso != 0)
                            {
                                std::cout << "Sorry, the artist you are looking for is not in the list.";
                            }
                            else
                            {
                                //display maps using print method, also ordered due to getMaps function
                                std::cout << "Here's what we found.\n";
                                disp = frame.getMaps(userPref, artist);
                                printPages(disp, frame, dso);
                            }
                            break;
                        case 3:
                            std::cout << "Please enter the tag: " << std::endl;
                            std::getline(std::cin, tag);
                            std::getline(std::cin, tag);
                            tag += "tag";
                            if (!isinList(tag, frame) && dso == 0)
                            {
                                std::cout << "Sorry, the tag you are looking for is not in the list.";
                            }
                            if(!isinEList(tag, frame) && dso != 0)
                            {
                                std::cout << "Sorry, the tag you are looking for is not in the list.";
                            }
                            else
                            {
                                //display maps using print method, also ordered due to getMaps function
                                std::cout << "Here's what we found.\n";
                                disp = frame.getMaps(userPref, tag);
                                printPages(disp, frame, dso);
                            }
                            break;
                        case 4:
                            std::cout << "Please enter the mapper name: " << std::endl;
                            std::getline(std::cin, mapper);
                            std::getline(std::cin, mapper);
                            mapper += "mapper";
                            if (!isinList(mapper, frame) && dso == 0)
                            {
                                std::cout << "Sorry, the mapper you are looking for is not in the list.";
                            }
                            if(!isinEList(mapper, frame) && dso != 0)
                            {
                                std::cout << "Sorry, the mapper you are looking for is not in the list.";
                            }
                            else
                            {
                                //display maps using print method, also ordered due to getMaps function
                                std::cout << "Here's what we found.\n";
                                disp = frame.getMaps(userPref, mapper);
                                printPages(disp, frame, dso);
                            }
                            break;
                        case 5:
                            std::cout << "Please enter the source: " << std::endl;
                            std::getline(std::cin, source);
                            std::getline(std::cin, source);
                            source += "source";
                            if (!isinList(source, frame) && dso == 0)
                            {
                                std::cout << "Sorry, the source you are looking for is not in the list.";
                            }
                            if(!isinEList(source, frame) && dso != 0)
                            {
                                std::cout << "Sorry, the source you are looking for is not in the list.";
                            }
                            else
                            {
                                //display maps using print method, also ordered due to getMaps function
                                std::cout << "Here's what we found.\n";
                                disp = frame.getMaps(userPref, source);
                                printPages(disp, frame, dso);
                            }
                            break;
                        case 6:
                            //exit command
                            run4 = false;
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 6:
                std::cout << "Please enter the beatmap ID you wish to look up.\n";
                std::cin >> in6n;
                if(frame.list.getNode(in6n) != nullptr)
                {
                    //displays extensive info about a beatmap
                    Beatmap *disp;
                    if (dso == 0)
                    {
                        disp = frame.list.getNode(in6n)->getBeatmap();
                    }
                    else
                    {
                        disp = frame.elist.getNode(in6n)->getBeatmap();
                    }
                    std::cout << '\n' << "Title: " << disp->title << '\n';
                    std::cout << "Artist: " << disp->artist << '\n';
                    std::cout << "Mapper: " << disp->mapper << "\nDifficulty Name: " << disp->diffName << '\n';
                    std::cout << "Star Rating: " << disp->starRating << '\n';
                    std::cout << std::setprecision(1) << "CS: " << disp->cs << " AR: " << disp->ar << " OD: " << disp->od << " HP: " << disp->hp << '\n';
                    std::cout << disp->length / 60 << " minutes " << disp->length % 60 << " seconds\n";
                    std::cout << disp->websiteLink << '\n';
                }
                break;
            case 7:
                std::cout << "Welcome to the help page!\n";
                std::cout << "This application is designed to help you find the right osu! beatmap for you! \n";
                std::cout << "osu! is a rhythm game created in 2007 by Dean \"peppy\" Herbert. A beatmap is \n";
                std::cout << "akin to a level you can play and is developed by the players from scratch! \n";
                std::cout << "These players are what we call mappers. The star rating determines how difficult\n";
                std::cout << "the map really is, from being very easy at 1 star, to almost impossible at 10+\n";
                std::cout << "stars! Some terms you may want to know are\nCS: circle size\nAR: approach rate\n";
                std::cout << "OD: overall difficulty\nHP: health points\n";
                std::cout << "These are also values used to determine the difficulty of\n";
                std::cout << "a particular beatmap and range from 0 - 10.\n";
                std::cout << "If need be, you can also\n";
                run6 = true;

                while(run6)
                {
                    std::cout << "1. Display the list of tags\n";
                    std::cout << "2. Display the list of sources\n";
                    std::cout << "3. Display a list of mappers\n";
                    std::cout << "4. Go back\n";
                    in6 = "";
                    std::cin >> in6;
                    if (!checkValidInteger(in6)) //menu checking
                    {
                        continue;
                    }
                    submenu6 = stoi(in6);
                    if(!inRange(submenu6, 1, 4))
                    {
                        std::cout << "Please enter a valid menu option\n";
                        continue;
                    }
                    switch(submenu6)
                    {
                        case 1:
                            if (dso == 0)
                            {
                                tagdisp = frame.list.getTags();
                            }
                            else
                            {
                                tagdisp = frame.elist.getTags();
                            }
                            printSearch(tagdisp, 3);
                            break;
                        case 2:
                            if(dso == 0)
                            {
                                sourcedisp = frame.list.getSources();
                            }
                            else
                            {
                                sourcedisp = frame.elist.getSources();
                            }
                            printSearch(sourcedisp, 6);
                            break;
                        case 3:
                            if (dso == 0)
                            {
                                mapperdisp = frame.list.getMappers();
                            }
                            else
                            {
                                mapperdisp = frame.elist.getMappers();
                            }
                            
                            printSearch(mapperdisp, 6);
                            break;
                        case 4:
                            run6 = false;
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 8:
                //change the data structure in use
                if (dso == 0)
                {
                    dso = 1;
                }
                else
                {
                    dso = 0;
                }
                std::cout << "Now using: " << ds[dso];
                break;
            case 9:
                //exit case
                std::cout << "See you next time!";
                run = false;
                break;
            default:
                break;
        }
        std::cout << std::endl;
    }
    return 0;
}