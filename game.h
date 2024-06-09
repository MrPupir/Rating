#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <ctime>

class Game {
private:
    int id;
    std::string name;
    std::string description;
    std::string releaseDate;
    std::string tags;
public:
    Game();
    Game(int id, const std::string& name, const std::string& description, const std::string& releaseDate, const std::string& tags);
    int getID() const;
    void setID(int id);
    std::string getName() const;
    void setName(const std::string& name);
    std::string getDescription() const;
    void setDescription(const std::string& description);
    std::string getReleaseDate() const;
    void setReleaseDate(const std::string& releaseDate);
    std::string getTags() const;
    void setTags(const std::string& tags);
};

#endif