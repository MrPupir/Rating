#ifndef RATING_H
#define RATING_H

#include <vector>
#include <fstream>
#include <windows.h>
#include "user.h"
#include "game.h"
#include "review.h"

const int MAX_USERS = 20;
const int MAX_GAMES = 50;
const int MAX_REVIEWS = 100;

class Rating {
private:
    std::vector<User*> users;
    std::vector<Game*> games;
    std::vector<Review*> reviews;

public:
    Rating();
    ~Rating();

    void addUser(const std::string& username, const std::string& password, bool isAdmin);
    void removeUser(const std::string& username);
    User *getUser(const std::string& username, const std::string& password);
    User *getUser(const std::string& username);
    std::vector<User *> getUsers();
    void saveUser(std::ofstream& file, User& user);
    void loadUser(std::ifstream& file, User& user);
    void saveUsers();
    void loadUsers();
    void addGame(int id, const std::string& name, const std::string& description, const std::string& releaseDate, const std::string& tags);
    void addGame(const std::string& name, const std::string& description, const std::string& releaseDate, const std::string& tags);
    void removeGame(int id);
    void clearGames();
    Game *getGame(int id);
    std::vector<Game *> getGames();
    void saveGame(std::ofstream& file, Game& game);
    void loadGame(std::ifstream& file, Game& game);
    void saveGames();
    void loadGames();
    void addReview(int id, Game* game, User* user, int rating, const std::string& text);
    void addReview(Game* game, User* user, int rating, const std::string& text);
    void removeReview(int id);
    void clearReviews();
    Review *getReview(int id);
    std::vector<Review *> getReviews();
    void saveReview(std::ofstream& file, Review& review);
    void loadReview(std::ifstream& file, Review& review);
    void saveReviews();
    void loadReviews();
    void printGames() const;
    void printReviews() const;
    void generateTestData();
};

#endif