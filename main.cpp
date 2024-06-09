#include <iostream>
#include <conio.h>
#include <vector>
#include "window.h"
#include "rating.h"

using namespace std;

User *currentUser = nullptr;

Rating rating;

void reviewsMenu(int selectedGame = -1)
{
	vector<string> options;
	vector<string> gameNames;
	vector<string> gameIds;

	for (Game *game : rating.getGames())
	{
		double average = 0;
		int count = 0;

		for (Review *review : rating.getReviews())
		{
			if (review->getGame() == game)
			{
				average += review->getRating();
				count++;
			}
		}

		if (count > 0)
		{
			average /= count;
		}

		string averageStr = to_string(average);
		averageStr.erase(averageStr.find_last_not_of('0') + 1, string::npos);

		if (averageStr[averageStr.size() - 1] == '.')
		{
			averageStr.pop_back();
		}

		if (averageStr.size() > 3)
		{
			averageStr = averageStr.substr(0, 3);
		}

		options.push_back(game->getName() + " (" + averageStr + "/5)");
		gameNames.push_back(game->getName());
		gameIds.push_back(to_string(game->getID()));
	}

	Window games(0, 0, 60, 14, "Всi iгри");
	games.Center();
	games.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
	games.AddArray(0, 0, 58, 10, options, true);

	while (true)
	{
		Clear();

		int callback;

		if (selectedGame >= 0)
		{
			int index = -1;
			for (int i = 0; i < gameIds.size(); i++)
			{
				if (gameIds[i] == to_string(selectedGame))
				{
					index = i;
					break;
				}
			}

			callback = index;
			selectedGame = -1;
		}
		else
		{
			callback = games.DrawElementsLoop(true);
		}

		if (callback >= 0)
		{
			vector<Review *> reviews;

			for (Review *review : rating.getReviews())
			{
				if (review->getGameName() == gameNames[callback])
				{
					reviews.push_back(review);
				}
			}

			Window reviewsWindow(0, 0, 60, 15, "Вiдгуки");
			reviewsWindow.Center();
			reviewsWindow.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);

			int index = 0;

			reviewsWindow.AddButton(0, -2, 20, 1, 0, "Попереднiй");
			reviewsWindow.AddButton(38, -2, 20, 1, 1, "Наступний");
			reviewsWindow.AddButton(0, 10, 58, 1, 2, "Вийти");
			string gameName = reviews[index]->getGameName();
			int centerGameName = (58 - gameName.size()) / 2;
			reviewsWindow.AddLabel(centerGameName, 0, gameName.size(), 1, gameName);
			reviewsWindow.AddLabel(26, 2, 6, 3, reviews[index]->getUsername());
			reviewsWindow.AddLabel(0, 4, 58, 3, reviews[index]->getText());
			reviewsWindow.AddLabel(22, 8, 14, 1, "Рейтинг: " + to_string(reviews[index]->getRating()) + " / 5");

			reviewsWindow.SetActiveElement(0);

			while (true)
			{
				int callback = reviewsWindow.DrawElementsLoop(false, true);

				if (callback == 1 || callback == 0)
				{
					if (callback == 1)
					{
						index++;
					}
					else
					{
						index--;
					}

					if (index < 0)
					{
						index = reviews.size() - 1;
					}
					else if (index >= reviews.size())
					{
						index = 0;
					}

					reviewsWindow.SetElementInfo(4, reviews[index]->getUsername());
					reviewsWindow.SetElementInfo(5, reviews[index]->getText());
					reviewsWindow.SetElementInfo(6, "Рейтинг: " + to_string(reviews[index]->getRating()) + " / 5");
				}
				else if (callback == -1 || callback == 2)
				{
					break;
				}
			}
		}
		else if (callback == -1)
		{
			break;
		}
	}
}

