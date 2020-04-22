#include "utils.h"


// -------------------- Books --------------------
Books::Books(string path, string genre)
{
    this->path = path;
    this->genre = genre;
}

void Books::insert_book(Book new_book)
{
    this->books.insert({new_book.get_book_id(), new_book});
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

    if (file)
      cout << file.gcount() <<" characters read successfully.\n";
    else
      cout << "error: only " << file.gcount() << " could be read\n";
    file.close();
    this->buffer = buff;
    this->buffer_length = length;
    // TODO: delete[] buff when parsed.
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
                        Book new_book(line_vec);
                        this->insert_book(new_book);
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
    cout << "map size : " << this->books.size() << endl;
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

void Reviews::insert_review(Review new_review)
{
    this->reviews.push_back(new_review);
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

    if (file)
      cout << file.gcount() <<" characters read successfully.\n";
    else
      cout << "error: only " << file.gcount() << " could be read\n";
    file.close();
    this->buffer = buff;
    this->buffer_length = length;
    // TODO: delete[] buff when parsed.
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
                    Review new_review(line_vec);
                    this->insert_review(new_review);
                    break;
                }
                word.push_back(line[j]);
            }
            line = "";
            continue;
        }
        line.push_back(this->buffer[i]);
    }
    cout << "map size : " << this->reviews.size() << endl;
    delete[] this->buffer;
}

Reviews::~Reviews()
{
}


// ------------------ Book --------------------
Book::Book(vector<string> &input)
{
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
