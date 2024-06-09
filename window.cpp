#include "window.h"
#include <conio.h>

Window::Window(int posX, int posY, int w, int h, const std::string &t) : x(posX), y(posY), width(w), height(h), title(t),
                                                                         borderColor(White), backgroundColor(Black), textColor(White), selectionColor(Green), activeElementIndex(-1)
{
    SetSize(width, height);
    SetTitle(title);
    borders[0] = 201;
    borders[1] = 205;
    borders[2] = 187;
    borders[3] = 186;
    borders[4] = 200;
    borders[5] = 188;
    borders[6] = 204;
    borders[7] = 185;
}

void Window::AddInput(int x, int y, int w, int h, const std::string &content, int maxLength, bool hideText)
{
    ElementData element = {Input, content + ": ", x, y, w, h, -1, maxLength, hideText, ""};
    elements.push_back(element);
}

void Window::AddButton(int x, int y, int w, int h, int callback, const std::string &content)
{
    ElementData element = {Button, content, x, y, w, h, callback};
    elements.push_back(element);
}

void Window::AddArray(int x, int y, int w, int h, const std::vector<std::string> &options, bool breakOnSelect)
{
    ElementData element = {Array, "", x, y, w, h, -1, -1, false, "", options, 0, breakOnSelect};
    elements.push_back(element);
}

void Window::AddCheckbox(int x, int y, int w, int h, const std::string &content, bool checked)
{
    ElementData element = {Checkbox, content, x, y, w, h, -1, -1, false, "", {}, 0, 0, checked};
    elements.push_back(element);
}

void Window::AddLabel(int x, int y, int w, int h, const std::string &content)
{
    ElementData element = {Label, content, x, y, w, h};
    elements.push_back(element);
}

void Window::RemoveElement(int index)
{
    if (index >= 0 && index < elements.size())
    {
        elements.erase(elements.begin() + index);
        if (activeElementIndex == index)
            activeElementIndex = -1;
        else if (activeElementIndex > index)
            activeElementIndex--;
    }
}

Window &Window::SetPos(int posX, int posY)
{
    x = posX;
    y = posY;

    return *this;
}

Window &Window::SetX(int posX)
{
    x = posX;

    return *this;
}

Window &Window::SetY(int posY)
{
    y = posY;

    return *this;
}

Window &Window::Center()
{
    x = (GetCols() - width) / 2;
    y = (GetRows() - height) / 2;

    return *this;
}

Window &Window::CenterX()
{
    x = (GetCols() - width) / 2;

    return *this;
}

Window &Window::CenterY()
{
    y = (GetRows() - height) / 2;

    return *this;
}

Window &Window::SetSize(int w, int h)
{
    width = w;
    height = h;

    return *this;
}

Window &Window::SetTitle(const std::string &t)
{
    title = t;

    return *this;
}

Window &Window::SetBackgroundColor(int color)
{
    backgroundColor = color;

    return *this;
}

Window &Window::SetBorderColor(int color)
{
    borderColor = color;

    return *this;
}

Window &Window::SetTextColor(int color)
{
    textColor = color;

    return *this;
}

Window &Window::SetSelectionColor(int color)
{
    selectionColor = color;

    return *this;
}

std::string Window::GetElementInfo(int index)
{
    if (index >= 0 && index < elements.size())
    {
        ElementType type = elements[index].type;

        if (type == Input)
        {
            return elements[index].inputText;
        }
        else if (type == Array)
        {
            return std::to_string(elements[index].selectedOption);
        }
        else if (type == Checkbox)
        {
            return elements[index].checked ? "1" : "0";
        }
        else if (type == Label)
        {
            return elements[index].content;
        }
    }
    return "";
}

void Window::SetElementInfo(int index, const std::string &info)
{
    if (index >= 0 && index < elements.size())
    {
        ElementType type = elements[index].type;

        if (type == Input)
        {
            elements[index].inputText = info;
        }
        else if (type == Array)
        {
            elements[index].selectedOption = std::stoi(info);
        }
        else if (type == Checkbox)
        {
            elements[index].checked = info == "1";
        }
        else if (type == Label)
        {
            elements[index].content = info;
        }

        DrawElement(index, index == activeElementIndex);
    }
}

void Window::SetActiveElement(int index)
{
    if (index >= 0 && index < elements.size())
    {
        if (activeElementIndex != -1)
            DrawElement(activeElementIndex);
        activeElementIndex = index;
        DrawElement(activeElementIndex, true);
    }
}

int Window::GetActiveElement()
{
    return activeElementIndex;
}

