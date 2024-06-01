#include <iostream>
#include <string>
using namespace std;


const char lowRch[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к',
'л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы',
'ь','э','ю','я' }; //массив строчных Русского алфавита
const char highRch[] = { 'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К',
'Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь',
'Э','Ю','Я' };//массив заглавных Русского алфавита
const char lowEch[] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };
//массив строчных букв Английского алфавита
const char highEch[] = { 'A','B','C','D','E','F','G','H','I','J','K','L',
'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
//массив заглавных букв Английского алфавита

void correct(int& j, string& str, string ch, int shift, int i, int ABC)
{//функция для шифрования/дешифрования символа со сдвигом
    j += shift; //введённый сдвиг индекса буквы по алфавиту
    if (j >= ABC) j -= ABC;
    //корректировка при необходимости символа в диапазон алфавита
    else if (j < 0) j += ABC;
    str[i] = ch[j]; //замена символа на зашифрованный
}

void NH(string& str, int shift, int coise)
{ //функция для определения символа и его шифрования/дешифрования
    int ABCe = 26; //количество букв Английского алфавита
    int ABCr = 33; //количество букв Русского алфавита
    if (coise == 2) shift = -shift;//корректировка вида операции
    for (unsigned i = 0; i < str.size(); i++)
    { //цикл для всех символов строки
        for (int j = 0; j < 33; j++)
        {//перебор всех буквы обоих алфавитов для поиска соответствия
            if (str[i] == lowEch[j] and j < 26)
            {//сравнение с строчной английской буквой
                correct(j, str, lowEch, shift, i, ABCe);
                break;
            }
            else if (str[i] == highEch[j] and j < 26)
            {//сравнение с заглавной английской буквой
                correct(j, str, highEch, shift, i, ABCe);
                break;
            }
            else if (str[i] == lowRch[j])
            {//сравнение с строчной русской буквой
                correct(j, str, lowRch, shift, i, ABCr);
                break;
            }
            else if (str[i] == highRch[j])
            {//сравнение с заглавной русской буквой
                correct(j, str, highRch, shift, i, ABCr);
                break;
            }
        }
    }
    if (coise == 2) shift = -shift;
    //корректировка сдвига для следующий операций без его изменения
}


void correctcin(int& choice)
{//функция для ввода выбора и его проверки на корректность 
    cin >> choice;//ввод выбора
    if (choice == 3) exit(0);//выбор выйти
    if (choice != 1 and choice != 2)
    {//проверка корректности и при некорректности повторный ввод
        cout << "\nВвод некорректный, попробуйте снова. ->";
        cin >> choice;
        if (choice == 3) exit(0);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian"); //задаёт русский текст
    system("chcp 1251");

    string str = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ абвгдеёжзийклмнопрстуфхцчшщъыьэюя ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz"; 
    cout << "\nВведите '3' для выхода при любом вводе выбора.";

    int choice = 1, shift = 3;

    cout << "\n Cтрока по умолчанию: ";
    cout << str;
    cout << "\n Сдвиг по умолчанию: ";
    cout << shift;

    for (; choice != 3; )//цикл с выходом только при условии выбора выхода
    {
        cout << "\nВыберите текст";
            cout << "('1'-оставить прошлый, '2'-ввести новый). ->";
        correctcin(choice);
        if (choice == 2)
            //в случае выбора введения нового текста его ввод 
            //(ввод без разделения абзацев)
        {
            cout << "\n";
            cin.ignore();
            getline(cin, str);
            cout << "\n";
        }

        cout << "Выберите сдвиг ";
        cout << "('1'-оставить прежний, '2'-ввести новый). ->";
        correctcin(choice);
        if (choice == 2) cin >> shift;
        //в случае выбора введения нового сдвига его ввод

        cout << "Выберите ('1'-шифрование, '2'-дешифрование). ->";
        correctcin(choice);
        NH(str, shift, choice);
        cout << "\n" << str << "\n";//вывод текста после операции
    }
    return 0;
}