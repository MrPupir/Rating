#include "game.h"

Game::Game()
    : id(0), name(""), description(""), releaseDate(), tags("") {}

Game::Game(int id, const std::string& name, const std::string& description, const std::string& releaseDate, const std::string& tags)
    : id(id), name(name), description(description), releaseDate(releaseDate), tags(tags) {}

int Game::getID() const
{
    return id;
}

void Game::setID(int id)
{
    this->id = id;
}

std::string Game::getName() const
{
    return name;
}

void Game::setName(const std::string& name)
{
    this->name = name;
}

std::string Game::getDescription() const
{
    return description;
}

void Game::setDescription(const std::string& description)
{
    this->description = description;
}

std::string Game::getReleaseDate() const
{
    return releaseDate;
}

void Game::setReleaseDate(const std::string& releaseDate)
{
    this->releaseDate = releaseDate;
}

std::string Game::getTags() const
{
    return tags;
}

void Game::setTags(const std::string& tags)
{
    this->tags = tags;
}