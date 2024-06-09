#include "rating.h"
#include <iostream>

Rating::Rating() {
    loadUsers();
    loadGames();
    loadReviews();
}

Rating::~Rating()
{
    for (User *user : users)
    {
        delete user;
    }
    for (Game *game : games)
    {
        delete game;
    }
    for (Review *review : reviews)
    {
        delete review;
    }
}

void Rating::addUser(const std::string &username, const std::string &password, bool isAdmin)
{
    if (users.size() < MAX_USERS)
    {
        users.push_back(new User(username, password, isAdmin));
        saveUsers();
    }
}

void Rating::removeUser(const std::string &username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->getUsername() == username)
        {
            delete users[i];
            users.erase(users.begin() + i);
            saveUsers();
            return;
        }
    }
}

User *Rating::getUser(const std::string &username, const std::string &password)
{
    for (User *user : users)
    {
        if (user->getUsername() == username && user->getPassword() == password)
        {
            return user;
        }
    }
    return nullptr;
}

User *Rating::getUser(const std::string &username)
{
    for (User *user : users)
    {
        if (user->getUsername() == username)
        {
            return user;
        }
    }
    return nullptr;
}

std::vector<User *> Rating::getUsers()
{
    return users;
}

void Rating::saveUser(std::ofstream &file, User &user)
{
    std::string username = user.getUsername();

    if (username.empty())
    {
        return;
    }

    int usernameLength = username.size();
    file.write((char *)&usernameLength, sizeof(int));
    file.write(username.c_str(), usernameLength);

    std::string password = user.getPassword();
    int passwordLength = password.size();
    file.write((char *)&passwordLength, sizeof(int));
    file.write(password.c_str(), passwordLength);

    bool isAdmin = user.isAdmin();
    file.write((char *)&isAdmin, sizeof(bool));
}

void Rating::loadUser(std::ifstream &file, User &user)
{
    int usernameLength;
    file.read((char *)&usernameLength, sizeof(int));
    char *usernameBuffer = new char[usernameLength + 1];
    file.read(usernameBuffer, usernameLength);
    usernameBuffer[usernameLength] = '\0';
    std::string username(usernameBuffer);
    delete[] usernameBuffer;

    int passwordLength;
    file.read((char *)&passwordLength, sizeof(int));
    char *passwordBuffer = new char[passwordLength + 1];
    file.read(passwordBuffer, passwordLength);
    passwordBuffer[passwordLength] = '\0';
    std::string password(passwordBuffer);
    delete[] passwordBuffer;

    bool isAdmin;
    file.read((char *)&isAdmin, sizeof(bool));

    user = User(username, password, isAdmin);
}

void Rating::saveUsers()
{
    std::ofstream file("data/users.dat", std::ios::binary);
    if (file.is_open())
    {
        for (int i = 0; i < users.size(); i++)
        {
            saveUser(file, *users[i]);
        }
        file.close();
    }
}

void Rating::loadUsers()
{
    std::ifstream file("data/users.dat", std::ios::binary);
    if (file.is_open())
    {
        while (file.peek() != EOF)
        {
            User user;
            loadUser(file, user);
            addUser(user.getUsername(), user.getPassword(), user.isAdmin());
        }
        file.close();
    }
}

void Rating::addGame(int id, const std::string &name, const std::string &description, const std::string &releaseDate, const std::string &tags)
{
    if (games.size() < MAX_GAMES)
    {
        games.push_back(new Game(id, name, description, releaseDate, tags));
        saveGames();
    }
}

void Rating::addGame(const std::string &name, const std::string &description, const std::string &releaseDate, const std::string &tags)
{
    if (games.size() < MAX_GAMES)
    {
        int id = games.size() + 1;
        games.push_back(new Game(id, name, description, releaseDate, tags));
        saveGames();
    }
}

void Rating::removeGame(int id)
{
    for (int i = 0; i < games.size(); i++)
    {
        if (games[i]->getID() == id)
        {
            delete games[i];
            games.erase(games.begin() + i);
            saveGames();
            return;
        }
    }
}

void Rating::clearGames()
{
    for (Game *game : games)
    {
        delete game;
    }
    games.clear();
    saveGames();
}

Game *Rating::getGame(int id)
{
    for (Game *game : games)
    {
        if (game->getID() == id)
        {
            return game;
        }
    }
    return nullptr;
}

std::vector<Game *> Rating::getGames()
{
    return games;
}

