#include "utils.h"


// ------------------ Book --------------------
Book::Book(vector<string> &input)
{
    this ->totol_book_reviews_likes = 0;
    this ->score = 0;

    // dataset guarantees no execptions here
    this->book_id               = stoi(input[0]);
    this->book_title            =      input[1];
    this->genre_1               =      input[2];
    this->genre_2               =      input[3];
    this->pages                 = stoi(input[4]);
    this->author_name           =      input[5];
    this->author_average_rating = stof(input[6]);
}


// ------------------ Review --------------------
Review::Review(vector<string> &input)
{
    // dataset guarantees no execptions here
    this->book_id         = stoi(input[0]);
    this->rating          = stoi(input[1]);
    this->number_of_likes = stoi(input[2]);
}


// ----------------------- others -----------------------
void specify_boundaries(long *arr, bool is_book)
{
    int points = is_book ? BOOKS_THREADS_NUM - 1 : REVIEWS_THREADS_NUM - 1;
    string path = is_book ? BOOKS_PATH : REVIEWS_PATH;

    FILE *file;
    file = fopen((const char*)path.c_str(), "r");
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < points; i++)
    {
        int curr_char;
        long pos = (i + 1) * floor(length / (points + 1));
        while (true)
        {
            fseek(file, pos, SEEK_SET);
            curr_char = fgetc(file);
            if (curr_char == '\n')
            {
                *(arr + i) = pos;
                break;
            }
            else
                ++pos;
        }
    }
    fseek(file, 0, SEEK_END);
    *(arr + points) = ftell(file);
    fclose(file);
}
