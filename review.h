#ifndef REVIEW_H
#define REVIEW_H

#include <string>
#include "game.h"
#include "user.h"

class Review {
private:
    int id;
    Game* game;
    User* user;
    int rating;
    std::string text;
public:
    Review();
    Review(int id, Game* game, User* user, int rating, const std::string& text);
    int getID() const;
    void setID(int id);
    Game* getGame() const;
    std::string getGameName() const;
    User* getUser() const;
    std::string getUsername() const;
    int getRating() const;
    void setRating(int rating);
    std::string getText() const;
    void setText(const std::string& text);
};

#endif