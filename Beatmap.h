#pragma once
#include <string>
#include <vector>
#include <sstream>

//a place to store all the data of a beatmap
struct Beatmap
{
    std::string tags;
    std::string title;
    std::string mapper;
    std::string artist;
    std::string source;
    std::string diffName;
    std::string beatmap_id;
    std::string websiteLink;
    std::string approved_date;
    std::string beatmapset_id;
    std::string title_unicode;
    std::string artist_unicode;
    float cs;
    float od;
    float ar;
    float hp;
    int mode;
    float bpm;
    int length;
    float rating;
    int genre_id;
    int playcount;
    int language_id;
    float starRating;
    int favorite_count;
    int id;
    
    std::vector<std::string> tagList;

    Beatmap();
    Beatmap(std::string arr[]);
};

Beatmap::Beatmap()
{
    id = 0;
    beatmapset_id = "";
    beatmap_id = "";
    websiteLink = "";
    diffName = "";
    length = 0;
    cs = 0 ;
    od = 0;
    ar = 0;
    hp = 0;
    mode = 0;
    artist = "";
    title = "";
    mapper = "";
    bpm = 0.0f;
    tags = "";
    rating = 0.0f;
    starRating = 0.0f;
    title_unicode = "";
    artist_unicode = "";
    source = "";
    approved_date = "";
    favorite_count = 0;
    playcount = 0;
    language_id = 0;
    genre_id = 0;
    
}
Beatmap::Beatmap(std::string arr[])
{
    title = arr[0];
    title_unicode = arr[1];
    diffName = arr[2];
    mapper = arr[3];
    artist = arr[4];
    artist_unicode = arr[5];
    source = arr[6];
    tags = arr[7];
    approved_date = arr[8];
    favorite_count = stoi(arr[9]);
    playcount = stoi(arr[10]);
    length = stoi(arr[11]);
    starRating = stof(arr[12]);
    bpm = stof(arr[13]);
    cs = stof(arr[14]);
    ar = stof(arr[15]);
    od = stof(arr[16]);
    hp = stof(arr[17]);
    rating = stof(arr[18]);
    genre_id = stoi(arr[19]);
    language_id = stoi(arr[20]);
    mode = stoi(arr[21]);
    beatmapset_id = arr[22];
    beatmap_id = arr[23];
    id = stoi(beatmap_id);

    //create the web link
    websiteLink = "https://osu.ppy.sh/beatmapsets/";
    websiteLink += beatmapset_id;
    switch(mode)
    {
        case 0:
            websiteLink += "#osu/";
            break;
        case 1:
            websiteLink += "#taiko/";
            break;
        case 2:
            websiteLink += "#fruits/";
            break;
        case 3:
            websiteLink += "#mania/";
            break;
        default:
            break;   
    }
    websiteLink += beatmap_id;

    //separate the tags
    std::stringstream t(tags);
    std::string separate;
    while(getline(t, separate, ' '))
    {
        tagList.push_back(separate);
    }
}