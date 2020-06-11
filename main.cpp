#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#define TAB_LEN 4

#define SUCCESS 0
#define INCORRECT_INPUT -1

using namespace std;
class Dictionary
{
private:
    const string basic_directory = "./Dictionary/";
    string cur_file = "";
    const string filenames = "./Dictionary/filenames.txt";
    vector<string> languages;
    map<string, vector<string>> plot;
    size_t max_trans_len, max_sing_len, max_plural_len, max_sin_gend_len;
    void save_lang_data(string file_name)
    {
        ofstream data_out(file_name, ifstream::out);
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
        {
            data_out << begin->first << endl;
            for(size_t i = 0; i != begin->second.size(); i++)
                data_out << begin->second[i] << endl;
        }
        data_out.close();
    }
    void files_lang_rewrite(string filename)
    {
        ifstream data_in(filename, ifstream::in);
        max_trans_len = 0, max_sing_len = 0, max_sin_gend_len = 0, max_plural_len = 0;
        pair<string, vector<string>> aux;
        string cur_str = "";
        while (getline(data_in, aux.first))
        {
            if (aux.first.length() > max_trans_len)
                max_trans_len = aux.first.length();

            getline(data_in, cur_str);
            if (cur_str.length() > max_sing_len)
                max_sing_len = cur_str.length();
            aux.second.push_back(cur_str);

            getline(data_in, cur_str);
            if (cur_str.length() > max_sin_gend_len)
                max_sin_gend_len = cur_str.length();
            aux.second.push_back(cur_str);

            getline(data_in, cur_str);
            if (cur_str.length() > max_plural_len)
                max_plural_len = cur_str.length();
            aux.second.push_back(cur_str);

            getline(data_in, cur_str);
            aux.second.push_back(cur_str);

            plot.insert(aux);
            aux.second.clear();
        }
        data_in.close();
    }
    int is_correct_gender(string gender)
    {
        for (size_t i = 0; i != gender.size(); i++)
            gender[i] = char(toupper(gender[i]));
        int result = gender.compare("F") && gender.compare("M");
        result &= gender.compare("M/F") && gender.compare("F/M");
        return result;
    }
    int add_language()
    {
        string from, to;
        flag:
        cout << "`````````````````````````````````````````" << endl;
        cout << "Enter a language you want to learn words from" << endl;
        getline(cin, from);
        if (from.compare("") == 0)
        {
            cout << "Empty input. Try again" << endl;
            goto flag;
        }
        cout << "Enter a language you want to describe these words on" << endl;
        getline(cin, to);
        for (size_t i = 0; i != languages.size(); i++)
            if (languages[i].compare(from + to) == 0 || to.compare("") == 0)
            {
                char aux;
                cout << "Already have this pair of languages or empty input. Enter 'E' to return to main menu or anything else to try again" << endl;
                cin >> aux;
                if (aux == 'E')
                    return INCORRECT_INPUT;
                goto flag;
            }
        languages.push_back(from + to);
        cout << "`````````````````````````````````````````" << endl;
        return SUCCESS;
    }
    void change_language()
    {
        flag:
        cout << "Choose on of the languages below by entering an appropriate number" << endl;
        for (size_t i = 0; i != languages.size(); i++)
            cout << i + 1 << " - " << languages[i] << endl;
        size_t au;
        cin >> au;
        if (au < 0 || au > languages.size())
        {
            cout << "Try again. Incorrect dial" << endl;
            goto flag;
        }

        save_lang_data(basic_directory + cur_file + ".txt");
        plot.clear();

        cur_file = languages[au - 1];

        files_lang_rewrite(basic_directory + cur_file + ".txt");
    }
    int add()
    {
        pair<string, vector<string>> aux;
        string cur_str = "";
        getchar();
        cout << "Enter a singular form of the word on the language u learn words on:" << endl;
        getline(cin, cur_str);
        if (cur_str.length() > max_sing_len)
            max_sing_len = cur_str.length();
        aux.second.push_back(cur_str);
        flag:
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter a gender of the singular from of this word" << endl;
        getline(cin, cur_str);
        if (is_correct_gender(cur_str))
        {
            cout << "Incorrect gender. Must be M, F, F/M, M/F" << endl;
            goto flag;
        }
        if (cur_str.length() > max_sin_gend_len)
            max_sin_gend_len = cur_str.length();
        aux.second.push_back(cur_str);

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter a plural form of the word on the language u learn words on:" << endl;
        getline(cin, cur_str);
        if (cur_str.length() > max_plural_len)
            max_plural_len = cur_str.length();
        aux.second.push_back(cur_str);

        flag_1:
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter a gender of the plural form of this word" << endl;
        getline(cin, cur_str);
        if (is_correct_gender(cur_str))
        {
            cout << "Incorrect gender. Must be M, F, F/M, M/F" << endl;
            goto flag_1;
        }
        aux.second.push_back(cur_str);

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter a translation for singular form of this word on the picked language" << endl;
        getline(cin, aux.first);
        if (aux.first.length() > max_trans_len)
            max_trans_len = aux.first.length();

        plot.insert(aux);
        return SUCCESS;
    }
    void print_pair(string word, string gender, int is_singular)
    {
        size_t amount_of_spaces = 0;
        cout << word;
        if (is_singular)
            amount_of_spaces = (max_sing_len + 1) - word.length();
        else
            amount_of_spaces = (max_plural_len + 1) - word.length();
        for (size_t i = 0; i < amount_of_spaces; i++)
            cout << ' ';
        cout << "| ";

        for (size_t i = 0; i != gender.length(); i++)
            cout << char(toupper(gender[i]));
        if (is_singular)
        {
            amount_of_spaces = (max_sin_gend_len + 1) - gender.length();
            for (size_t i = 0; i < amount_of_spaces; i++)
                cout << ' ';
            if (is_singular)
                cout << "| ";
        }
    }
    void print_all()
    {
        cout << "===========================================" << endl;
        size_t amount_of_spaces = 0;
        for (auto begin = plot.begin(); begin != plot.end(); begin++)
        {
            cout << begin->first;
            amount_of_spaces = (max_trans_len + 1) - begin->first.length();
            for (size_t i = 0; i < amount_of_spaces; i++)
                cout << ' ';
            cout << "|| ";

            print_pair(begin->second[0], begin->second[1], 1);
            print_pair(begin->second[2], begin->second[3], 0);
            cout << endl;
        }
        cout << "===========================================" << endl;
    }
    void delete_all()
    {
        plot.clear();
        max_sing_len = 0;
        max_trans_len = 0;
        max_sin_gend_len = 0;
        max_plural_len = 0;
    }
public:
    Dictionary()
    {
        flag_1:
        ifstream file_in(filenames, ifstream::in);
        if (!file_in.is_open())
        {
            ofstream file_out(filenames, ifstream::out);
            file_out.close();
            goto flag_1;
        }
        string aux_str = "";
        while (getline(file_in, aux_str))
            languages.push_back(aux_str);
        while (languages.size() == 0)
            add_language();
        cur_file = languages[0];

        ifstream data_in(basic_directory + cur_file + ".txt", ifstream::in);
        if (!data_in.is_open())
        {
            ofstream data_out(basic_directory + cur_file + ".txt", ifstream::out);
            data_out.close();    
        }
        else
            data_in.close();
        files_lang_rewrite(basic_directory + cur_file + ".txt");
        file_in.close();
    }
    int Menu()
    {
        flag:
        cout << "Current system of languages is " << cur_file << endl;
        cout << "______________________________" << endl;
        cout << "1 - Add word\n2 - See all words\n3 - Delete all words\n4 - Add language\n" <<
                "5 - Switch language\n6 - Exit\n";
        int key;
        cin >> key;
        switch(key)
        {
            case 1:
                add();
                break;
            case 2:
                print_all();
                break;
            case 3:
                delete_all();
                break;
            case 4:
                getchar();
                add_language();
                break;
            case 5:
                change_language();
                break;
            case 6:
                return SUCCESS;
                break;
            default:
                cout << "Try again" << endl;
                break;
        }
        cout << "+++++++++++++++++++++++++++++++++++++++++++" << endl;
        goto flag;
        return SUCCESS;
    }
    ~Dictionary()
    {
        save_lang_data(basic_directory + cur_file + ".txt");
        ofstream file_out(filenames, ifstream::out);
        for (size_t i = 0; i != languages.size(); i++)
            if (languages[i].compare(cur_file) == 0)
            {
               string aux = languages[i];
               languages[i] = languages[0];
               languages[0] = aux;
               break;
            }
        for (size_t i = 0; i != languages.size(); i++)
            file_out << languages[i] << '\n';
        file_out.close();
    }
};
int main()
{
    Dictionary example;
    example.Menu();
    return SUCCESS;
}