void Window::MoveActiveElement(int direction)
{
    int newIndex = activeElementIndex + direction;

    if (newIndex >= 0 && newIndex < elements.size())
    {
        while (elements[newIndex].type == Label) {
            if (newIndex + direction < 0 || newIndex + direction >= elements.size()) {
                newIndex = 0;
                break;
            }

            newIndex += direction;
        }

        if (newIndex >= 0 && newIndex < elements.size())
        {
            SetActiveElement(newIndex);
        }
    } else if (newIndex < 0) {
        SetActiveElement(elements.size() - 1);

        while (elements[activeElementIndex].type == Label) {
            MoveActiveElement(-1);
        }
    } else if (newIndex >= elements.size()) {
        SetActiveElement(0);
    }
}

void Window::NextElement()
{
    MoveActiveElement(1);
}

void Window::PrevElement()
{
    MoveActiveElement(-1);
}

void Window::ActivateElement()
{
    if (activeElementIndex >= 0 && activeElementIndex < elements.size())
    {
        ElementType type = elements[activeElementIndex].type;
        switch (type)
        {
        case Input:
            ActivateInput(activeElementIndex);
            break;
        case Button:
            ActivateButton(activeElementIndex);
            break;
        case Array:
            ActivateArray(activeElementIndex);
            break;
        case Checkbox:
            ActivateCheckbox(activeElementIndex);
            break;
        }
    }
}

void Window::ActivateButton(int index)
{
    if (index >= 0 && index < elements.size())
    {
        if (elements[index].callback != -1)
        {
            callback = elements[index].callback;
        }
    }
}

void Window::ActivateInput(int index)
{
    if (index >= 0 && index < elements.size())
    {
        HandleInput(index);
    }
}

void Window::ActivateArray(int index)
{
    if (index >= 0 && index < elements.size())
    {
        HandleArray(index);
    }
}

void Window::ActivateCheckbox(int index)
{
    if (index >= 0 && index < elements.size())
    {
        HandleCheckbox(index);
    }
}

void Window::DrawInput(int index, bool active, bool editing)
{
    if (index >= 0 && index < elements.size())
    {
        int x = elements[index].x + 1;
        int y = elements[index].y + 3;
        std::string content = elements[index].content;
        int elementWidth = elements[index].w;
        int elementHeight = elements[index].h;
        std::string inputText = elements[index].inputText;

        if (elements[index].hideText) {
            inputText = std::string(inputText.length(), '*');
        }

        int inputTextLength = inputText.length();
        int contentLength = content.length();
        int requiredSpaces = std::max(0, elementWidth * elementHeight - inputTextLength - contentLength);
        inputText += std::string(requiredSpaces, ' ');

        std::vector<std::string> lines;
        int currPos = 0;
        while (currPos < inputText.length())
        {
            int nextPos = currPos == 0 ? elementWidth - content.length() : elementWidth;
            lines.push_back(inputText.substr(currPos, nextPos));
            currPos += nextPos;
        }

        int lineCount = std::min((int)(lines.size()), elementHeight);
        for (int i = 0; i < lineCount; i++)
        {
            Draw(x, y + i, i > 0 ? lines[i] : content + lines[i], editing ? White : active ? Black : textColor, editing ? Cyan : active ? selectionColor : backgroundColor);
        }
    }
}

void Window::HandleInput(int index)
{
    int maxLength = elements[index].maxLength;
    int maxWidth = (elements[index].w * elements[index].h) - elements[index].content.length();
    std::string &inputText = elements[index].inputText;

    DrawInput(index, false, true);

    int key = _getch();

    while (key != 13)
    {
        if (key == 8 && !inputText.empty())
        {
            inputText.pop_back();
            DrawInput(index, false, true);
        }
        else if (((key >= 32 && key <= 126) || (key >= 128 && key <= 175) || (key >= 224 && key <= 247)) && (maxLength == -1 || inputText.length() < maxLength) && (inputText.length() < maxWidth))
        {
            inputText.push_back((char)key);
            DrawInput(index, false, true);
        }
        key = _getch();
    }

    DrawInput(index, true);
}

