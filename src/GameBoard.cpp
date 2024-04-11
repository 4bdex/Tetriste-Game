#include "headers/GameBoard.hpp"


Piece::Piece(PColor c, PShape s) : color(c), shape(s)
{
    next = nullptr;
    shapePrev = nullptr;
    shapeNext = nullptr;
    colorPrev = nullptr;
    colorNext = nullptr;
}
Piece *Piece::generateRandomPiece(int PiecePool)
{
    return new Piece(static_cast<PColor>(rand() % PiecePool), static_cast<PShape>(rand() % PiecePool));
}
Queue::Queue(int PiecePool) : front(nullptr), rear(nullptr), PiecePool(PiecePool){}
void Queue::initQueue()
{
    for (int i = 0; i < 4; i++)
    {
        enqueue(Piece::generateRandomPiece(PiecePool));
    }
}
Queue::~Queue()
{
    Piece *current = front;
    while(current != nullptr){
        Piece *next = current->next;
        delete current;
        current = next;
    }
}
void Queue::enqueue(Piece *piece)
{
    if (front == nullptr)
    {
        front = piece;
        rear = piece;
    }
    else
    {
        rear->next = piece;
        rear = piece;
    }
}
Piece *Queue::dequeue()
{
    if (front == nullptr)
    {
        return nullptr;
    }
    Piece *temp = front;
    front = front->next;
    // add a piece to be infinite in the queue
    enqueue(Piece::generateRandomPiece(PiecePool));
    return temp;
}
Piece *Queue::getFront()
{
    return front;
}
Piece *Queue::getRear()
{
    return rear;
}

void GameBoard::init(int PiecePool) {
    this->PiecePool = PiecePool;
    head = nullptr;
    tail = nullptr;
    colorhead = new Piece *[PiecePool];
    shapehead = new Piece *[PiecePool];
    colortail = new Piece *[PiecePool];
    shapetail = new Piece *[PiecePool];
    for (int i = 0; i < PiecePool; i++)
    {
        colorhead[i] = nullptr;
        colortail[i] = nullptr;
    }
    for (int i = 0; i < PiecePool; i++)
    {
        shapehead[i] = nullptr;
        shapetail[i] = nullptr;
    }
    size = 0;
    incomingPieces = new Queue(PiecePool);
}

GameBoard::GameBoard(int PiecePool) 
{
    init(PiecePool);
    
    incomingPieces->initQueue();
    // insert 4 Pieces initially , but they should not be repeated more than 3 times
    while (size < 4){
        insert(true, new Piece(static_cast<PColor>(rand() % PiecePool), static_cast<PShape>(rand() % PiecePool)));
        checkMatches();
    }
    score = 0;
}

