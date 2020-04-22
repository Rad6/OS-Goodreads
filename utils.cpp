#include "utils.h"


// -------------------- Books --------------------
Books::Books(string path, string genre)
{
    this->path = path;
    this->genre = genre;
}

void Books::read_csv()
{
    ifstream file(path);
    if (file) {
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);

    char *buff = new char[length];

    file.read(buff,length);

    if (!file)
      cout << "error: only " << file.gcount() << " could be read\n";
    file.close();
    this->buffer = buff;
    this->buffer_length = length;
  } 
}

void Books::parse_books()
{
    string line = "";
    string word = "";
    bool first_line = true;
    vector<string> line_vec;
    for (int i = 0; i < this->buffer_length; i++)
    {
        if (this->buffer[i] == '\n')
        {
            if (first_line)
            {
                first_line = false;
                line = "";
                continue;
            }
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == ',')
                {   
                    line_vec.push_back(word);
                    word = "";
                    continue;
                }
                if (j == line.size() - 1)
                {
                    word.push_back(line[j]);
                    line_vec.push_back(word);
                    if (line_vec[2] == this->genre || line_vec[3] == this->genre)
                    {
                        Book *new_book = new Book(line_vec);
                        this->books.insert({(*new_book).book_id, new_book});
                    }
                    word = "";
                    break;
                }
                word.push_back(line[j]);
            }
            line = "";
            line_vec.clear();
            continue;
        }
        line.push_back(this->buffer[i]);
    }
    delete[] this->buffer;
}

Books::~Books()
{
}


// ------------------ Reviews --------------------
Reviews::Reviews(string path)
{
    this->path = path;
}

void Reviews::read_csv()
{
    ifstream file(path);
    if (file) {
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);

    char *buff = new char[length];

    file.read(buff,length);

    if (!file)
      cout << "error: only " << file.gcount() << " could be read\n";
    file.close();
    this->buffer = buff;
    this->buffer_length = length;
  }
}

void Reviews::parse_reviews()
{
    string line = "";
    string word = "";
    bool first_line = true;
    vector<string> line_vec;
    for (int i = 0; i < this->buffer_length; i++)
    {
        if (this->buffer[i] == '\n')
        {
            if (first_line)
            {
                first_line = false;
                line = "";
                continue;
            }
            line_vec.clear();
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == ',')
                {
                    line_vec.push_back(word);
                    word = "";
                    continue;
                }
                if (j == line.size() - 1)
                {
                    word.push_back(line[j]);
                    line_vec.push_back(word);
                    word = "";
                    Review *new_review = new Review(line_vec);
                    this->reviews.push_back(new_review);
                    break;
                }
                word.push_back(line[j]);
            }
            line = "";
            continue;
        }
        line.push_back(this->buffer[i]);
    }
    delete[] this->buffer;
}

Reviews::~Reviews()
{
}


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

int Book::get_book_id()
{
    return this->book_id;
}


// ------------------ Review --------------------
Review::Review(vector<string> &input)
{
    // dataset guarantees no execptions here
    this->book_id         = stoi(input[0]);
    this->rating          = stoi(input[1]);
    this->number_of_likes = stoi(input[2]);
}


// ------------------ others --------------------
void print_result(unordered_map<int, Book*> &books, vector<Review*> &reviews)
{
    for (int i = 0; i < reviews.size(); i++)
    {
        unordered_map<int, Book*>::const_iterator it = books.find((*reviews[i]).book_id);
        if (it == books.end())
            continue;
        (*it->second).totol_book_reviews_likes += (*reviews[i]).number_of_likes;
        (*it->second).score += ((*reviews[i]).rating * (*reviews[i]).number_of_likes);
    }
    Book *most_pop_book;
    float max = 0;
    for (auto& it:books)
    {
        if ((*it.second).totol_book_reviews_likes == 0)
            (*it.second).score = 0;
        else
            (*it.second).score /= (*it.second).totol_book_reviews_likes;
        (*it.second).score += (*it.second).author_average_rating;
        (*it.second).score *= 0.1;
        if ((*it.second).score > max)
        {
            max = (*it.second).score;
            most_pop_book = it.second;
        }
    }
    cout << "id: " << (*most_pop_book).book_id << endl;
    cout << "Title: " << (*most_pop_book).book_title << endl;
    cout << "Genres: " << (*most_pop_book).genre_1 << ", " << (*most_pop_book).genre_2 << endl;
    cout << "Number of Pages: " << (*most_pop_book).pages << endl;
    cout << "author: " << (*most_pop_book).author_name << endl;
    printf("Average Rating: %.2f\n", max);
}