void Window::DrawArray(int index, int selectedOption, int firstVisible)
{
    if (index >= 0 && index < elements.size())
    {
        DrawBackground(index);

        int x = elements[index].x + 1;
        int y = elements[index].y + 3;
        std::vector<std::string> &arrayOptions = elements[index].arrayOptions;
        int elementWidth = elements[index].w;
        int elementHeight = elements[index].h;

        int visibleItemCount = elementHeight;

        firstVisible = std::max(0, std::min(firstVisible, static_cast<int>(arrayOptions.size()) - visibleItemCount));

        for (int i = 0; i < visibleItemCount; ++i)
        {
            int arrayIndex = firstVisible + i;
            if (arrayIndex >= arrayOptions.size())
                break;

            std::string optionText = arrayOptions[arrayIndex];
            Draw(x, y + i, optionText.substr(0, elementWidth), arrayIndex == selectedOption ? Black : textColor, arrayIndex == selectedOption ? White : backgroundColor);

            int textLength = optionText.length();
            if (textLength < elementWidth)
            {
                int remainingSpaces = elementWidth - textLength;
                std::string spaces(remainingSpaces, ' ');
                Draw(x + textLength, y + i, spaces, arrayIndex == selectedOption ? Black : textColor, arrayIndex == selectedOption ? White : backgroundColor);
            }
        }

        int lastLineLength = arrayOptions.size() % elementWidth;
        int lastLineY = y + arrayOptions.size() / elementWidth;
        int lastLineX = x + (lastLineLength == 0 ? elementWidth - 1 : lastLineLength - 1);

        GotoXY(lastLineX, lastLineY);
    }
}

void Window::HandleArray(int index)
{
    if (index >= 0 && index < elements.size())
    {
        int firstVisible = 0;
        int &selectedOption = elements[index].selectedOption;
        int optionCount = elements[index].arrayOptions.size();
        int height = elements[index].h;

        while (true)
        {
            int key = _getch();
            if (key == 224)
            {
                key = _getch();
                if (key == 72)
                {
                    selectedOption = (selectedOption - 1 + optionCount) % optionCount;

                    if (selectedOption < firstVisible)
                        firstVisible = selectedOption;
                    else if (selectedOption >= firstVisible + height)
                        firstVisible = selectedOption - height + 1;

                    DrawArray(index, selectedOption, firstVisible);
                }
                else if (key == 80)
                {
                    selectedOption = (selectedOption + 1) % optionCount;

                    if (selectedOption >= firstVisible + height)
                        firstVisible = selectedOption - height + 1;
                    else if (selectedOption < firstVisible)
                        firstVisible = selectedOption;

                    DrawArray(index, selectedOption, firstVisible);
                }
            }
            else if (key == 13)
            {
                if (elements[index].breakOnSelect)
                {
                    selectedArrayElement = selectedOption;
                }

                break;
            }
            else if (key == 27)
            {
                selectedArrayElement = -1;
                break;
            }
        }
    }
}

void Window::DrawCheckbox(int index, bool active)
{
    if (index >= 0 && index < elements.size())
    {
        int x = elements[index].x + 1;
        int y = elements[index].y + 3;
        std::string content = elements[index].content;
        int elementWidth = elements[index].w;
        int elementHeight = elements[index].h;
        bool checked = elements[index].checked;

        std::string checkbox = checked ? "[x]" : "[ ]";
        Draw(x, y, content, active ? Black : textColor, active ? selectionColor : backgroundColor);
        Draw(x + content.length(), y, std::string(elementWidth - 3 - content.length(), ' '), active ? Black : textColor, active ? selectionColor : backgroundColor);
        Draw(x + elementWidth - 3, y, checkbox, active ? Black : textColor, active ? selectionColor : backgroundColor);
    }
}

void Window::HandleCheckbox(int index)
{
    if (index >= 0 && index < elements.size())
    {
        elements[index].checked = !elements[index].checked;
        DrawCheckbox(index, true);
    }
}

void Window::DrawLabel(int index)
{
    if (index >= 0 && index < elements.size())
    {
        int x = elements[index].x + 1;
        int y = elements[index].y + 3;
        std::string content = elements[index].content;
        int elementWidth = elements[index].w;
        int elementHeight = elements[index].h;

        std::vector<std::string> lines;

        int currPos = 0;

        while (currPos < content.length())
        {
            int nextPos = currPos == 0 ? elementWidth : elementWidth;
            lines.push_back(content.substr(currPos, nextPos));
            currPos += nextPos;
        }

        int lineCount = std::min((int)(lines.size()), elementHeight);

        for (int i = 0; i < lineCount; i++)
        {
            Draw(x, y + i, lines[i], textColor, backgroundColor);
        }

        for (int i = lineCount; i < elementHeight; i++)
        {
            Draw(x, y + i, std::string(elementWidth, ' '), textColor, backgroundColor);
        }
    }
}

void Window::ClearElementArea(int index)
{
    if (index >= 0 && index < elements.size())
    {
        int x = elements[index].x + 1;
        int y = elements[index].y + 3;
        int elementWidth = elements[index].w;
        int elementHeight = elements[index].h;
        std::string elementContent = elements[index].content;

        for (int i = 0; i < elementHeight; i++)
        {
            if (i > 0)
                Draw(x, y + i, std::string(elementWidth, ' '));
            else
                Draw(x + elementContent.length(), y, std::string(elementWidth, ' '));
        }
    }
}

