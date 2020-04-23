#include "utils.h"


pthread_t book_threads  [BOOKS_THREADS_NUM];
pthread_t review_threads[REVIEWS_THREADS_NUM];

pthread_mutex_t _mutex;

Books   books   [BOOKS_THREADS_NUM];
Reviews reviews [REVIEWS_THREADS_NUM];

long book_bounds[BOOKS_THREADS_NUM] = {0};
long review_bounds[REVIEWS_THREADS_NUM] = {0};

string genre;

void* read_and_parse_books(void *arg)
{
    // ----------------------- reading part -----------------------
    long thread_id = (long) arg;
    long length, start;
    
    if (thread_id == 0)
        length = book_bounds[0];
    else
        length = book_bounds[thread_id] - book_bounds[thread_id - 1] - 1;
    // printf("thread %ld: len: %ld\n", thread_id, length);
    char *buff = new char[length];
    
    if (thread_id == 0)
        start = 0;
    else
        start = book_bounds[thread_id - 1] + 1;
    // printf("thread %ld: start: %ld\n", thread_id, start);
    ifstream file(BOOKS_PATH);
    if (file) {
        file.seekg(start, file.beg);
        file.read(buff, length);
        file.close();
    }
    // printf("thread %ld: %c %c \n", thread_id, buff[0], buff[1]);
    // ----------------------- parsing part -----------------------
    string line = "";
    string word = "";
    bool first_line = thread_id == 0;
    vector<string> line_vec;
    for (int i = 0; i < length; i++)
    {
        if (buff[i] == '\n')
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
                    if (line_vec[2] == genre || line_vec[3] == genre)
                    {
                        Book *new_book = new Book(line_vec);
                        books[thread_id].books.insert({(*new_book).book_id, new_book});
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
        line.push_back(buff[i]);
    }
    delete[] buff;
    // printf("thread %ld vector size: %lu\n", thread_id, books[thread_id].books.size());
}

void* read_and_parse_reviews(void *arg)
{
    // ----------------------- reading part -----------------------
    long thread_id = (long) arg;
    long length, start;
    
    if (thread_id == 0)
        length = review_bounds[0];
    else
        length = review_bounds[thread_id] - review_bounds[thread_id - 1] - 1;
    // printf("thread %ld: len: %ld\n", thread_id, length);
    char *buff = new char[length];
    
    if (thread_id == 0)
        start = 0;
    else
        start = review_bounds[thread_id - 1] + 1;
    // printf("thread %ld: start: %ld\n", thread_id, start);
    ifstream file(REVIEWS_PATH);
    if (file) {
        file.seekg(start, file.beg);
        file.read(buff, length);
        file.close();
    }
    // printf("thread %ld: %c %c \n", thread_id, buff[0], buff[1]);

    // ----------------------- parsing part -----------------------
    string line = "";
    string word = "";
    bool first_line = thread_id == 0;
    vector<string> line_vec;
    for (int i = 0; i < length; i++)
    {
        if (buff[i] == '\n')
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
                    reviews[thread_id].reviews.push_back(new_review);
                    break;
                }
                word.push_back(line[j]);
            }
            line = "";
            continue;
        }
        line.push_back(buff[i]);
    }
    delete[] buff;
    // printf("thread %ld vector size: %lu\n", thread_id, reviews[thread_id].reviews.size());
    
}

void print_result()
{
    for (int j = 0; j < REVIEWS_THREADS_NUM; j++)
    {
        for (int i = 0; i < reviews[j].reviews.size(); i++)
        {
            for (int k = 0; k < BOOKS_THREADS_NUM; k++)
            {
                unordered_map<int, Book*>::const_iterator it = books[k].books.find((*reviews[j].reviews[i]).book_id);
                if (it == books[k].books.end())
                    continue;
                (*it->second).totol_book_reviews_likes += (*reviews[j].reviews[i]).number_of_likes;
                (*it->second).score += ((*reviews[j].reviews[i]).rating * (*reviews[j].reviews[i]).number_of_likes);
            }
        }
    }
    Book *most_pop_book;
    float max = 0;
    for (int i = 0; i < BOOKS_THREADS_NUM; i++)
    {
        for (auto& it:books[i].books)
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
    }
    
    cout << "id: " << (*most_pop_book).book_id << endl;
    cout << "Title: " << (*most_pop_book).book_title << endl;
    cout << "Genres: " << (*most_pop_book).genre_1 << ", " << (*most_pop_book).genre_2 << endl;
    cout << "Number of Pages: " << (*most_pop_book).pages << endl;
    cout << "author: " << (*most_pop_book).author_name << endl;
    printf("Average Rating: %.2f\n", max);
}

int main(int argc, const char* argv[]) {

    genre = argv[1];
    
    vector <long> book_bounds_vec   = specify_boundaries(true);
    vector <long> review_bounds_vec = specify_boundaries(false);

    for (int i = 0; i < BOOKS_THREADS_NUM; i++)
        book_bounds[i] = book_bounds_vec[i];

    for (int i = 0; i < REVIEWS_THREADS_NUM; i++)
        review_bounds[i] = review_bounds_vec[i];

    pthread_mutex_init(&_mutex, NULL);

    for (long i = 0; i < BOOKS_THREADS_NUM; i++)
        pthread_create(&book_threads[i], NULL, read_and_parse_books, (void*)i);

    void *status1;
	for(long i = 0; i < BOOKS_THREADS_NUM; i++)
		pthread_join(book_threads[i], &status1);

    for (long i = 0; i < REVIEWS_THREADS_NUM; i++)
        pthread_create(&review_threads[i], NULL, read_and_parse_reviews, (void*)i);

    void *status2;
    for(long i = 0; i < REVIEWS_THREADS_NUM; i++)
		pthread_join(review_threads[i], &status2);
    print_result();
    return 0;
}