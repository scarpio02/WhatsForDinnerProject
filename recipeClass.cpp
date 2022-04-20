#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

struct recipe {
    string name;
    vector<string> ingredients;
    unsigned int numIngredients = 0;
    string directions;
};

class recipeBook {
private:
    map<string, recipe> recipeList;
    vector<recipe> recipes;

public:
    /*
    NOTES
    Nothing for this function
    */
    recipeBook() {
        // read in first file
        ifstream recipeListOne("recipes_raw_nosource_ar.json");
        json jsonFileOne = json::parse(recipeListOne);
        // iterate through JSON file
        for (auto i : jsonFileOne) {
            recipe r;
            // add name to recipe
            string name;
            if (i["title"] == nullptr)
                continue;
            r.name = i["title"];
            // Add ingredients to recipe
            vector<string> ingredients = i["ingredients"];
            if (ingredients.at(1).find("ADVERTISEMENT") != string::npos) {
                for (auto& ingredient : ingredients) {
                    ingredient = ingredient.erase(ingredient.size() - 13);
                }
            }
            r.ingredients = ingredients;
            if (ingredients.size() == 0)
                continue;
            if (r.ingredients.at(r.ingredients.size() - 1) == "")
                r.ingredients.pop_back();
            // add number of ingredients (used later for sorting
            r.numIngredients = r.ingredients.size();
            // Add directions to recipe
            string directions;
            if (i["instructions"] == nullptr)
                continue;
            r.directions = i["instructions"];
            // push into map
            recipeList[r.name] = r;
        }

        // read second file
        ifstream recipeListTwo("recipes_raw_nosource_fn.json");
        json jsonFileTwo = json::parse(recipeListTwo);
        // iterate through 2nd JSON file
        for (auto i : jsonFileTwo) {
            recipe r;
            // add name to recipe
            string name;
            if (i["title"] == nullptr)
                continue;
            r.name = i["title"];
            // Add ingredients to recipe
            vector<string> ingredients = i["ingredients"];
            r.ingredients = ingredients;
            if (ingredients.size() == 0)
                continue;
            if (r.ingredients.at(r.ingredients.size() - 1) == "")
                r.ingredients.pop_back();
            // add number of ingredients (used later for sorting
            r.numIngredients = r.ingredients.size();
            // Add directions to recipe
            string directions;
            if (i["instructions"] == nullptr)
                continue;
            r.directions = i["instructions"];
            // push into map
            recipeList[r.name] = r;
        }

        // read third file
        ifstream recipeListThree("recipes_raw_nosource_epi.json");
        json jsonFileThree = json::parse(recipeListThree);
        // iterate through 3rd JSON file
        for (auto i : jsonFileThree) {
            recipe r;
            // add name to recipe
            string name;
            if (i["title"] == nullptr)
                continue;
            r.name = i["title"];
            // Add ingredients to recipe
            vector<string> ingredients = i["ingredients"];
            r.ingredients = ingredients;
            if (ingredients.size() == 0)
                continue;
            if (r.ingredients.at(r.ingredients.size() - 1) == "")
                r.ingredients.pop_back();
            // add number of ingredients (used later for sorting
            r.numIngredients = r.ingredients.size();
            // Add directions to recipe
            string directions;
            if (i["instructions"] == nullptr)
                continue;
            r.directions = i["instructions"];
            // push into map
            recipeList[r.name] = r;
        }
    }

    /*
    NOTES
    Nothing for now
     */
    vector<recipe> FindRecipes(const vector<string>& ingredientList) {
        recipes.clear();
        // find valid recipes
        map<string, bool> checklist; // one-to-one connection for item and if found
        for (const auto& ingredient : ingredientList)
            checklist[ingredient] = false;
        for (const auto& recipe : recipeList) { // goes through each recipe
            for (auto& ingredient : recipe.second.ingredients) { // goes through ingredient list
                for (const auto& item : checklist) { // goes through each ingredient, checking if it matches map
                    if (ingredient.find(item.first) != string::npos) {
                        checklist[item.first] = true;
                    }
                }
            }
            bool goodRecipe = true;
            for (const auto& ingredient : checklist) {
                if (!ingredient.second)
                    goodRecipe = false;
            }
            if (goodRecipe)
                recipes.push_back(recipe.second);
            for (const auto& ingredient : checklist) {
                checklist[ingredient.first] = false;
            }
        }

        //        // printing used to test function outputs -> comment out in UI testing
        //        for (auto o : recipes) {
        //            PrintRecipe(o);
        //        }

        return recipes;
    }

    /*
    function to merge all the small vectors together
    */
    void finalMerge(vector<recipe>& info, int left, int mid, int right) {
        vector<recipe> temp;
        int lMove = left;
        int mMove = mid + 1;

        while (lMove <= mid && mMove <= right) {
            if (info[lMove].numIngredients <= info[mMove].numIngredients) {
                temp.push_back(info[lMove]);
                lMove++;
            }
            else {
                temp.push_back(info[mMove]);
                mMove++;
            }
        }
        while (lMove <= mid) {
            temp.push_back(info[lMove]);
            lMove++;
        }
        while (mMove <= right) {
            temp.push_back(info[mMove]);
            mMove++;
        }
        for (int i = left; i <= right; i++) {
            info[i] = temp[i - left];
        }
    }

    /*
    function to carry out the mergesort of the recipe vector
    */
    void merging(vector<recipe>& info, int left, int right) {
        if (left < right) {
            int mid = left + ((right - left) / 2);
            merging(info, left, mid);
            merging(info, (mid + 1), right);
            finalMerge(info, left, mid, right);
        }
    }

    /*
    NOTES
    FIXME - This function has not been implemented yet lol
    */
    vector<recipe> SortRecipes() {
        int left = 0;
        int right = (recipes.size() - 1);
        vector<recipe> temp = recipes;
        merging(temp, left, right);
        recipes = temp;

        return recipes;
    }

    /*
    NOTES
    All words must begin with a capital letter for this function to work
    */
    vector<recipe> SearchRecipes(const string& search) {
        vector<recipe> results;
        for (auto i : recipeList) {
            if (i.second.name.find(search) != string::npos)
                results.push_back(i.second);
        }

        // printing used to test function outputs -> comment out in UI testing
//        for (auto j : results)
//            PrintRecipe(j);

        return results;
    }

    /*
    NOTES
    This function works weird when printing multiple recipes, but this likely won't be used on implementation
    */
    void PrintRecipe(recipe r) {
        cout << "Title: " << r.name << endl;
        cout << "Ingredients:" << endl;
        for (auto i : r.ingredients)
            cout << "\t- " << i << endl;
        cout << "Instructions:" << endl;
        cout << r.directions << endl;
    }
};

// TESTING FUNCTION-> DELETE ME IF I'M STILL HERE
//int main() {
//    recipeBook book;
//    vector<string> list = {"Chicken", "pasta", "cheese"};
//    book.FindRecipes(list);
//    book.SortRecipes();
//    return 0;
//}