int Window::DrawElementsLoop(bool activate, bool dontClear)
{
    selectedArrayElement = -1;
	callback = -1;

    Draw();

    if (!dontClear)
        SetActiveElement(0);

    while (true)
    {
        if (activate)
        {
            ActivateElement();

            if (callback != -1)
            {
                return callback;
            }
            else if (selectedArrayElement == -1)
            {
                return -1;
            }
            else if (selectedArrayElement >= 0)
            {
                return selectedArrayElement;
            }

            activate = false;
        }
        else
        {
            int key = _getch();
            if (key == 224)
            {
                key = _getch();
                if (key == 72)
                {
                    PrevElement();
                }
                else if (key == 80)
                {
                    NextElement();
                }
            }
            else if (key == 13)
            {
                ActivateElement();
                if (callback != -1)
                {
                    return callback;
                }
                else if (selectedArrayElement >= 0)
                {
                    return selectedArrayElement;
                }
            }
            else if (key == 27)
            {
                return -1;
            }
        }
    }

    return 0;
}

void Window::Draw()
{
    DrawBackground();
    DrawBorder();
    DrawElements();
}

void Window::DrawBackground()
{
    SetColor(textColor, backgroundColor);
    for (int i = 1; i < height - 1; i++)
    {
        GotoXY(x + 1, y + i);
        for (int j = 0; j < width - 2; j++)
        {
            std::cout << " ";
        }
    }
    SetColor(White, Black);
}

void Window::DrawBackground(int index, bool active)
{
    int x = elements[index].x;
    int y = elements[index].y;
    int w = elements[index].w;
    int h = elements[index].h;

    SetColor(textColor, active ? selectionColor : backgroundColor);
    for (int i = 0; i < h; i++)
    {
        GotoXY(Window::x + x + 1, Window::y + y + 3 + i);
        for (int j = 0; j < w; j++)
        {
            std::cout << " ";
        }
    }
    SetColor(White, Black);
}

void Window::DrawBorder()
{
    SetColor(borderColor, backgroundColor);
    GotoXY(x, y);
    std::cout << borders[0];
    for (int j = 0; j < width - 2; j++)
        std::cout << borders[1];
    std::cout << borders[2];
    for (int i = 1; i < height - 1; i++)
    {
        GotoXY(x, y + i);
        std::cout << borders[3];
        GotoXY(x + width - 1, y + i);
        std::cout << borders[3];
    }
    GotoXY(x, y + height - 1);
    std::cout << borders[4];
    for (int j = 0; j < width - 2; j++)
        std::cout << borders[1];
    std::cout << borders[5];

    if (title != "")
    {
        GotoXY(x, y + 2);
        std::cout << borders[6];
        for (int j = 0; j < width - 2; j++)
            std::cout << borders[1];
        std::cout << borders[7];
        DrawTitle();
    }
}

void Window::DrawTitle()
{
    int titleX = (width - title.length()) / 2;
    Draw(titleX, 1, title);
}

void Window::DrawElements()
{
    for (size_t i = 0; i < elements.size(); ++i)
    {
        DrawElement(i, i == activeElementIndex);
    }
}

void Window::Draw(int x, int y, const std::string &text, int textColor, int backgroundColor)
{
    GotoXY(this->x + x, this->y + y);
    SetColor(textColor, backgroundColor);
    std::cout << text;
    SetColor(White, Black);
}

void Window::Draw(int x, int y, const std::string &text)
{
    Draw(x, y, text, textColor, backgroundColor);
}

void Window::DrawElement(int index, bool active)
{
    if (index >= 0 && index < elements.size())
    {
        int y = elements[index].y + 3;

        ElementType type = elements[index].type;

        int contentWidth = elements[index].content.length();
        int padding = std::max(0, (elements[index].w - contentWidth) / 2);
        std::string paddedContent = std::string(padding, ' ') + elements[index].content + std::string(padding, ' ');

        if (paddedContent.size() < elements[index].w)
        {
            paddedContent += " ";
        }

        switch (type)
        {
        case Input:
            DrawInput(index, active);
            break;
        case Button:
            Draw(elements[index].x + 1, y, paddedContent, textColor, active ? selectionColor : Cyan);
            break;
        case Array:
            DrawArray(index, elements[index].selectedOption);
            break;
        case Checkbox:
            DrawCheckbox(index, active);
            break;
        case Label:
            DrawLabel(index);
            break;
        }
    }
}

Message::Message(const std::string& t) : Window(0, 2, 0, 0, t)
{
    SetSize(t.length() + 4, 5);
    CenterX();
    SetBackgroundColor(Blue).SetBorderColor(LightBlue).SetSelectionColor(Green).SetTextColor(White);
    AddButton(0, 0, t.length() + 2, 1, 1, "OK");
}