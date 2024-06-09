#include "review.h"

Review::Review()
    : game(nullptr), user(nullptr), rating(0), text("") {}

Review::Review(int id, Game *game, User *user, int rating, const std::string &text)
    : id(id), game(game), user(user), rating(rating), text(text) {}

int Review::getID() const
{
    return id;
}

void Review::setID(int id)
{
    this->id = id;
}

Game* Review::getGame() const
{
    return game;
}

std::string Review::getGameName() const
{
    return game->getName();
}

User* Review::getUser() const
{
    return user;
}

std::string Review::getUsername() const
{
    return user->getUsername();
}

int Review::getRating() const
{
    return rating;
}

void Review::setRating(int rating)
{
    this->rating = rating;
}

std::string Review::getText() const
{
    return text;
}

void Review::setText(const std::string &text)
{
    this->text = text;
}