void clientMenu()
{
	Window window(0, 0, 30, 10, "Меню клiєнта");
	window.Center();
	window.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
	window.AddArray(0, 0, 28, 6, {"Меню вiдгукiв", "Пошук гри", "Пошук гри за тегом", "Вiдгук про гру", "Мої вiдгуки", "Вихiд"}, true);

	while (true)
	{
		Clear();

		int callback = window.DrawElementsLoop(true);

		if (callback >= 0)
		{
			int menu = stoi(window.GetElementInfo(0));

			if (menu == 0)
			{
				Clear();

				reviewsMenu();
			}
			else if (menu == 1)
			{
				Clear();

				Window findGame(0, 0, 60, 6, "Пошук гри");
				findGame.Center();
				findGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				findGame.AddInput(0, 0, 58, 1, "Назва");
				findGame.AddButton(0, 1, 28, 1, 1, "Пошук");
				findGame.AddButton(30, 1, 28, 1, 0, "Назад");

				while (true)
				{
					Clear();

					int callback = findGame.DrawElementsLoop();

					if (callback == 1)
					{
						string name = findGame.GetElementInfo(0);

						vector<string> options;
						vector<int> gameIds;

						for (Game *game : rating.getGames())
						{
							if (game->getName().find(name) != string::npos)
							{
								options.push_back(game->getName());
								gameIds.push_back(game->getID());
							}
						}

						if (options.empty())
						{
							Message message("Гри не знайдено!");
							message.DrawElementsLoop();
							break;
						}

						Window games(0, 0, 60, 14, "Результати пошуку");
						games.Center();
						games.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
						games.AddArray(0, 0, 58, 10, options, true);

						Clear();

						int callback = games.DrawElementsLoop(true);

						if (callback >= 0)
						{
							int id = gameIds[callback];

							Game *game = rating.getGame(id);

							if (game != nullptr)
							{
								reviewsMenu(id);
							}
						}

						break;
					}
					else if (callback == 0 || callback == -1)
					{
						break;
					}
				}
			}
			else if (menu == 2)
			{
				Clear();

				Window findGame(0, 0, 30, 6, "Пошук гри за тегом");
				findGame.Center();
				findGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				findGame.AddInput(0, 0, 28, 1, "Тег");
				findGame.AddButton(0, 1, 13, 1, 1, "Пошук");
				findGame.AddButton(15, 1, 13, 1, 0, "Назад");

				while (true)
				{
					Clear();

					int callback = findGame.DrawElementsLoop();

					if (callback == 1)
					{
						string tag = findGame.GetElementInfo(0);

						vector<string> options;
						vector<int> gameIds;

						for (Game *game : rating.getGames())
						{
							if (game->getTags().find(tag) != string::npos)
							{
								options.push_back(game->getName());
								gameIds.push_back(game->getID());
							}
						}

						if (options.empty())
						{
							Message message("Гри не знайдено!");
							message.DrawElementsLoop();
							break;
						}

						Window games(0, 0, 60, 14, "Результати пошуку");
						games.Center();
						games.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
						games.AddArray(0, 0, 58, 10, options, true);

						Clear();

						int callback = games.DrawElementsLoop(true);

						if (callback >= 0)
						{
							int id = gameIds[callback];

							Game *game = rating.getGame(id);

							if (game != nullptr)
							{
								reviewsMenu(id);
							}
						}

						break;
					}
					else if (callback == 0 || callback == -1)
					{
						break;
					}
				}
			}
			else if (menu == 3)
			{
				Clear();

				vector<string> options;
				vector<int> gameIds;

				for (Game *game : rating.getGames())
				{
					bool exist = false;

					for (Review *review : rating.getReviews())
					{
						if (review->getGame() == game && review->getUser() == currentUser)
						{
							exist = true;
							break;
						}
					}

					if (!exist)
					{
						options.push_back(game->getName());
						gameIds.push_back(game->getID());
					}
				}

				Window games(0, 0, 60, 14, "Вибiр гри");
				games.Center();
				games.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				games.AddArray(0, 0, 58, 10, options, true);

				Clear();

				int callback = games.DrawElementsLoop(true);

				if (callback >= 0)
				{
					Game *game = rating.getGame(gameIds[callback]);

					Window reviewWindow(0, 0, 60, 9, "Вiдгук (" + game->getName() + ")");
					reviewWindow.Center();
					reviewWindow.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
					reviewWindow.AddInput(0, 0, 1, 1, "Рейтинг", 1);
					reviewWindow.AddInput(0, 1, 58, 3, "Вiдгук");
					reviewWindow.AddButton(0, 4, 28, 1, 1, "Додати");
					reviewWindow.AddButton(30, 4, 28, 1, 0, "Назад");

					while (true)
					{
						Clear();

						int callback = reviewWindow.DrawElementsLoop();

						if (callback == 1)
						{
							if (!isdigit(reviewWindow.GetElementInfo(0)[0]))
							{
								Message message("Рейтинг має бути цiлим числом!");
								message.DrawElementsLoop();
								continue;
							}

							int irating = stoi(reviewWindow.GetElementInfo(0));

							if (irating < 0 || irating > 5)
							{
								Message message("Рейтинг має бути вiд 0 до 5!");
								message.DrawElementsLoop();
								continue;
							}

							string text = reviewWindow.GetElementInfo(1);

							if (text.empty())
							{
								Message message("Заповнiть всi поля!");
								message.DrawElementsLoop();
								continue;
							}

							Message message("Вiдгук про гру " + game->getName() + " доданий!");

							rating.addReview(game, currentUser, irating, text);

							message.DrawElementsLoop();

							break;
						}
						else if (callback == 0 || callback == -1)
						{
							break;
						}
					}
				}
				else if (callback == -1)
				{
					return;
				}
			}
			else if (menu == 4)
			{
				Clear();

				vector<string> options;
				vector<Review *> reviews;

				for (Review *review : rating.getReviews())
				{
					if (review->getUser() == currentUser)
					{
						options.push_back(review->getGameName());
						reviews.push_back(review);
					}
				}

				if (reviews.empty())
				{
					Message message("Вiдгукi вiдсутнi!");
					message.DrawElementsLoop();

					return;
				}

				Window myReviews(0, 0, 30, 10, "Мої вiдгуки");
				myReviews.Center();
				myReviews.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				myReviews.AddArray(0, 0, 28, 6, options, true);

				Clear();

				int callback = myReviews.DrawElementsLoop(true);

				if (callback >= 0)
				{
					Review *review = reviews[callback];

					Window reviewWindow(0, 0, 60, 10, "Вiдгук");
					reviewWindow.Center();
					reviewWindow.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
					reviewWindow.AddButton(0, 5, 13, 1, 0, "Назад");
					reviewWindow.AddButton(30, 5, 14, 1, 1, "Редагувати");
					reviewWindow.AddButton(46, 5, 12, 1, 2, "Видалити");
					reviewWindow.AddLabel(0, 0, 58, 1, "Гра: " + review->getGameName());
					reviewWindow.AddLabel(0, 1, 58, 1, "Рейтинг: " + to_string(review->getRating()));
					reviewWindow.AddLabel(0, 2, 58, 3, "Вiдгук: " + review->getText());

					while (true)
					{
						Clear();
						int callback = reviewWindow.DrawElementsLoop();

						if (callback == 1)
						{
							Window editReview(0, 0, 60, 9, "Редагування вiдгуку");
							editReview.Center();
							editReview.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
							editReview.AddInput(0, 0, 58, 1, "Рейтинг");
							editReview.AddInput(0, 1, 58, 3, "Вiдгук");
							editReview.AddButton(0, 4, 28, 1, 1, "Редагувати");
							editReview.AddButton(30, 4, 28, 1, 0, "Назад");

							editReview.SetElementInfo(0, to_string(review->getRating()));
							editReview.SetElementInfo(1, review->getText());

							while (true)
							{
								Clear();

								int callback = editReview.DrawElementsLoop();

								if (callback == 1)
								{
									if (!stoi(editReview.GetElementInfo(0)))
									{
										Message message("Рейтинг має бути цiлим числом!");
										message.DrawElementsLoop();
										continue;
									}

									int irating = stoi(editReview.GetElementInfo(0));

									if (irating < 0 || irating > 5)
									{
										Message message("Рейтинг має бути вiд 0 до 5!");
										message.DrawElementsLoop();
										continue;
									}

									string text = editReview.GetElementInfo(1);

									if (text.empty())
									{
										Message message("Заповнiть всi поля!");
										message.DrawElementsLoop();
										continue;
									}

									Message message("Вiдгук про гру " + review->getGameName() + " вiдредагований!");

									review->setRating(irating);
									review->setText(text);

									rating.saveReviews();

									reviewWindow.SetElementInfo(4, "Рейтинг: " + to_string(review->getRating()));
									reviewWindow.SetElementInfo(5, "Вiдгук: " + review->getText());

									editReview.Draw();

									message.DrawElementsLoop();

									break;
								}
								else if (callback == 0 || callback == -1)
								{
									break;
								}
							}
						}
						else if (callback == 2)
						{
							Message message("Вiдгук про гру " + review->getGameName() + " видалений!");

							rating.removeReview(review->getID());
							rating.saveReviews();

							message.DrawElementsLoop();

							break;
						}
						else if (callback == 0 || callback == -1)
						{
							break;
						}
					}
				}
			}
			else if (menu == 5)
			{
				break;
			}
		}
	}
}

