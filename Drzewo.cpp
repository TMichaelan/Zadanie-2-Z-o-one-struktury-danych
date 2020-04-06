#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <sstream>
#include <exception>
#include <algorithm>
#include <ctime>
#include <thread>
#include <fstream>

struct Node;
Node* AVL(std::vector<unsigned int> tablica, int a, int b);
Node* BST(std::vector<unsigned int> tablica);
void PreOrder(Node* root);
void InOrder(Node* root);
Node* PostOrderDelete(Node* root);
Node* Find(Node* root, unsigned int value);
Node* Delete(Node* root, unsigned int value);
Node* RecursiveDelete(Node* toDelete);
Node* GetMax(Node* root, bool path=true);
Node* GetMin(Node* root, bool path=true);
Node* Insert(Node* root, unsigned int value);
void BFSBalance(Node* root);
unsigned int StringToInt(std::string x);
std::string IntToString(int x);
void Menu(Node* root);
unsigned int GetNumber(std::string informacja, unsigned int limit);
unsigned int GetNumberFromFile(std::string x, unsigned int limit);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::vector<unsigned int> tablicaWejsciowa;
        unsigned int n = GetNumber("Podaj ilosc danych: ", 10);

        std::cout << "Podaj klucze.\n";
        for (int i = 0; i < n; i++)
        {
            tablicaWejsciowa.push_back(GetNumber("Element " + IntToString(i + 1) + ": ", 4294967295));
        }
        unsigned int zapytanie = GetNumber("Wybierz typ drzewa:\n1- AVL\n2- BST\n", 2);
        Node* mainRoot = NULL;
        if (zapytanie == 1)
        {
            sort(tablicaWejsciowa.begin(), tablicaWejsciowa.end());
            std::clock_t timestart = std::clock();
            mainRoot = AVL(tablicaWejsciowa, 0, tablicaWejsciowa.size() - 1);
            std::clock_t timeend = std::clock();
            std::cout << "Czas tworzenia drzewa AVL: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
        }
        else
        {
            std::clock_t timestart = std::clock();
            mainRoot = BST(tablicaWejsciowa);
            std::clock_t timeend = std::clock();
            std::cout << "Czas tworzenia drzewa BST: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
        }
        Menu(mainRoot);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            std::ifstream text(argv[i]);
            if (!text.good())
            {
                std::cout << "Brak dostepu do pliku.\n";
                continue;
            }
            std::vector<unsigned int> tablicaWejsciowa;
            while (!text.eof())
            {
                std::string temp;
                getline(text,temp);
                tablicaWejsciowa.push_back(GetNumberFromFile(temp, 4294967295));
            }
            unsigned int zapytanie = GetNumber("Wybierz typ drzewa:\n1- AVL\n2- BST\n", 2);
            Node* mainRoot = NULL;
            if (zapytanie == 1)
            {
                sort(tablicaWejsciowa.begin(), tablicaWejsciowa.end());
                std::clock_t timestart = std::clock();
                mainRoot = AVL(tablicaWejsciowa, 0, tablicaWejsciowa.size() - 1);
                std::clock_t timeend = std::clock();
                std::cout << "Czas tworzenia drzewa AVL: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
            }
            else
            {
                std::clock_t timestart = std::clock();
                mainRoot = BST(tablicaWejsciowa);
                std::clock_t timeend = std::clock();
                std::cout << "Czas tworzenia drzewa BST: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
            }
            Menu(mainRoot);
        }
    }


    return 0;
}

