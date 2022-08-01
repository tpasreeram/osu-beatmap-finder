#include "GraphNode.h"
#include <map>
#include <set>

class EdgeList
{
    private:
        std::vector<std::pair<GraphNode*, GraphNode*>> graph;
        std::map<std::string, GraphNode*> data;
        GraphNode* a;

        std::set<std::string> mappers;
        std::set<std::string> sources;
        std::set<std::string> tags;
        std::set<std::string> lengths;
        std::set<std::string> stars;
        std::set<std::string> languages;
        std::set<std::string> genres;
        std::set<std::string> modes;
        std::set<std::string> artists;
        std::set<std::string> titles;

        std::set<std::string> css;
        std::set<std::string> ars;
        std::set<std::string> ods;
        std::set<std::string> hps;
    public:
        EdgeList();

        void insertEdge(std::string from, std::string to);
        void createNode(std::string from, std::string to);
        void insertVertex(Beatmap* b);

        std::vector<GraphNode*> getAdjacent(std::string n);
        GraphNode* getNode(std::string n);
        std::set<std::string> getTags();
        std::set<std::string> getSources();
        std::set<std::string> getMappers();
};

EdgeList::EdgeList()
{
    //create source node to connect all nodes
    a = new GraphNode("0");
    data["0"] = a;
}

GraphNode* EdgeList::getNode(std::string n)
{
    //get the node the string is referencing
    return data[n];
}
std::vector<GraphNode*> EdgeList::getAdjacent(std::string n)
{
    //get all adjacent nodes
    std::vector<GraphNode*> out;
    for(int i = 0; i < graph.size(); ++i)
    {
        if (graph[i].first->getName().compare(n) == 0)
        {
            out.push_back(graph[i].second);
        }
    }
    return out;
}
std::set<std::string> EdgeList::getTags()
{
    return tags;
}
std::set<std::string> EdgeList::getSources()
{
    return sources;
}
std::set<std::string> EdgeList::getMappers()
{
    return mappers;
}

void EdgeList::insertEdge(std::string from, std::string to)
{
    //adds an undirected edge between from and to
    graph.push_back(std::make_pair(data.find(from)->second, data.find(to)->second));
    graph.push_back(std::make_pair(data.find(to)->second, data.find(from)->second));
}
void EdgeList::createNode(std::string from, std::string to)
{
    //creates node to and adds an undirected edge between them
    GraphNode* node = new GraphNode(to);
    data[to] = node;
    graph.push_back(std::make_pair(data.find(from)->second, data.find(to)->second));
    graph.push_back(std::make_pair(data.find(to)->second, data.find(from)->second));
}