void adminMenu()
{
	Window window(0, 0, 30, 14, "Меню адмiнiстратора");
	window.Center();
	window.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
	window.AddArray(0, 0, 28, 10, {"Додати гру", "Редагувати гру", "Видалити гру", "Пошук гри за тегом", "Список iгор i вiдгукiв", "Експорт iгор i вiдгукiв", "Сгенерувати тестовi данi", "Видалити всi iгри", "Видалити всi вiдгуки", "Вихiд"}, true);

	while (true)
	{
		Clear();

		int callback = window.DrawElementsLoop(true);

		if (callback >= 0)
		{
			int menu = stoi(window.GetElementInfo(0));

			if (menu == 0)
			{
				Window addGame(0, 0, 60, 12, "Додати гру");
				addGame.Center();
				addGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				addGame.AddInput(0, 0, 58, 1, "ID");
				addGame.AddInput(0, 1, 58, 1, "Назва");
				addGame.AddInput(0, 2, 58, 3, "Опис");
				addGame.AddInput(0, 5, 58, 1, "Дата виходу");
				addGame.AddInput(0, 6, 58, 1, "Теги");
				addGame.AddButton(0, 7, 28, 1, 1, "Додати");
				addGame.AddButton(30, 7, 28, 1, 0, "Назад");

				while (true)
				{
					Clear();

					int callback = addGame.DrawElementsLoop();

					if (callback == 1)
					{
						if (!stoi(addGame.GetElementInfo(0)))
						{
							Message message("ID має бути цiлим числом!");
							message.DrawElementsLoop();
							continue;
						}

						int id = stoi(addGame.GetElementInfo(0));

						if (id < 0)
						{
							Message message("ID має бути додатнiм числом!");
							message.DrawElementsLoop();
							continue;
						}

						if (rating.getGame(id) != nullptr)
						{
							Message message("Гра з таким ID вже iснує!");
							message.DrawElementsLoop();
							continue;
						}

						string name = addGame.GetElementInfo(1);
						string description = addGame.GetElementInfo(2);
						string releaseDate = addGame.GetElementInfo(3);
						string tags = addGame.GetElementInfo(4);

						if (name.empty() || description.empty() || releaseDate.empty() || tags.empty())
						{
							Message message("Заповнiть всi поля!");
							message.DrawElementsLoop();
							continue;
						}

						Message message("Гра " + to_string(id) + " (" + name + ") додана!");

						rating.addGame(id, name, description, releaseDate, tags);

						message.DrawElementsLoop();

						break;
					}
					else if (callback == 0 || callback == -1)
					{
						break;
					}
				}
			}
			else if (menu == 1)
			{
				if (rating.getGames().empty())
				{
					Message message("Iгор немає!");
					message.DrawElementsLoop();
					continue;
				}

				Clear();

				vector<string> options;
				vector<int> gameIds;

				for (Game *game : rating.getGames())
				{
					options.push_back(game->getName());
					gameIds.push_back(game->getID());
				}

				Window deleteGame(0, 0, 60, 14, "Редагувати гру");
				deleteGame.Center();
				deleteGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				deleteGame.AddArray(0, 0, 58, 10, options, true);

				Clear();

				int callback = deleteGame.DrawElementsLoop(true);

				if (callback >= 0)
				{
					int id = gameIds[callback];

					Game *game = rating.getGame(id);

					if (game != nullptr)
					{
						Window editGame(0, 0, 60, 11, "Редагування гри");
						editGame.Center();
						editGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
						editGame.AddInput(0, 0, 58, 1, "Назва");
						editGame.AddInput(0, 1, 58, 3, "Опис");
						editGame.AddInput(0, 4, 58, 1, "Дата виходу");
						editGame.AddInput(0, 5, 58, 1, "Теги");
						editGame.AddButton(0, 6, 28, 1, 1, "Редагувати");
						editGame.AddButton(30, 6, 28, 1, 0, "Назад");

						editGame.SetElementInfo(0, game->getName());
						editGame.SetElementInfo(1, game->getDescription());
						editGame.SetElementInfo(2, game->getReleaseDate());
						editGame.SetElementInfo(3, game->getTags());

						Clear();

						int callback = editGame.DrawElementsLoop();

						if (callback == 1)
						{
							string name = editGame.GetElementInfo(0);
							string description = editGame.GetElementInfo(1);
							string releaseDate = editGame.GetElementInfo(2);
							string tags = editGame.GetElementInfo(3);

							if (name.empty() || description.empty() || releaseDate.empty() || tags.empty())
							{
								Message message("Заповнiть всi поля!");
								message.DrawElementsLoop();
								continue;
							}

							Message message("Гра " + to_string(game->getID()) + " (" + game->getName() + ") вiдредагована!");

							game->setName(name);
							game->setDescription(description);
							game->setReleaseDate(releaseDate);
							game->setTags(tags);

							message.DrawElementsLoop();
						}
					}
				}
			}
			else if (menu == 2)
			{
				if (rating.getGames().empty())
				{
					Message message("Iгор немає!");
					message.DrawElementsLoop();
					continue;
				}

				Clear();

				vector<string> options;
				vector<int> gameIds;

				for (Game *game : rating.getGames())
				{
					options.push_back(game->getName());
					gameIds.push_back(game->getID());
				}

				Window deleteGame(0, 0, 60, 14, "Видалити гру");
				deleteGame.Center();
				deleteGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				deleteGame.AddArray(0, 0, 58, 10, options, true);

				Clear();

				int callback = deleteGame.DrawElementsLoop(true);

				if (callback >= 0)
				{
					int id = gameIds[callback];

					Game *game = rating.getGame(id);

					if (game != nullptr)
					{
						Message message("Гра " + to_string(game->getID()) + " (" + game->getName() + ") видалена!");

						for (Review *review : rating.getReviews())
						{
							if (review->getGame() == game)
							{
								rating.removeReview(review->getID());
							}
						}

						rating.removeGame(id);

						message.DrawElementsLoop();
					}
				}
			}
			else if (menu == 3)
			{
				if (rating.getGames().empty())
				{
					Message message("Iгор немає!");
					message.DrawElementsLoop();
					continue;
				}

				Clear();

				Window findGame(0, 0, 30, 6, "Пошук гри за тегом");
				findGame.Center();
				findGame.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				findGame.AddInput(0, 0, 28, 1, "Тег");
				findGame.AddButton(0, 1, 13, 1, 1, "Пошук");
				findGame.AddButton(15, 1, 13, 1, 0, "Назад");

				while (true)
				{
					Clear();

					int callback = findGame.DrawElementsLoop();

					if (callback == 1)
					{
						string tag = findGame.GetElementInfo(0);

						vector<string> options;
						vector<int> gameIds;

						for (Game *game : rating.getGames())
						{
							if (game->getTags().find(tag) != string::npos)
							{
								options.push_back(game->getName());
								gameIds.push_back(game->getID());
							}
						}

						if (options.empty())
						{
							Message message("Гри не знайдено!");
							message.DrawElementsLoop();
							break;
						}

						Window games(0, 0, 60, 14, "Результати пошуку");
						games.Center();
						games.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
						games.AddArray(0, 0, 58, 10, options, true);

						Clear();

						int callback = games.DrawElementsLoop(true);

						if (callback >= 0)
						{
							int id = gameIds[callback];

							Game *game = rating.getGame(id);

							if (game != nullptr)
							{
								reviewsMenu(id);
							}
						}

						break;
					}
					else if (callback == 0 || callback == -1)
					{
						break;
					}
				}
			}
			else if (menu == 4)
			{
				if (rating.getGames().empty())
				{
					Message message("Iгор немає!");
					message.DrawElementsLoop();
					continue;
				}

				Clear();

				reviewsMenu();
			}
			else if (menu == 5)
			{
				if (rating.getGames().empty())
				{
					Message message("Iгор немає!");
					message.DrawElementsLoop();
					continue;
				}

				ofstream file("export.html");

				file << "<!DOCTYPE html>\n";
				file << "<html>\n";
				file << "<head>\n";
				file << "<title>Export</title>\n";
				file << "</head>\n";
				file << "<body>\n";
				file << "<table border=\"1\">\n";
				file << "<tr>\n";
				file << "<th>ID</th>\n";
				file << "<th>Назва</th>\n";
				file << "<th>Опис</th>\n";
				file << "<th>Дата виходу</th>\n";
				file << "<th>Теги</th>\n";
				file << "</tr>\n";

				for (Game *game : rating.getGames())
				{
					file << "<tr>\n";
					file << "<td>" << game->getID() << "</td>\n";
					file << "<td>" << game->getName() << "</td>\n";
					file << "<td>" << game->getDescription() << "</td>\n";
					file << "<td>" << game->getReleaseDate() << "</td>\n";
					file << "<td>" << game->getTags() << "</td>\n";
					file << "</tr>\n";
				}

				file << "</table>\n";

				if (!rating.getReviews().empty())
				{

					file << "<table border=\"1\">\n";
					file << "<tr>\n";
					file << "<th>ID</th>\n";
					file << "<th>Гра</th>\n";
					file << "<th>Користувач</th>\n";
					file << "<th>Рейтинг</th>\n";
					file << "<th>Вiдгук</th>\n";
					file << "</tr>\n";

					for (Review *review : rating.getReviews())
					{
						file << "<tr>\n";
						file << "<td>" << review->getID() << "</td>\n";
						file << "<td>" << review->getGameName() << "</td>\n";
						file << "<td>" << review->getUsername() << "</td>\n";
						file << "<td>" << review->getRating() << "</td>\n";
						file << "<td>" << review->getText() << "</td>\n";
						file << "</tr>\n";
					}

					file << "</table>\n";
				}
				file << "</body>\n";
				file << "</html>\n";

				file.close();

				Message message("Данi експортованi у файл export.html!");
				message.DrawElementsLoop();

				system("export.html");
			}
			else if (menu == 6)
			{
				rating.generateTestData();

				Message message("Тестовi данi згенерованi!");
				message.DrawElementsLoop();
			}
			else if (menu == 7)
			{
				if (rating.getGames().empty())
				{
					Message message("Iгор немає!");
					message.DrawElementsLoop();
					continue;
				}

				Message message("Всi iгри видаленi!");
				message.DrawElementsLoop();

				rating.clearReviews();
				rating.clearGames();
			}
			else if (menu == 8)
			{
				if (rating.getReviews().empty())
				{
					Message message("Вiдгукi вiдсутнi!");
					message.DrawElementsLoop();
					continue;
				}

				Message message("Всi вiдгуки видаленi!");
				message.DrawElementsLoop();

				rating.clearReviews();
			}
			else if (menu == 9)
			{
				break;
			}
		}
	}
}

