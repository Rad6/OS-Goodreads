#include "utils.h"



















// ----------------------- others -----------------------
vector<int> specify_boundaries(bool is_book)
{
    vector<int> result;
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
        int pos = (i + 1) * floor(length / (points + 1));
        while (true)
        {
            fseek(file, pos, SEEK_SET);
            curr_char = fgetc(file);
            if (curr_char == '\n')
            {
                result.push_back(pos);
                break;
            }
            else
                ++pos;
        }
    }
    fclose(file);
    return result;
}