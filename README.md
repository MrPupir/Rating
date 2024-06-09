# Game Review Application

## Overview

This is a console-based application that allows users to interact with a game review system. Users can view reviews, search for games by name or tags, add their own reviews, and manage their reviews. Admin users have additional capabilities to add, edit, and delete games from the system. The application uses custom `Window` and `Rating` classes to handle the UI and backend functionality.

## Features

### User Features
- **View Reviews**: Users can view a list of games along with their average ratings. Selecting a game shows its reviews.
- **Search Games**: Users can search for games by name or tags.
- **Add Review**: Users can add reviews for games they haven't reviewed yet.
- **Manage Reviews**: Users can view, edit, and delete their own reviews.

### Admin Features
- **Add Game**: Admins can add new games to the system.
- **Edit Game**: Admins can edit details of existing games.
- **Delete Game**: Admins can delete games from the system.

## Code Structure

### Main Components

1. **Global Variables**
   - `User *currentUser`: Pointer to the currently logged-in user.
   - `Rating rating`: Instance of the `Rating` class that handles game and review data.

2. **Functions**

   - `void reviewsMenu(int selectedGame = -1)`: Displays the list of games and their reviews. If a game is selected, it shows the reviews for that game.
   - `void clientMenu()`: Displays the main menu for regular users with options to view reviews, search games, add reviews, and manage their reviews.
   - `void adminMenu()`: Displays the main menu for admin users with options to add, edit, and delete games, as well as manage reviews and users.

### Key Classes (Assumed)

- **Game**: Represents a game with attributes like ID, name, description, release date, and tags.
- **Review**: Represents a review with attributes like game, user, rating, and text.
- **User**: Represents a user with attributes like username and password.
- **Rating**: Manages collections of games and reviews, providing methods to interact with these collections.
- **Window**: Handles the UI elements like windows, buttons, inputs, and labels.

### Sample Usage

1. **Main Menu**: Upon launching the application, users are presented with a menu to select their desired action.
2. **Reviews Menu**: Users can browse games and view their average ratings. Selecting a game displays its reviews.
3. **Add Review**: Users can add a new review for a game they haven't reviewed yet.
4. **Admin Menu**: Admins can add, edit, or delete games and manage user reviews.

## How to Run

1. **Compile the Program**: Ensure all necessary header files are included and compile the main file.
2. **Run the Program**: Execute the compiled binary.

## Future Enhancements

- **User Authentication**: Implement user login and registration functionality.
- **Improved UI**: Enhance the console UI for better user experience.
- **Database Integration**: Replace in-memory data storage with a persistent database.

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