int main()
{
	Clear();

	ShowCaret(false);

	Window window(0, 0, 30, 7, "Рейтинг iгор");
	window.Center();
	window.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
	window.AddArray(0, 0, 28, 3, {"Увiйти", "Реєстрацiя", "Вихiд"}, true);

	while (true)
	{
		currentUser = nullptr;

		int callback = window.DrawElementsLoop(true);

		if (callback >= 0)
		{
			int menu = stoi(window.GetElementInfo(0));

			if (menu == 0)
			{
				Clear();
				Window login(0, 0, 30, 8, "Увiйти");
				login.Center();
				login.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				login.AddInput(0, 0, 28, 1, "Логiн");
				login.AddInput(0, 1, 28, 1, "Пароль", -1, true);
				login.AddButton(0, 2, 13, 1, 1, "Увiйти");
				login.AddButton(15, 2, 13, 1, 0, "Назад");
				login.AddLabel(0, 3, 28, 1, "Натиснiть Enter для входу");
				int callback = login.DrawElementsLoop();

				if (callback == 1)
				{
					string username = login.GetElementInfo(0);
					string password = login.GetElementInfo(1);

					User *user = rating.getUser(username, password);

					if (user != nullptr)
					{
						currentUser = user;
						Message message("Вiтаємо, " + currentUser->getUsername() + " (" + (currentUser->isAdmin() ? "адмiн" : "клiєнт") + ")!");
						message.DrawElementsLoop();

						if (currentUser->isAdmin())
						{
							adminMenu();
						}
						else
						{
							clientMenu();
						}
					}
					else
					{
						Message message("Користувача з таким логiном та паролем не знайдено!");
						message.DrawElementsLoop();
					}
				}

				Clear();
			}
			else if (menu == 1)
			{
				Clear();
				Window reg(0, 0, 30, 8, "Зареєструватися");
				reg.Center();
				reg.SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
				reg.AddInput(0, 0, 28, 1, "Логiн", 32);
				reg.AddInput(0, 1, 28, 1, "Пароль", 20, true);
				reg.AddCheckbox(0, 2, 28, 1, "Адмiн?");
				reg.AddButton(0, 3, 13, 1, 1, "Реєстрацiя");
				reg.AddButton(15, 3, 13, 1, 0, "Назад");
				int callback = reg.DrawElementsLoop();

				if (callback == 1)
				{
					string username = reg.GetElementInfo(0);
					string password = reg.GetElementInfo(1);
					bool isAdmin = reg.GetElementInfo(2) == "1";

					Message message("Користувач успiшно зареєстрований!");
					message.DrawElementsLoop();

					rating.addUser(username, password, isAdmin);
				}

				Clear();
			}
			else if (menu == 2)
			{
				break;
			}
		}
	}
}