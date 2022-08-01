#include "AdjList.h"
#include "EdgeList.h"
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
class BeatmapListing
{
    private:
        std::vector<Beatmap*> maps;
    public:
        AdjList list;
        EdgeList elist;
        BeatmapListing();

        void readFile(std::string fileName);
        double getScore(Beatmap* b, Beatmap* a);


        std::vector<std::string> getMaps(Beatmap* b, std::string id);
        std::vector<std::string> getEMaps(Beatmap* b, std::string id);
};

BeatmapListing::BeatmapListing()
{
    //nothing here
}

double BeatmapListing::getScore(Beatmap* userPref, Beatmap* target)
{
    //weighting things based off of arbitrary things -> results in an ordered output
    double weight = 0.0;
    //mode
    if (userPref->mode == target->mode)
    {
        weight += 100000;
    }
    float a = (target->starRating - userPref->starRating) + 0.01f;
    float b = (1 / a) * 100;
    weight += (double)b;
    float c = (target->cs - userPref->cs) + 0.01f;
    float d = (1 / c) * 80;
    weight += (double)d;
    float e = (target->ar - userPref->ar) + 0.01f;
    float f = (1 / e) * 80;
    weight += (double)f;
    float g = (target->od - userPref->od) + 0.01f;
    float h = (1 / g) * 80;
    weight += (double)h;
    float i = (target->hp - userPref->hp) + 0.01f;
    float j = (1 / i) * 80;
    weight += (double)j;
    return weight;
}

std::vector<std::string> BeatmapListing::getMaps(Beatmap* userPref, std::string id)
{
    std::vector<std::string> out;
    std::string find;
    std::map<double, std::string> temp;
    GraphNode* node = list.getNode(id);
    std::vector<GraphNode*> adjacent = list.getAdjacent(id);
    //finds all maps adjacent to id and returns them in order of score
    std::priority_queue<std::pair<double, std::string>> pq;
    for(int i = 0; i < adjacent.size(); ++i)
    {
        pq.emplace(std::make_pair(getScore(userPref, adjacent[i]->getBeatmap()), adjacent[i]->getName()));   
    }
    while(!pq.empty())
    {
        out.push_back(pq.top().second);
        pq.pop();
    }
    return out;
}
std::vector<std::string> BeatmapListing::getEMaps(Beatmap* userPref, std::string id)
{
    std::vector<std::string> out;
    std::string find;
    std::map<double, std::string> temp;
    GraphNode* node = elist.getNode(id);
    std::vector<GraphNode*> adjacent = elist.getAdjacent(id);
    //finds all maps adjacent to id and returns them in order of score
    std::priority_queue<std::pair<double, std::string>> pq;
    for(int i = 0; i < adjacent.size(); ++i)
    {
        pq.emplace(std::make_pair(getScore(userPref, adjacent[i]->getBeatmap()), adjacent[i]->getName()));   
    }
    while(!pq.empty())
    {
        out.push_back(pq.top().second);
        pq.pop();
    }
    return out;
}


