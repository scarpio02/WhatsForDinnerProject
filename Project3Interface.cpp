#include <SFML/Graphics.hpp>
#include "recipeClass.cpp"

int main()
{
    // Initialize recipeBook
    recipeBook book;
    std::vector<recipe> recipes;

    // Set up window and font
    sf::RenderWindow window(sf::VideoMode(1200, 900), "\"What's for Dinner?\" by the Kitchen Koders!");
    sf::RectangleShape rectangle(sf::Vector2f(1200.f, 900.f));
    rectangle.setFillColor(sf::Color::White);
    sf::Font font;
    font.loadFromFile("SourceCodePro-Regular.ttf");
    
    // Create title
    sf::Text title;
    title.setFont(font);
    title.setString("What's for Dinner?");
    title.setCharacterSize(28);
    title.setFillColor(sf::Color::Blue);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setPosition(400, 0);

    //Create instructions for change pages of lists and go to previous screen
    sf::Text userInstructions;
    userInstructions.setFont(font);
    userInstructions.setString("\tPress Esc to go to previous page.\n\tUse Left/Right arrow keys to change pages of list.");
    userInstructions.setCharacterSize(22);
    userInstructions.setFillColor(sf::Color::Red);
    userInstructions.setStyle(sf::Text::Bold);
    userInstructions.setPosition(0, 814);

    // Create prompt for number of ingredients
    sf::Text numIngredientsPrompt;
    numIngredientsPrompt.setFont(font);
    numIngredientsPrompt.setString("\tEnter the number of ingredients (1-9): ");
    numIngredientsPrompt.setCharacterSize(22);
    numIngredientsPrompt.setFillColor(sf::Color::Blue);
    numIngredientsPrompt.setStyle(sf::Text::Bold);
    numIngredientsPrompt.setPosition(0, 36);

    // Create prompts for ingredients
    std::vector<sf::Text> ingredientsPrompts;
    for (int i = 0; i < 9; i++)
    {
        sf::Text temp;
        temp.setFont(font);
        std::string tempString = "\tEnter ingredient ";
        tempString += std::to_string(i + 1);
        tempString += ": ";
        temp.setString(tempString);
        temp.setCharacterSize(22);
        temp.setFillColor(sf::Color::Blue);
        temp.setStyle(sf::Text::Bold);
        temp.setPosition(0, 36 * (i + 3));
        ingredientsPrompts.push_back(temp);
    }

    // Create headers for table displaying recipes
    sf::Text recipesHeader, numIngredientsHeader;
    recipesHeader.setFont(font);
    recipesHeader.setString("\tRecipes");
    recipesHeader.setCharacterSize(22);
    recipesHeader.setFillColor(sf::Color::Blue);
    recipesHeader.setStyle(sf::Text::Bold);

    numIngredientsHeader.setFont(font);
    numIngredientsHeader.setString("# Ingredients");
    numIngredientsHeader.setCharacterSize(22);
    numIngredientsHeader.setFillColor(sf::Color::Blue);
    numIngredientsHeader.setStyle(sf::Text::Bold);
    numIngredientsHeader.setPosition(960, 0);

    // Create prompt for user to choose a sorting method
    sf::Text sortPrompt;
    sortPrompt.setFont(font);
    sortPrompt.setString("\tSort recipes by:\n\t(1) Name\n\t(2) # Ingredients");
    sortPrompt.setCharacterSize(22);
    sortPrompt.setFillColor(sf::Color::Blue);
    sortPrompt.setStyle(sf::Text::Bold);
    sortPrompt.setPosition(0, 470);

    sf::Text userSortInput;
    userSortInput.setFont(font);
    userSortInput.setCharacterSize(22);
    userSortInput.setFillColor(sf::Color::Black);
    userSortInput.setStyle(sf::Text::Bold);
    userSortInput.setPosition(320, 470);


    // Create prompt for user to choose a recipe
    sf::Text recipePrompt;
    recipePrompt.setFont(font);
    recipePrompt.setString("\tEnter the recipe number: ");
    recipePrompt.setCharacterSize(22);
    recipePrompt.setFillColor(sf::Color::Blue);
    recipePrompt.setStyle(sf::Text::Bold);
    recipePrompt.setPosition(0, 764);

    // Create lines for table displaying recipes
    sf::RectangleShape horizontalLine(sf::Vector2f(1100.f, 5.f));
    horizontalLine.setPosition(50, 24);
    horizontalLine.setFillColor(sf::Color::Blue);
    sf::RectangleShape verticalLine(sf::Vector2f(5.f, 745.f));
    verticalLine.setPosition(940, 0);
    verticalLine.setFillColor(sf::Color::Blue);
    
    // Set up user input variables
    std::string userNumInput, userStringInput, userBinaryInput;
    std::vector<std::string> ingredients;

    sf::Text currNumIngredients;
    currNumIngredients.setFont(font);
    currNumIngredients.setCharacterSize(22);
    currNumIngredients.setFillColor(sf::Color::Black);
    currNumIngredients.setStyle(sf::Text::Bold);
    currNumIngredients.setPosition(600, 36);
    int userNumIngredients = 0;

    sf::Text currUserIngredient;
    currUserIngredient.setFont(font);
    currUserIngredient.setCharacterSize(22);
    currUserIngredient.setFillColor(sf::Color::Black);
    currUserIngredient.setStyle(sf::Text::Bold);
    currUserIngredient.setPosition(350, 36*3);

    std::vector<sf::Text> userIngredients;
    for (int i = 0; i < 9; i++)
    {
        sf::Text temp;
        temp.setFont(font);
        temp.setCharacterSize(22);
        temp.setFillColor(sf::Color::Black);
        temp.setStyle(sf::Text::Bold);
        temp.setPosition(350, 36 * (i + 3));
        userIngredients.push_back(temp);
    }

    sf::Text userNumRecipe;
    userNumRecipe.setFont(font);
    userNumRecipe.setCharacterSize(22);
    userNumRecipe.setFillColor(sf::Color::Black);
    userNumRecipe.setStyle(sf::Text::Bold);
    userNumRecipe.setPosition(400, 764);
    int recipeNum = 0;

    // bools for window state
    bool inputNumIngredients = true;
    bool inputIngedientsNames = false;
    bool inputSortMethod = false;
    bool displayRecipes = false;
    bool displayRecipeInfo = false;
    bool sortByNumIngredients = false;

    // Variables for displaying table of recipes
    int totalPages = 0;
    int pageIndex = 0;
    std::vector<sf::Text> listedRecipes;
    std::vector<sf::Text> listedNumIngredients;

    // Variables for displaying ingredients of recipe
    int ingredientsTotalPages = 0;
    int ingredientsPageIndex = 0;
    std::vector<sf::Text> recipeIngredients;

    // Variables for displaying recipe info
    sf::Text titleHeader, ingredientsHeader, instructionsHeader, recipeTitle, recipeInstructions;
    titleHeader.setFont(font);
    titleHeader.setString("\tTitle");
    titleHeader.setCharacterSize(22);
    titleHeader.setFillColor(sf::Color::Blue);
    titleHeader.setStyle(sf::Text::Bold);
    titleHeader.setPosition(0, 0);

    recipeTitle.setFont(font);
    recipeTitle.setCharacterSize(22);
    recipeTitle.setFillColor(sf::Color::Black);
    recipeTitle.setStyle(sf::Text::Bold);
    recipeTitle.setPosition(0, 36);

    recipeInstructions.setFont(font);
    recipeInstructions.setCharacterSize(18);
    recipeInstructions.setFillColor(sf::Color::Black);
    recipeInstructions.setStyle(sf::Text::Bold);
    recipeInstructions.setPosition(0, 506);

    ingredientsHeader.setFont(font);
    ingredientsHeader.setString("\tIngredients");
    ingredientsHeader.setCharacterSize(22);
    ingredientsHeader.setFillColor(sf::Color::Blue);
    ingredientsHeader.setStyle(sf::Text::Bold);
    ingredientsHeader.setPosition(0, 36*2);

    instructionsHeader.setFont(font);
    instructionsHeader.setString("\tInstructions");
    instructionsHeader.setCharacterSize(22);
    instructionsHeader.setFillColor(sf::Color::Blue);
    instructionsHeader.setStyle(sf::Text::Bold);
    instructionsHeader.setPosition(0, 470);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed)
                window.close();

            // User input text
            else if (event.type == sf::Event::TextEntered)
            {
                if (inputNumIngredients && userNumInput.empty() && std::isdigit(event.text.unicode) && event.text.unicode < 58 && event.text.unicode > 48)
                    userNumInput += event.text.unicode;
                if (inputSortMethod && userBinaryInput.empty() && std::isdigit(event.text.unicode) && event.text.unicode < 51 && event.text.unicode > 48)
                    userBinaryInput += event.text.unicode;
                else if (displayRecipes && (userNumInput.size() < to_string(recipes.size()).size()) && std::isdigit(event.text.unicode))
                    userNumInput += event.text.unicode;
                else if (inputIngedientsNames && (std::isalpha(event.text.unicode) || std::isblank(event.text.unicode)))
                    userStringInput += event.text.unicode;
            }

            // User pressed a key
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if ((inputNumIngredients || displayRecipes) && !userNumInput.empty())
                        userNumInput.pop_back();
                    else if (inputIngedientsNames && !userStringInput.empty())
                        userStringInput.pop_back();
                    else if (inputSortMethod && !userBinaryInput.empty())
                        userBinaryInput.pop_back();
                }

                if (event.key.code == sf::Keyboard::Return)
                {
                    if (inputNumIngredients && !userNumInput.empty())
                    {
                        userNumIngredients = stoi(userNumInput);
                        inputNumIngredients = false;
                        inputSortMethod = true;
                    }
                    else if (inputSortMethod && !userBinaryInput.empty())
                    {
                        if (userBinaryInput == "2")
                        {
                            sortByNumIngredients = true;
                        }
                        inputSortMethod = false;
                        inputIngedientsNames = true;
                    }
                    else if (displayRecipes && !userNumInput.empty() && (stoi(userNumInput) <= recipes.size()))
                    {
                        recipeNum = stoi(userNumInput) - 1;
                        displayRecipes = false;
                        displayRecipeInfo = true;

                        std::string tempString = "\t";
                        tempString += recipes[recipeNum].name;
                        recipeTitle.setString(tempString);

                        tempString = "\t";
                        int charCounter = 0;
                        std::string tempString2 = recipes[recipeNum].directions;
                        for (int i = 0; i < recipes[recipeNum].directions.size(); i++)
                        {
                            tempString += tempString2[i];
                            charCounter++;
                            if (charCounter >= 80 && tempString2[i] == ' ')
                            {
                                tempString += "\n\t";
                                charCounter = 0;
                            }
                            else if (tempString2[i] == '\n')
                            {
                                tempString += "\t";
                                charCounter = 0;
                            }
                        }
                        recipeInstructions.setString(tempString);
                        

                        ingredientsTotalPages = (int)ceil(recipes[recipeNum].numIngredients / 10.0);
                        ingredientsPageIndex = 0;
                        recipeIngredients.clear();
                        for (int i = 0; i < recipes[recipeNum].numIngredients; i++)
                        {
                            sf::Text temp;
                            temp.setFont(font);
                            tempString = "\t\t";
                            tempString += to_string(i+1);
                            tempString += ". ";
                            tempString += recipes[recipeNum].ingredients[i];
                            temp.setString(tempString);
                            temp.setCharacterSize(18);
                            temp.setFillColor(sf::Color::Black);
                            temp.setStyle(sf::Text::Bold);
                            temp.setPosition(0, 36 * (i%10 + 3));
                            recipeIngredients.push_back(temp);
                        }

                    }
                    else if (inputIngedientsNames && !userStringInput.empty())
                    {
                        userIngredients[ingredients.size()].setString(userStringInput);
                        ingredients.push_back(userStringInput);
                        userStringInput.clear();
                        currUserIngredient.move(0, 36);
                        if (ingredients.size() == userNumIngredients)
                        {
                            userNumInput.clear();
                            inputIngedientsNames = false;
                            displayRecipes = true;
                            recipes = book.recipeBook::FindRecipes(ingredients);
                            if (sortByNumIngredients)
                            {
                                recipes = book.recipeBook::SortRecipes();
                            }
                            totalPages = (int)ceil(recipes.size() / 20.0);
                            pageIndex = 0;
                            listedRecipes.clear();
                            for (int i = 0; i < 20; i++)
                            {
                                if (i + (pageIndex * 20) >= recipes.size())
                                {
                                    break;
                                }
                                sf::Text temp;
                                temp.setFont(font);
                                int tempRecipeNum = 1 + i + (pageIndex * 20);
                                std::string tempString = "\t";
                                tempString += std::to_string(tempRecipeNum);
                                tempString += ". ";
                                tempString += recipes[i + (pageIndex * 20)].name;
                                temp.setString(tempString);
                                temp.setCharacterSize(18);
                                temp.setFillColor(sf::Color::Black);
                                temp.setStyle(sf::Text::Bold);
                                temp.setPosition(0, 36 * (i + 1));
                                listedRecipes.push_back(temp);
                            }

                            listedNumIngredients.clear();
                            for (int i = 0; i < 20; i++)
                            {
                                if (i + (pageIndex * 20) >= recipes.size())
                                {
                                    break;
                                }
                                sf::Text temp;
                                temp.setFont(font);
                                std::string tempString = "\t";
                                tempString += to_string(recipes[i + (pageIndex * 20)].numIngredients);
                                temp.setString(tempString);
                                temp.setCharacterSize(18);
                                temp.setFillColor(sf::Color::Black);
                                temp.setStyle(sf::Text::Bold);
                                temp.setPosition(960, 36 * (i + 1));
                                listedNumIngredients.push_back(temp);
                            }
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (displayRecipes)
                    {
                        displayRecipes = false;
                        inputNumIngredients = true;
                        sortByNumIngredients = false;
                        userNumInput.clear();
                        userStringInput.clear();
                        userBinaryInput.clear();
                        ingredients.clear();
                        recipes.clear();
                        listedRecipes.clear();
                        listedNumIngredients.clear();
                        currUserIngredient.setPosition(350, 36 * 3);
                    }
                    else if (displayRecipeInfo)
                    {
                        displayRecipeInfo = false;
                        displayRecipes = true;
                        userNumInput.clear();
                    }
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    if (displayRecipes)
                    {
                        if (pageIndex > 0)
                        {
                            pageIndex--;
                            listedRecipes.clear();
                            for (int i = 0; i < 20; i++)
                            {
                                if (i + (pageIndex * 20) >= recipes.size())
                                {
                                    break;
                                }
                                sf::Text temp;
                                temp.setFont(font);
                                int tempRecipeNum = 1 + i + (pageIndex * 20);
                                std::string tempString = "\t";
                                tempString += std::to_string(tempRecipeNum);
                                tempString += ". ";
                                tempString += recipes[i + (pageIndex * 20)].name;
                                temp.setString(tempString);
                                temp.setCharacterSize(18);
                                temp.setFillColor(sf::Color::Black);
                                temp.setStyle(sf::Text::Bold);
                                temp.setPosition(0, 36 * (i + 1));
                                listedRecipes.push_back(temp);
                            }

                            listedNumIngredients.clear();
                            for (int i = 0; i < 20; i++)
                            {
                                if (i + (pageIndex * 20) >= recipes.size())
                                {
                                    break;
                                }
                                sf::Text temp;
                                temp.setFont(font);
                                std::string tempString = "\t";
                                tempString += to_string(recipes[i + (pageIndex * 20)].numIngredients);
                                temp.setString(tempString);
                                temp.setCharacterSize(18);
                                temp.setFillColor(sf::Color::Black);
                                temp.setStyle(sf::Text::Bold);
                                temp.setPosition(960, 36 * (i + 1));
                                listedNumIngredients.push_back(temp);
                            }
                        }
                    }

                    else if (displayRecipeInfo)
                    {
                        if (ingredientsPageIndex > 0)
                        {
                            ingredientsPageIndex--;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    if (displayRecipes)
                    {
                        if (pageIndex < totalPages-1)
                        {
                            pageIndex++;
                            listedRecipes.clear();
                            for (int i = 0; i < 20; i++)
                            {
                                if (i + (pageIndex * 20) >= recipes.size())
                                {
                                    break;
                                }
                                sf::Text temp;
                                temp.setFont(font);
                                int tempRecipeNum = 1 + i + (pageIndex * 20);
                                std::string tempString = "\t";
                                tempString += std::to_string(tempRecipeNum);
                                tempString += ". ";
                                tempString += recipes[i + (pageIndex * 20)].name;
                                temp.setString(tempString);
                                temp.setCharacterSize(18);
                                temp.setFillColor(sf::Color::Black);
                                temp.setStyle(sf::Text::Bold);
                                temp.setPosition(0, 36 * (i + 1));
                                listedRecipes.push_back(temp);
                            }

                            listedNumIngredients.clear();
                            for (int i = 0; i < 20; i++)
                            {
                                if (i + (pageIndex * 20) >= recipes.size())
                                {
                                    break;
                                }
                                sf::Text temp;
                                temp.setFont(font);
                                std::string tempString = "\t";
                                tempString += to_string(recipes[i + (pageIndex * 20)].numIngredients);
                                temp.setString(tempString);
                                temp.setCharacterSize(18);
                                temp.setFillColor(sf::Color::Black);
                                temp.setStyle(sf::Text::Bold);
                                temp.setPosition(960, 36 * (i + 1));
                                listedNumIngredients.push_back(temp);
                            }
                        }
                    }

                    else if (displayRecipeInfo)
                    {
                        if (ingredientsPageIndex < ingredientsTotalPages - 1)
                        {
                            ingredientsPageIndex++;
                        }
                    }
                }
            }
        }


        // Set current user texts
        currNumIngredients.setString(userNumInput);
        currUserIngredient.setString(userStringInput);
        userNumRecipe.setString(userNumInput);
        userSortInput.setString(userBinaryInput);

        // Draw and display window
        window.clear();
        window.draw(rectangle);
        if (!displayRecipes && !displayRecipeInfo)
        {
            window.draw(title);
            window.draw(numIngredientsPrompt);
            window.draw(currNumIngredients);
            if (!inputNumIngredients)
            {
                window.draw(sortPrompt);
                window.draw(userSortInput);
            }
            if (inputIngedientsNames)
            {
                for (int i = 0; i < userNumIngredients; i++)
                {
                    window.draw(ingredientsPrompts[i]);
                }
                window.draw(currUserIngredient);
                for (int i = 0; i < ingredients.size(); i++)
                {
                    window.draw(userIngredients[i]);
                }
            }
        }
        else if (displayRecipes)
        {
            window.draw(userInstructions);
            window.draw(recipesHeader);
            window.draw(numIngredientsHeader);
            window.draw(horizontalLine);
            window.draw(verticalLine);
            window.draw(recipePrompt);
            window.draw(userNumRecipe);

            for (int i = 0; i < listedRecipes.size(); i++)
            {
                window.draw(listedRecipes[i]);
            }
            for (int i = 0; i < listedNumIngredients.size(); i++)
            {
                window.draw(listedNumIngredients[i]);
            }

        }

        else
        {
            window.draw(userInstructions);
            window.draw(titleHeader);
            window.draw(ingredientsHeader);
            window.draw(instructionsHeader);
            window.draw(recipeTitle);
            window.draw(recipeInstructions);
            for (int i = 0; i < 10; i++)
            {
                if (i + (ingredientsPageIndex*10) < recipeIngredients.size())
                window.draw(recipeIngredients[i + (ingredientsPageIndex * 10)]);
            }

        }


        window.display();
    }

    return 0;
}