GameBoard::GameBoard(bool resume) 
{
    ifstream file;
    file.open(SAVE_PATH, ios::in);
    if (file.is_open())
    {
        // load difficulty first
        string line;
        getline(file, line);
        int PiecePool = stoi(line.substr(line.find(':') + 1));
        init(PiecePool);
        // load score second
        getline(file, line);
        score = stoi(line.substr(line.find(':') + 2));
        // load the pieces
        getline(file, line); // skip the line containing "Board:"
        while (getline(file, line) && line != "Queue:")
        {
            int color = stoi(line.substr(0, line.find(',')));
            int shape = stoi(line.substr(line.find(',') + 1));
            insert(true, new Piece(static_cast<PColor>(color), static_cast<PShape>(shape)));
        }
        // load the queue
        while (getline(file, line))
        {
            int color = stoi(line.substr(0, line.find(',')));
            int shape = stoi(line.substr(line.find(',') + 1));
            incomingPieces->enqueue(new Piece(static_cast<PColor>(color), static_cast<PShape>(shape)));
        }
        file.close();
        remove(SAVE_PATH);
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

GameBoard::~GameBoard()
{
    // free pieces
    Piece *current = head;
    for (int i = 0; i < size; i++)
    {
        Piece *next = current->next;
        delete current;
        current = next;
    }
}
int GameBoard::getPiecePool()
{
    return PiecePool;
}

int GameBoard::getSize()
{
    return size;
}
// get the score
int GameBoard::getScore()
{
    return score;
}
// set the score
void GameBoard::setScore(int score)
{
    this->score = score;
}
// get the head of the board
Piece *GameBoard::getHead()
{
    return head;
}
// get the tail of the board
Piece *GameBoard::getTail()
{
    return tail;
}

// insert Piece to left or right
void GameBoard::insert(bool left, Piece *piece)
{
    if (head == nullptr)
    {
        // If the board is empty
        head = piece;
        tail = piece;
    }
    else
    {
        if (left)
        {
            // Insert to the left
            piece->next = head;
            head = piece;
        }
        else
        {
            // Insert to the right
            tail->next = piece;
            tail = piece;
        }
    }
    tail->next = head;

    // Update shape pointers
    PShape shape = piece->shape;
    if (shapehead[static_cast<int>(shape)] == nullptr)
    {
        // If this is the first piece of this shape
        shapehead[static_cast<int>(shape)] = piece;
        shapetail[static_cast<int>(shape)] = piece;
    }
    else
    {
        if (left)
        {
            // Update the next and previous pointers for shape
            piece->shapeNext = shapehead[static_cast<int>(shape)];
            shapehead[static_cast<int>(shape)]->shapePrev = piece;
            shapehead[static_cast<int>(shape)] = piece;
        }
        else
        {
            // Update the next and previous pointers for shape
            piece->shapePrev = shapetail[static_cast<int>(shape)];
            shapetail[static_cast<int>(shape)]->shapeNext = piece;
            shapetail[static_cast<int>(shape)] = piece;
        }
    }

    // Update color pointers
    PColor color = piece->color;
    if (colorhead[static_cast<int>(color)] == nullptr)
    {
        // If this is the first piece of this color
        colorhead[static_cast<int>(color)] = piece;
        colortail[static_cast<int>(color)] = piece;
    }
    else
    {
        if (left)
        {

            // Update the next and previous pointers for color
            piece->colorNext = colorhead[static_cast<int>(color)];
            colorhead[static_cast<int>(color)]->colorPrev = piece;
            colorhead[static_cast<int>(color)] = piece;
        }
        else
        {

            // Update the next and previous pointers for color
            piece->colorPrev = colortail[static_cast<int>(color)];
            colortail[static_cast<int>(color)]->colorNext = piece;
            colortail[static_cast<int>(color)] = piece;
        }
    }
    // Update size
    size++;
}
// update pointer
void GameBoard::updatePointers()
{
    for (int i = 0; i < PiecePool; i++)
    {
        shapehead[i] = nullptr;
        shapetail[i] = nullptr;
    }
    Piece *current = head;
    do
    {
        int i = static_cast<int>(current->shape);
        if (shapehead[i] == nullptr)
        {
            shapehead[i] = current;
            shapetail[i] = current;
        }
        else
        {
            shapetail[i]->shapeNext = current;
            current->shapePrev = shapetail[i];
            shapetail[i] = current;
        }
        current = current->next;
    } while (current != head);

    for (int i = 0; i < PiecePool; i++)
    {
        colorhead[i] = nullptr;
        colortail[i] = nullptr;
    }
    current = head;
    do
    {
        int i = static_cast<int>(current->color);
        if (colorhead[i] == nullptr)
        {
            colorhead[i] = current;
            colortail[i] = current;
        }
        else
        {
            colortail[i]->colorNext = current;
            current->colorPrev = colortail[i];
            colortail[i] = current;
        }
        current = current->next;
    } while (current != head);
}
void GameBoard::shiftByColor(bool left, PColor color)
{
    if (colorhead[static_cast<int>(color)] == nullptr)
    {
        return;
    }

    Piece *current;
    Piece *nextPiece;
    PShape temp;

    if (left)
    {
        // Start from the head and traverse towards the tail
        current = colorhead[static_cast<int>(color)];
        temp = current->shape;
        while (current != colortail[static_cast<int>(color)])
        {
            current->shape = current->colorNext->shape;
            current = current->colorNext;
        }
        colortail[static_cast<int>(color)]->shape = temp;
    }
    else
    {
        // Start from the tail and traverse towards the head
        current = colortail[static_cast<int>(color)];
        temp = current->shape;
        while (current != colorhead[static_cast<int>(color)])
        {
            current->shape = current->colorPrev->shape;
            current = current->colorPrev;
        }
        colorhead[static_cast<int>(color)]->shape = temp;
    }
    updatePointers();
}
void GameBoard::shiftByShape(bool left, PShape shape)
{
    if (shapehead[static_cast<int>(shape)] == nullptr)
    {
        return;
    }

    Piece *current;
    Piece *nextPiece;
    PColor temp;

    if (left)
    {
        // Start from the head and traverse towards the tail
        current = shapehead[static_cast<int>(shape)];
        temp = current->color;
        while (current != shapetail[static_cast<int>(shape)])
        {
            current->color = current->shapeNext->color;
            current = current->shapeNext;
        }
        shapetail[static_cast<int>(shape)]->color = temp;
    }
    else
    {
        // Start from the tail and traverse towards the head
        current = shapetail[static_cast<int>(shape)];
        temp = current->color;
        while (current != shapehead[static_cast<int>(shape)])
        {
            current->color = current->shapePrev->color;
            current = current->shapePrev;
        }
        shapehead[static_cast<int>(shape)]->color = temp;
    }
    updatePointers();
}

// remove given piece from the board
void GameBoard::removePiece(Piece *piece)
{
    if (size == 0)
    {
        cout << "No pieces on the board!" << endl;
        return;
    }
    if (piece == head)
    {
        head = head->next;
        tail->next = head;
    }
    else
    {
        Piece *current = head;
        while (current->next != piece)
        {
            current = current->next;
        }
        current->next = piece->next;
        if (piece == tail)
        {
            tail = current;
        }
    }
    size--;
    updatePointers();
}

// check if there are three or more consecutive pieces of the same color or shape in the board, delete the repeated pieces and update the score (10 * number of pieces deleted)
int GameBoard::checkMatches()
{
    if (size < 3)
    {
        if (size == 0)
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
    Piece *current = head;
    Piece *nextPiece;
    int countColor = 1, countShape = 1;
    while (current != tail)
    {
        nextPiece = current->next;

        // check the color of the current piece and the next piece, if they are the same, increment the count
        while (nextPiece != head && current->color == nextPiece->color)
        {
            countColor++;
            nextPiece = nextPiece->next;
        }
        if (countColor >= 3)
        {
            score += 10 * countColor;
            for (int i = 0; i < countColor; i++)
            {
                Piece *temp = current->next;
                removePiece(current);
                if (size == 0)
                {
                    break;
                }
                temp = current->next;
                delete current;
                current = temp;
            }
            countColor = 1;
        }
        else
        {
            countColor = 1;
        }
        nextPiece = current->next;
        // check the shape of the current piece and the next piece, if they are the same, increment the count
        while (nextPiece != head && current->shape == nextPiece->shape)
        {
            countShape++;
            nextPiece = nextPiece->next;
        }
        if (countShape >= 3)
        {
            score += 10 * countShape;
            for (int i = 0; i < countShape; i++)
            {
                Piece *temp = current->next;
                removePiece(current);
                if (size == 0)
                {
                    break;
                }
                temp = current->next;
                delete current;
                current = temp;
            }
            countShape = 1;
        }
        else
        {
            countShape = 1;
        }
        current = current->next;
    }
    if (size >= 15){
        return -1;
    }
    return 0;
}

// save current game state so it can be loaded later
void GameBoard::saveGame()
{

    // save the current game state to a file csv
    ofstream file;
    // if the file exists, remove it and create a new one
    file.open(SAVE_PATH, ios::out | ios::trunc);
    if (file.is_open())
    {
        file << "Difficulty: " << PiecePool << endl;
        file << "Score: " << score << endl;
        // save board
        file << "Board:"<< endl;
        Piece *current = head;
        for (int i = 0; i < size; i++)
        {
            file << static_cast<int>(current->color) << "," << static_cast<int>(current->shape) << endl;
            current = current->next;
        }
        // save Queue
        file << "Queue:"<< endl;
        current = incomingPieces->getFront();
        while(current != nullptr)
        {
            file << static_cast<int>(current->color) << "," << static_cast<int>(current->shape) << endl;
            current = current->next;
        }
        file.close();
        cout << "Game saved successfully!" << endl;
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

// check saved game
bool checkSavedGame(){
    ifstream file;
    file.open(SAVE_PATH, ios::in);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}
// save score to a file in descending order (Format of the csv file: playername,score)
void saveScore(int score,string playername)
{
    ifstream file;
    file.open(SCORE_PATH, ios::in);

    if (file.is_open())
    {
        // get all the scores from the file and store them in a vector
        vector<pair<string, int>> scores;
        string line;
        while (getline(file, line))
        {
            string name = line.substr(0, line.find(','));
            int score = stoi(line.substr(line.find(',') + 1));
            scores.push_back(make_pair(name, score));
        }
        // add the current player's score to the vector
        scores.push_back(make_pair(playername, score));
        // sort the vector in descending order
        sort(scores.begin(), scores.end(), [](const pair<string, int> &a, const pair<string, int> &b)
             { return a.second > b.second; });
        file.close();
        // save top 10 scores only to the file from vector
        ofstream outputFile;
        // if the file exists, remove it and create a new one
        outputFile.open(SCORE_PATH, ios::out | ios::trunc);
        if (outputFile.is_open())
        {
            int count = 0;
            for (const auto &score : scores)
            {
                if (count >= 10)
                    break;
                outputFile << score.first << "," << score.second << endl;
                count++;
            }
            outputFile.close();
        }
     
    
    }
    else
    {
        // create file and save current score
        ofstream newfile;
        newfile.open(SCORE_PATH, ios::out | ios::trunc);
        if (newfile.is_open())
        {
            // add current score
            newfile << playername << "," << score << endl;
            newfile.close();
        }
    
      
    }
}
// check if the score is among Top 10 scores
bool checkScore(int score)
{
    // check if the score is among the top 10 scores, return true else false
    vector<pair<string, int>> scores;
    ifstream file;
    file.open(SCORE_PATH, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            string name = line.substr(0, line.find(','));
            int score = stoi(line.substr(line.find(',') + 1));
            scores.push_back(make_pair(name, score));
        }
        file.close();
        // sort the vector in descending order
        sort(scores.begin(), scores.end(), [](const pair<string, int> &a, const pair<string, int> &b)
             { return a.second > b.second; });
        // check if the current player's score is among the top 10 scores
        for (const auto &scr : scores)
        {
            if (scr.second < score)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        // file dosen't exists , so the score is among the top 10 scores 
        return true;
    }
}
// get Scores
vector<pair<string, int>> getScores()
{
    // get all the scores from the file and store them in a vector
    vector<pair<string, int>> scores;
    ifstream file;
    file.open(SCORE_PATH, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            string name = line.substr(0, line.find(','));
            int score = stoi(line.substr(line.find(',') + 1));
            scores.push_back(make_pair(name, score));
        }
        file.close();
        return scores;
    }
    else
    {
        return scores;
    }
}
// print the board
void GameBoard::printBoard()
{
    Piece *current = head;
    for (int i = 0; i < size; i++)
    {
        cout << "Color: " << static_cast<int>(current->color) << " Shape: " << static_cast<int>(current->shape) << endl;
        current = current->next;
    }
}