void Menu(Node* root)
{
    std::cout << "Drzewo zostalo stworzone.\n";
    unsigned int zapytanie;
    unsigned int zapytanie2;
    Node* temp = NULL;
    std::clock_t timestart;
    std::clock_t timeend;
    do
    {
        zapytanie = GetNumber("Wybierz operacje:\n1- Wyswietlenie wartosci maksymalnej i minimalnej.\n2- Usuniecie kluczy.\n3- Wypisanie elementow drzewa (In-Order).\n4- Wypisanie elementow drzewa (Pre-Order).\n5- Usuniecie drzewa.\n6- Wypisanie podrzewa.\n7- Rownowazenie drzewa.\n8- Wyjscie.\n", 8);
        switch(zapytanie)
        {
        case 1:
            std::cout << "Sciezka do wartosci minimalnej: [";
            timestart = std::clock();
            GetMin(root);
            timeend = std::clock();
            std::cout << "\b] Czas trwania: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
            std::cout << "Sciezka do wartosci maksymalnej: [";
            GetMax(root);
            std::cout << "\b]\n";
            break;
        case 2:
            zapytanie2 = GetNumber("Podaj liczbe kluczy do usuniecia: ", 4294967295);
            for (int i = 0; i < zapytanie2; i++)
            {
                root = Delete(root, GetNumber("Podaj klucz: ", 4294967295));
            }
            break;
        case 3:
            std::cout << "[";
            timestart = std::clock();
            InOrder(root);
            timeend = std::clock();
            std::cout << "\b] Czas trwania: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
            break;
        case 4:
            std::cout << "[";
            PreOrder(root);
            std::cout << "\b]\n";
            break;
        case 5:
            std::cout << "[";
            root = PostOrderDelete(root);
            std::cout << "\b]\n";
            break;
        case 6:
            temp = Find(root, GetNumber("Podaj klucz: ", 4294967295));
            if (temp != NULL)
            {
                std::cout << "[";
                PreOrder(temp);
                std::cout << "\b]\n";
            }
            break;
        case 7:
            timestart = std::clock();
            BFSBalance(root);
            timeend = std::clock();
            std::cout << "Czas trwania: " << (timeend - timestart) / CLOCKS_PER_SEC << "ms.\n";
            break;
        case 8:
            break;
        default:
            std::cout << "Zle zapytanie.\n";
        }
    }while (zapytanie != 8);
    PostOrderDelete(root);
}

unsigned int GetNumber(std::string informacja, unsigned int limit)
{
    unsigned int n;
    for (;;)
    {
        std::cout << informacja;
        std::string l;
        getline(std::cin, l);
        n = StringToInt(l);
        if (IntToString(n) != l || n > limit || n < 1)
        {
            std::cout << "Bledne dane.\n";
            continue;
        }
        break;
    }
    return n;
}

unsigned int GetNumberFromFile(std::string l, unsigned int limit)
{
    unsigned int n;
    n = StringToInt(l);
    return n;
}

std::string IntToString(int x)
{
    std::stringstream y;
    y << x;
    std::string z;
    y >> z;
    return z;
}

unsigned int StringToInt(std::string x)
{
    std::stringstream y;
    y << x;
    unsigned int z;
    y >> z;
    return z;
}

struct Node
{
    Node* left;
    Node* right;
    int height;
    int value;
    int GetBF()
    {
        if (left == NULL && right == NULL)
            return 0;
        else if (left == NULL && right != NULL)
            return 0-right->height;
        else if (left != NULL && right == NULL)
            return left->height;
        return left->height - right->height;
    }
};

void BFSBalance(Node* root)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.\n";
        return;
    }
    std::queue<Node*> x;
    x.push(root);
    while (!x.empty())
    {
        Node* t = x.front();
        x.pop();
        while (abs(t->GetBF()) > 1)
        {
            int value = t->value;
            Delete(t, t->value);
            Insert(root, value);
        }
        if (t->left != NULL)
            x.push(t->left);
        if (t->right != NULL)
            x.push(t->right);
    }
    std::cout << "Zbalansowano\n";
}

Node* AVL(std::vector<unsigned int> tablica, int a, int b)
{
    if (b < a)
        return NULL;
    int i = floor((a + b) / 2.0);
    Node* root = (struct Node*)malloc(sizeof(Node));
    root->value = tablica[i];
    root->left = AVL(tablica, a, i - 1);
    root->right = AVL(tablica, i + 1, b);
    if (root->left == NULL && root->right == NULL)
        root->height = 1;
    else if (root->left == NULL && root->right != NULL)
        root->height = root->right->height + 1;
    else if (root->left != NULL && root->right == NULL)
        root->height = root->left->height + 1;
    else
        root->height = std::max(root->left->height, root->right->height) + 1;
    return root;
}

Node* BST(std::vector<unsigned int> tablica)
{
    Node* mainRoot = NULL;
    mainRoot = Insert(mainRoot, tablica[0]);
    for (int i = 1; i < tablica.size(); i++)
    {
        Insert(mainRoot, tablica[i]);
    }
    return mainRoot;
}

void PreOrder(Node* root)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.";
        return;
    }
    std::cout << root->value << " ";
    if (root->left != NULL)
    {
        PreOrder(root->left);
    }
    if (root->right != NULL)
    {
        PreOrder(root->right);
    }

}