void EdgeList::insertVertex(Beatmap* b)
{
    //connects the beatmap b to the source node
    GraphNode* bm = new GraphNode(b->beatmap_id, b);
    createNode("0", bm->getName());
    data[bm->getName()] = bm;
        
    //and other possible nodes, such as

    //mappers
    std::string mapper = b->mapper+"mapper";
    if (mappers.find(mapper) == mappers.end())
    {
        mappers.emplace(mapper);
        createNode(b->beatmap_id, mapper);
    }
    else
    {
        insertEdge(b->beatmap_id, mapper);
    }

    //titles
    std::string title = b->title+"title";
    if (titles.find(title) == titles.end())
    {
        titles.emplace(title);
        createNode(b->beatmap_id, title);
    }
    else
    {
        insertEdge(b->beatmap_id, title);
    }

    //artists
    std::string artist = b->artist+"artist";
    if (artists.find(artist) == artists.end())
    {
        artists.emplace(artist);
        createNode(b->beatmap_id, artist);
    }
    else
    {
        insertEdge(b->beatmap_id, artist);
    }

    //sources
    if (b->source.compare("") != 0)
    {
        std::string source = b->source+"source";
        if (sources.find(source) == sources.end())
        {
            sources.emplace(source);
            createNode(b->beatmap_id, source);
        }
        else
        {
            insertEdge(b->beatmap_id, source);
        }
    }

    //tags
    for(int i = 0 ; i < b->tagList.size(); ++i)
    {
        std::string tag = b->tagList[i]+"tag";
        if (tags.find(tag) == tags.end())
        {
            tags.emplace(tag);
            createNode(b->beatmap_id, tag);
        }
        else
        {
            insertEdge(b->beatmap_id, tag);
        }
    }
    //lengths
    std::string length;
    if (b->length <= 30)
    {
        length = "< 30 sec";
    }
    else if (b->length > 30 && b->length <= 75)
    {
        length = "30sec - 1:15";
    }
    else if (b->length > 75 && b->length <= 150)
    {
        length = "1:15 - 2:30";
    }
    else if (b->length > 150 && b->length <= 300)
    {
        length = "2:30 - 5:00";
    }
    else if (b->length > 300 && b->length <= 600)
    {
        length = "5:00 - 10:00";
    }
    else if (b->length > 600 && b->length <= 1200)
    {
        length = "10:00 - 20:00";
    }
    else if (b->length > 1200)
    {
        length = "> 20:00";
    }
    if(lengths.find(length) == lengths.end())
    {
        lengths.emplace(length);
        createNode(b->beatmap_id, length);
    }
    else
    {
        insertEdge(b->beatmap_id, length);
    }


    //star ratings
    std::string starr;
    if (b->starRating <= 1)
    {
        starr = "< 1";
    }
    else if (b->starRating > 1 && b->starRating <= 2)
    {
        starr = "1 - 2";
    }
    else if (b->starRating > 2 && b->starRating <= 3)
    {
        starr = "2 - 3";
    }
    else if (b->starRating > 3 && b->starRating <= 4)
    {
        starr = "3 - 4";
    }
    else if (b->starRating > 4 && b->starRating <= 5)
    {
        starr = "4 - 5";
    }
    else if (b->starRating > 5 && b->starRating <= 6)
    {
        starr = "5 - 6";
    }
    else if (b->starRating > 6 && b->starRating <= 7)
    {
        starr = "6 - 7";
    }
    else if (b->starRating > 7 && b->starRating <= 8)
    {
        starr = "7 - 8";
    }
    else if (b->starRating > 8)
    {
        starr = "> 8";
    }
    if(stars.find(starr) == stars.end())
    {
        stars.emplace(starr);
        createNode(b->beatmap_id, starr);
    }
    else
    {
        insertEdge(b->beatmap_id, starr);
    }

    //genres
    std::string genre;
    switch(b->genre_id)
    {
        case 0:
            genre = "anygenre";
            break;
        case 1:
            genre = "unspecifiedgenre";
            break;
        case 2:
            genre = "video gamegenre";
            break;
        case 3:
            genre = "animegenre";
            break;
        case 4:
            genre = "rockgenre";
            break;
        case 5:
            genre = "popgenre";
            break;
        case 6:
            genre = "othergenre";
            break;
        case 7:
            genre = "noveltygenre";
            break;
        case 9:
            genre = "hip hopgenre";
            break;
        case 10:
            genre = "electronicgenre";
            break;
        case 11:
            genre = "metalgenre";
            break;
        case 12:
            genre = "classicalgenre";
            break;
        case 13:
            genre = "folkgenre";
            break;
        case 14:
            genre = "jazzgenre";
            break;
        default:
            break;
    }
    if(genres.find(genre) == lengths.end())
    {
        genres.emplace(genre);
        createNode(b->beatmap_id, genre);
    }
    else
    {
        insertEdge(b->beatmap_id, genre);
    }

    //languages
    std::string language;
    switch(b->language_id)
    {
        case 0:
            language = "any";
            break;
        case 1:
            language = "unspecified";
            break;
        case 2:
            language = "english";
            break;
        case 3:
            language = "japanese";
            break;
        case 4:
            language = "chinese";
            break;
        case 5:
            language = "instrumental";
            break;
        case 6:
            language = "korean";
            break;
        case 7:
            language = "french";
            break;
        case 8:
            language = "germam";
            break;
        case 9:
            language = "swedish";
            break;
        case 10:
            language = "spanish";
            break;
        case 11:
            language = "italian";
            break;
        case 12:
            language = "russian";
            break;
        case 13:
            language = "polish";
            break;
        case 14:
            language = "other";
            break;
        default:
            break;
    }
    if(languages.find(language) == languages.end())
    {
        languages.emplace(language);
        createNode(b->beatmap_id, language);
    }
    else
    {
        insertEdge(b->beatmap_id, language);
    }

    //and modes
    std::string mode = "";
    switch(b->mode)
    {
        case 0:
            mode = "osu!";
            break;
        case 1:
            mode = "osu!taiko";
            break;
        case 2:
            mode = "osu!catch";
            break;
        case 3:
            mode = "osu!mania";
            break;
        default:
            break;
    }
    if(modes.find(mode) == modes.end())
    {
        modes.emplace(mode);
        createNode(b->beatmap_id, mode);
    }
    else
    {
        insertEdge(b->beatmap_id, mode);
    }
}