void Rating::saveGame(std::ofstream &file, Game &game)
{
    int id = game.getID();
    file.write((char *)&id, sizeof(int));

    std::string name = game.getName();
    int nameLength = name.size();
    file.write((char *)&nameLength, sizeof(int));
    file.write(name.c_str(), nameLength);

    std::string description = game.getDescription();
    int descriptionLength = description.size();
    file.write((char *)&descriptionLength, sizeof(int));
    file.write(description.c_str(), descriptionLength);

    std::string releaseDate = game.getReleaseDate();
    int releaseDateLength = releaseDate.size();
    file.write((char *)&releaseDateLength, sizeof(int));
    file.write(releaseDate.c_str(), releaseDateLength);

    std::string tags = game.getTags();
    int tagsLength = tags.size();
    file.write((char *)&tagsLength, sizeof(int));
    file.write(tags.c_str(), tagsLength);
}

void Rating::loadGame(std::ifstream &file, Game &game)
{
    int id;
    file.read((char *)&id, sizeof(int));

    int nameLength;
    file.read((char *)&nameLength, sizeof(int));
    char *nameBuffer = new char[nameLength + 1];
    file.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    std::string name(nameBuffer);
    delete[] nameBuffer;

    int descriptionLength;
    file.read((char *)&descriptionLength, sizeof(int));
    char *descriptionBuffer = new char[descriptionLength + 1];
    file.read(descriptionBuffer, descriptionLength);
    descriptionBuffer[descriptionLength] = '\0';
    std::string description(descriptionBuffer);
    delete[] descriptionBuffer;

    int releaseDateLength;
    file.read((char *)&releaseDateLength, sizeof(int));
    char *releaseDateBuffer = new char[releaseDateLength + 1];
    file.read(releaseDateBuffer, releaseDateLength);
    releaseDateBuffer[releaseDateLength] = '\0';
    std::string releaseDate(releaseDateBuffer);
    delete[] releaseDateBuffer;

    int tagsLength;
    file.read((char *)&tagsLength, sizeof(int));
    char *tagsBuffer = new char[tagsLength + 1];
    file.read(tagsBuffer, tagsLength);
    tagsBuffer[tagsLength] = '\0';
    std::string tags(tagsBuffer);
    delete[] tagsBuffer;

    game = Game(id, name, description, releaseDate, tags);
}

void Rating::saveGames()
{
    std::ofstream file("data/games.dat", std::ios::binary);
    if (file.is_open())
    {
        for (int i = 0; i < games.size(); i++)
        {
            saveGame(file, *games[i]);
        }
        file.close();
    }
}

void Rating::loadGames()
{
    std::ifstream file("data/games.dat", std::ios::binary);
    if (file.is_open())
    {
        while (file.peek() != EOF)
        {
            Game game;
            loadGame(file, game);
            addGame(game.getID(), game.getName(), game.getDescription(), game.getReleaseDate(), game.getTags());
        }
        file.close();
    }
}

void Rating::addReview(int id, Game *game, User *user, int rating, const std::string &text)
{
    if (reviews.size() < MAX_REVIEWS)
    {
        reviews.push_back(new Review(id, game, user, rating, text));
        saveReviews();
    }
}

void Rating::addReview(Game *game, User *user, int rating, const std::string &text)
{
    if (reviews.size() < MAX_REVIEWS)
    {
        int id = reviews.size() + 1;
        reviews.push_back(new Review(id, game, user, rating, text));
        saveReviews();
    }
}

void Rating::removeReview(int id)
{
    for (int i = 0; i < reviews.size(); i++)
    {
        if (reviews[i]->getID() == id)
        {
            delete reviews[i];
            reviews.erase(reviews.begin() + i);
            saveReviews();
            return;
        }
    }
}

void Rating::clearReviews()
{
    for (Review *review : reviews)
    {
        delete review;
    }
    reviews.clear();
    saveReviews();
}

Review *Rating::getReview(int id)
{
    for (Review *review : reviews)
    {
        if (review->getID() == id)
        {
            return review;
        }
    }
    return nullptr;
}

std::vector<Review *> Rating::getReviews()
{
    return reviews;
}

void Rating::saveReview(std::ofstream &file, Review &review)
{
    int Id = review.getID();
    file.write((char *)&Id, sizeof(int));

    int gameId = review.getGame()->getID();
    file.write((char *)&gameId, sizeof(int));

    std::string username = review.getUsername();
    int usernameLength = username.size();
    file.write((char *)&usernameLength, sizeof(int));
    file.write(username.c_str(), usernameLength);

    int rating = review.getRating();
    file.write((char *)&rating, sizeof(int));

    std::string text = review.getText();
    int textLength = text.size();
    file.write((char *)&textLength, sizeof(int));
    file.write(text.c_str(), textLength);
}