void InOrder(Node* root)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.";
        return;
    }
    if (root->left != NULL)
        InOrder(root->left);
    std::cout << root->value << " ";
    if (root->right != NULL)
        InOrder(root->right);
}

Node* PostOrderDelete(Node* root)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.";
        return NULL;
    }
    if (root->left != NULL)
        root->left = PostOrderDelete(root->left);
    if (root->right != NULL)
        root->right = PostOrderDelete(root->right);
    std::cout << root->value << " ";
    free(root);
    return NULL;
}

Node* Find(Node* root, unsigned int value)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.\n";
        return NULL;
    }
    if (root->value == value)
        return root;
    if (root->left != NULL)
    {
        Node* x = Find(root->left, value);
        if (x != NULL)
            return x;
    }
    if (root->right != NULL)
    {
        Node* x = Find(root->right, value);
        if (x != NULL)
            return x;
    }
    return NULL;
}

Node* Delete(Node* root, unsigned int value)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.\n";
        return NULL;
    }
    if (root->value != value)
    {
        if (root->value < value)
        {
            if (root->right != NULL)
            {
                root->right = Delete(root->right, value);
            }
            else
            {
                std::cout << "Element " << value << " nie istnieje.\n";
                return NULL;
            }
        }
        else
        {
            if (root->left != NULL)
            {
                root->left = Delete(root->left, value);
            }
            else
            {
                std::cout << "Element " << value << " nie istnieje.\n";
                return NULL;
            }
        }
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else
        {
            if (root->left != NULL && root->right != NULL)
            {
                if (root->left->height > root->right->height)
                {
                    Node* tmp = GetMax(root->left, false);
                    root->value = tmp->value;
                    root->left = Delete(root->left, tmp->value);
                }
                else
                {
                    Node* tmp = GetMin(root->right, false);
                    root->value = tmp->value;
                    root->right = Delete(root->right, tmp->value);
                }
            }
            else if (root->left != NULL)
            {
                Node* tmp = GetMax(root->left, false);
                root->value = tmp->value;
                root->left = Delete(root->left, tmp->value);
            }
            else if (root->right != NULL)
            {
                Node* tmp = GetMin(root->right, false);
                root->value = tmp->value;
                root->right = Delete(root->right, tmp->value);
            }
        }
    }
    if (root->left == NULL && root->right == NULL)
        root->height = 1;
    else if (root->left == NULL && root->right != NULL)
        root->height = root->right->height + 1;
    else if (root->left != NULL && root->right == NULL)
        root->height = root->left->height + 1;
    else
        root->height = std::max(root->left->height, root->right->height) + 1;
    return root;
}

Node* GetMax(Node* root, bool path)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.";
        return NULL;
    }
    if (path)
        std::cout << root->value << " ";
    if (root->right != NULL)
        return GetMax(root->right, path);
    return root;
}

Node* GetMin(Node* root, bool path)
{
    if (!root)
    {
        std::cout << "Drzewo nie istnieje.";
        return NULL;
    }
    if (path)
        std::cout << root->value << " ";
    if (root->left != NULL)
        return GetMin(root->left, path);
    return root;
}

Node* Insert(Node* root, unsigned int value)
{
    if (root == NULL)
    {
        Node* x = (struct Node*)malloc(sizeof(Node));
        x->value = value;
        x->left = NULL;
        x->right = NULL;
        x->height = 1;
        return x;
    }
    if (root->value < value)
    {
        if (root->right == NULL)
        {
            Node* x = (struct Node*)malloc(sizeof(Node));
            x->value = value;
            x->left = NULL;
            x->right = NULL;
            x->height = 1;
            root->right = x;
        }
        else
        {
            Insert(root->right, value);
        }
    }
    else
    {
        if (root->left == NULL)
        {
            Node* x = (struct Node*)malloc(sizeof(Node));
            x->value = value;
            x->left = NULL;
            x->right = NULL;
            x->height = 1;
            root->left = x;
        }
        else
        {
            Insert(root->left, value);
        }
    }
    if (root->left == NULL && root->right == NULL)
        root->height = 1;
    else if (root->left == NULL && root->right != NULL)
        root->height = root->right->height + 1;
    else if (root->left != NULL && root->right == NULL)
        root->height = root->left->height + 1;
    else
        root->height = std::max(root->left->height, root->right->height) + 1;
}
