#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <vector>
#include "fun_console.h"

enum ElementType
{
	Input,
	Button,
	Array,
	Checkbox,
	Label
};

struct ElementData
{
	ElementType type;
	std::string content;
	int x, y, w, h;
	int callback = -1;
	int maxLength = -1;
	bool hideText = false;
	std::string inputText = "";
	std::vector<std::string> arrayOptions = {};
	int selectedOption = 0;
	bool breakOnSelect = false;
	bool checked = false;
};

class Window
{
private:
	int x, y, width, height;
	std::string title;
	int borderColor, backgroundColor, textColor, selectionColor;
	std::vector<ElementData> elements;
	int activeElementIndex;
	char borders[8];

public:
	Window(int posX, int posY, int w, int h, const std::string& t);

	void AddInput(int x, int y, int w, int h, const std::string& content, int maxLength = -1, bool hideText = false);
	void AddButton(int x, int y, int w, int h, int callback, const std::string& content);
	void AddArray(int x, int y, int w, int h, const std::vector<std::string>& options, bool breakOnSelect = false);
	void AddCheckbox(int x, int y, int w, int h, const std::string &content, bool checked = false);
	void AddLabel(int x, int y, int w, int h, const std::string &content);
	void RemoveElement(int index);

	Window& SetPos(int posX, int posY);
	Window& SetX(int posX);
	Window& SetY(int posY);
	Window& Center();
	Window& CenterX();
	Window& CenterY();
	Window& SetSize(int w, int h);
	Window& SetTitle(const std::string& t);
	Window& SetBackgroundColor(int color);
	Window& SetBorderColor(int color);
	Window& SetTextColor(int color);
	Window& SetSelectionColor(int color);

	std::string GetElementInfo(int index);
	void SetElementInfo(int index, const std::string &info);
	void SetActiveElement(int index);
	int GetActiveElement();
	void MoveActiveElement(int direction);
	void NextElement();
	void PrevElement();
	void ActivateElement();
	void ActivateButton(int index);
	void ActivateInput(int index);
	void ActivateArray(int index);
	void ActivateCheckbox(int index);
	void DrawInput(int index, bool active, bool editing = false);
	void HandleInput(int index);
	void DrawArray(int index, int selectedOption, int firstVisible = 0);
	void HandleArray(int index);
	void DrawCheckbox(int index, bool active);
	void HandleCheckbox(int index);
	void DrawLabel(int index);
	void ClearElementArea(int index);
	int DrawElementsLoop(bool activate = false, bool dontClear = false);
	void Draw();
	void DrawBackground();
	void DrawBackground(int index, bool active = false);
	void DrawBorder();
	void DrawTitle();
	void DrawElements();
	void Draw(int x, int y, const std::string& text, int textColor, int backgroundColor);
	void Draw(int x, int y, const std::string& text);
	void DrawElement(int index, bool active = false);

	int selectedArrayElement = -1;
	int callback = -1;
};

class Message : public Window
	{
	public:
		Message(const std::string& t);
};

#endif