void Rating::loadReview(std::ifstream &file, Review &review)
{
    int id;
    file.read((char *)&id, sizeof(int));

    int gameId;
    file.read((char *)&gameId, sizeof(int));

    int usernameLength;
    file.read((char *)&usernameLength, sizeof(int));
    char *usernameBuffer = new char[usernameLength + 1];
    file.read(usernameBuffer, usernameLength);
    usernameBuffer[usernameLength] = '\0';
    std::string username(usernameBuffer);
    delete[] usernameBuffer;

    int rating;
    file.read((char *)&rating, sizeof(int));

    int textLength;
    file.read((char *)&textLength, sizeof(int));
    char *textBuffer = new char[textLength + 1];
    file.read(textBuffer, textLength);
    textBuffer[textLength] = '\0';
    std::string text(textBuffer);
    delete[] textBuffer;

    Game *game = getGame(gameId);
    User *user = getUser(username);
    review = Review(id, game, user, rating, text);
}

void Rating::saveReviews()
{
    std::ofstream file("data/reviews.dat", std::ios::binary);
    if (file.is_open())
    {
        for (int i = 0; i < reviews.size(); i++)
        {
            saveReview(file, *reviews[i]);
        }
        file.close();
    }
}

void Rating::loadReviews()
{
    std::ifstream file("data/reviews.dat", std::ios::binary);
    if (file.is_open())
    {
        while (file.peek() != EOF)
        {
            Review review;
            loadReview(file, review);
            addReview(review.getID(), review.getGame(), review.getUser(), review.getRating(), review.getText());
        }
        file.close();
    }
}

void Rating::printGames() const
{
    for (Game *game : games)
    {
        std::cout << game->getID() << " " << game->getName() << " " << game->getDescription() << " " << game->getReleaseDate() << " " << game->getTags() << std::endl;
    }
}

void Rating::printReviews() const
{
    for (Review *review : reviews)
    {
        std::cout << review->getGameName() << " " << review->getUsername() << " " << review->getRating() << " " << review->getText() << std::endl;
    }
}

void Rating::generateTestData()
{
    addUser("admin", "admin", true);
    addUser("user1", "password1", false);
    addUser("user2", "password2", false);
    addUser("user3", "password3", false);

    addGame(1, "The Legend of Zelda: Breath of the Wild", "An open-world adventure game with stunning graphics and immersive gameplay.", "3 March, 2017", "Adventure, RPG");
    addGame(2, "The Witcher 3: Wild Hunt", "A story-driven, open world RPG set in a visually stunning fantasy universe full of meaningful choices and impactful consequences.", "19 May, 2015", "RPG, Adventure");
    addGame(3, "Red Dead Redemption 2", "An epic tale of life in America at the dawn of the modern age.", "26 October, 2018", "Action, Adventure");
    addGame(4, "Cyberpunk 2077", "An open-world, action-adventure story set in Night City, a megalopolis obsessed with power, glamour and body modification.", "10 December, 2020", "RPG, Sci-Fi");
    addGame(5, "Hades", "A rogue-like dungeon crawler that combines the best aspects of Supergiant's critically acclaimed titles.", "17 September, 2020", "Rogue-like, Action");

    addReview(1, getGame(1), getUser("user1"), 5, "An absolute masterpiece! The freedom and exploration are unparalleled.");
    addReview(2, getGame(2), getUser("user2"), 5, "The storytelling and character development are top-notch. One of the best RPGs ever made.");
    addReview(3, getGame(3), getUser("user3"), 4, "Incredible world-building and attention to detail. A must-play.");
    addReview(4, getGame(4), getUser("user1"), 3, "Great visuals and setting, but the game has many bugs that detract from the experience.");
    addReview(5, getGame(5), getUser("user2"), 5, "Fast-paced and challenging gameplay with a great story. Supergiant Games did it again.");
    addReview(6, getGame(1), getUser("user3"), 4, "Amazing game with lots of things to do, but the combat can be a bit repetitive.");
    addReview(7, getGame(2), getUser("user1"), 4, "Fantastic game with an engaging story, though some quests can feel a bit tedious.");
    addReview(8, getGame(3), getUser("user2"), 5, "A true masterpiece in terms of narrative and world design. Highly recommend.");
    addReview(9, getGame(4), getUser("user3"), 2, "Disappointed with the bugs and performance issues. Expected more from CD Projekt Red.");
    addReview(10, getGame(5), getUser("user1"), 5, "Absolutely addictive. Every run feels fresh and exciting.");
}