void BeatmapListing::readFile(std::string fileName)
{
    std::ifstream file(fileName);
    std::string header;
    getline(file, header); //read header

    std::string line;
    while(getline(file, line))
    {
        std::stringstream ss(line);
        std::string beatmapset_id;
        std::string beatmap_id;
        std::string total_length;
        std::string diff_name;
        std::string cs, od, ar, hp;
        std::string mode;
        std::string approved_date;
        std::string artists;
        std::string artist_unicode;
        std::string title;
        std::string title_unicode;
        std::string mapper;
        std::string bpm;
        std::string source;
        std::string tags;
        std::string genre_id, language_id;
        std::string favorite_count;
        std::string rating;
        std::string playcount;
        std::string star_rating;

        std::string temp; //used as a junk filter
        getline(ss, temp, ','); //junk
        getline(ss, temp, ','); //junk
        getline(ss, temp, ','); //audio_hash
        getline(ss, beatmapset_id, ','); //beatmapset_id
        getline(ss, beatmap_id, ','); //beatmap_id
        getline(ss, temp, ','); //approved
        getline(ss, total_length, ','); //total_length (sec)
        getline(ss, temp, ','); //hit_length
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, diff_name, '"');
            ss.get();
        }
        else
        {
            getline(ss, diff_name, ','); //diff name
        }
        getline(ss, temp, ','); //file_md5
        getline(ss, cs, ','); //cs (circle size)
        getline(ss, od, ','); //od (overall difficulty)
        getline(ss, ar, ','); //ar (approach rate)
        getline(ss, hp, ','); //hp (health points)
        getline(ss, mode, ','); //mode
        getline(ss, temp, ','); //circle count
        getline(ss, temp, ','); //slider count
        getline(ss, temp, ','); //spinner count
        getline(ss, temp, ','); //submit date
        getline(ss, approved_date, ','); //approved date
        getline(ss, temp, ','); //last update
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, artists, '"'); //artist(s)
            ss.get();
        }
        else
        {
            getline(ss, artists, ','); //artist(s)
        }
        if(ss.peek() == 34)
        {
            ss.get();
            getline(ss, artist_unicode, '"'); //artist_unicode
            ss.get();
        }
        else
        {
            getline(ss, artist_unicode, ','); //artist_unicode
        }
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, title, '"'); //title
            ss.get();
        }
        else
        {
            getline(ss, title, ','); //title
        }
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, title_unicode, '"'); //title_unicode
            ss.get();
        }
        else
        {
            getline(ss, title_unicode, ','); //title_unicode
        }
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, mapper, '"');
            ss.get();
        }
        else
        {
            getline(ss, mapper, ','); //mapper
        }
        getline(ss, temp, ','); //mapper_id
        getline(ss, bpm, ','); //bpm
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, source, '"'); //source
            ss.get();
        }
        else
        {
            getline(ss, source, ','); //source
        }
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, tags, '"'); //tags
            ss.get();
        }
        else
        {
            getline(ss, tags, ','); //tags
        }
        getline(ss, genre_id, ','); //genre_id
        getline(ss, language_id, ','); //language_id
        getline(ss, favorite_count, ','); //favorite_count
        getline(ss, rating, ','); //rating(?)
        getline(ss, temp, ','); //storyboard (0 or 1)
        getline(ss, temp, ','); //video (0 or 1)
        getline(ss, temp, ','); //download_unavailable
        getline(ss, temp, ','); //audio_unavailable
        getline(ss, playcount, ','); //playcount
        getline(ss, temp, ','); //passcount
        if (ss.peek() == 34)
        {
            ss.get();
            getline(ss, temp, '"'); //packs
            ss.get();
        }
        else
        {
            getline(ss, temp, ','); //packs
        }
        getline(ss, temp, ','); //max_combo
        getline(ss, temp, ','); //diff_aim
        getline(ss, temp, ','); //diff_speed
        getline(ss, star_rating, '\n'); //star rating

        std::string arr[24];
        arr[0] = title;
        arr[1] = title_unicode;
        arr[2] = diff_name;
        arr[3] = mapper;
        arr[4] = artists;
        arr[5] = artist_unicode;
        arr[6] = source;
        arr[7] = tags;
        arr[8] = approved_date;
        arr[9] = favorite_count;
        arr[10] = playcount;
        arr[11] = total_length;
        arr[12] = star_rating;
        arr[13] = bpm;
        arr[14] = cs;
        arr[15] = ar;
        arr[16] = od;
        arr[17] = hp;
        arr[18] = rating;
        arr[19] = genre_id;
        arr[20] = language_id;
        arr[21] = mode;
        arr[22] = beatmapset_id;
        arr[23] = beatmap_id;

        Beatmap* newMap = new Beatmap(arr); //create beatmap
        maps.push_back(newMap);
        list.insertVertex(newMap);
        elist.insertVertex(newMap);
    }
}