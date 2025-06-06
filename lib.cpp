#include <iostream>
#include <string>
#include <fstream>
#define el endl
using namespace std;

//Developed by Ali Efe ォKIR, Yusuf Efe TEZCAN, Muhammed Seccad BENDI DERYAN 

struct book{               //Kitaplar i癟in structure
    public:
        string bname;      //Kitap ismi
        string aname;      //Yazar ismi
        int bpage;         //Sayfa Say覺s覺
        bool inUse;        //Kullan覺mda
};
bool isAdmin;              //admin bool'u
                         //FONKSIYONLAR
void adminEvents(bool clearConsole);     //admin opsiyonlar覺
void studentEvents(bool clearConsole);   //繹��renci opsiyonlar覺
void adminCheck();                       //admin kontrol羹
void adminLogin();                       //admin giri��i
void listBooks();                        //kitap g繹sterme
void addBook();                          //kitap ekleme
void giveBook();                         //kitap 繹d羹n癟 alma
void removeBook();                       //kitap silme
void depBook();                          //kitap iade etme
void wait();                             //bekleme komutu     

                            //Devam tu�� gereklili��i
void wait(){


    cout << "Devam etmek icin bir tusa basin..." << el;
    cin.ignore(); // program覺n devam etmesi i癟in kullan覺c覺n覺n bir tu��a basmas覺n覺 ister
    cin.get();    // Tu�� giri��i bekle
}

                            //admin Giri��i
void adminLogin()
{
	string username="admin";   //admin giri��i kullan覺c覺 ad覺
    string password="1234";    //admin giri��i ��ifresi
    
	string input_username,input_password;
    cout<<"Kullanici adi:";
    cin >>input_username;
    cout<<"Sifre:";
    cin >>input_password;
    if(input_username == username && input_password == password)    //Girdilerler tan覺mlanm覺��lar覺n e��le��mesi
    {
        isAdmin=true;
        adminEvents(true);
        
    }
    else
    cout<<"Hatali giris. Tekrar deneyiniz!"<<el;    //hatali giri��
    adminLogin();
}

                            //admin kontrol羹
void adminCheck(){
   if(isAdmin){      //admin
    adminEvents(false);
   }
   else{              //admin de��il
    studentEvents(false);
   }
}

                            //admin opsiyonu
void adminEvents(bool clearConsole)
{
    system("CLS");    //konsol temizleme komutu
    string options[] = { "Liste", "Kitap Ekleme", "Kitap Silme", "Kitap Verme", "Kitap Iade","Cikis" }; // Opsiyonlar覺n tan覺mlanmas覺
    
    if (clearConsole) {
        system("CLS");
        cout<<"Yapmak istediginiz eylemi secin:\n";
    }

    for (int i = 0; i < sizeof(options) / sizeof(string); i++)  //Se癟ilecek opsiyon i癟in index atamas覺
    {
        cout << "\n" << i + 1 << ". " << options[i] << "\n";
    }
    cout << "\n";

     // Index i switch e aktarma 
    int selectedIndex; 
    cin >> selectedIndex;
    system("CLS");
    switch (selectedIndex) {    //Opsiyonlar覺n atanmas覺

    default:
        adminEvents(true); 
        break;
    case 1: 
        listBooks();      //kitaplar覺 listeler
        wait();           //bekleme komutu 
        adminCheck();     //admin kontrol羹
        break;
    case 2:
        addBook();         //kitap ekleme
        break;
    case 3:
        removeBook();      //kitap silme
        break;
    case 4:
        giveBook();        //kitap 繹d羹n癟 verme
        break;
    case 5:
        depBook();         //kitap iadesi
        break;
    case 6:
        exit(1);           //癟覺k覺�� komutu
        break;
    }
}

                            //kitap listesi
void listBooks()
 {
    fstream kitap;
    kitap.open("kitaplar.txt", ios::in); //txt dosyas覺n覺 a癟ar
    string line;
    int i=1;
    
    while (getline(kitap, line)) {  //getline kullanarak verileri 癟eker
        cout << i <<". " << line << endl;
        i++;
    }
   
 }

                            //kitap ekleme
void addBook() {
    int n;
    cout << "Eklemek istediginiz kitap sayisini girin: ";
    cin >> n;
    cin.ignore(); // program覺n devam etmesi i癟in kullan覺c覺n覺n bir tu��a basmas覺n覺 ister

    struct book b[n];   
    fstream kitap;
    kitap.open("kitaplar.txt", ios::app);   //kitaplar.txt ye append olarak yazmas覺n覺 sa��lar

    for(int i = 0; i < n; i++) {            
        cout << "Kitap bilgilerini girin:" << el;

        cout << "Kitap adi: ";
        getline(cin, b[i].bname); // Aralardaki bo��luklar i癟in getline kullan覺l覺r
        kitap << "Kitap adi: " << b[i].bname << ",\t";

        cout << "Yazar adi: ";
        getline(cin, b[i].aname); // Aralardaki bo��luklar i癟in getline kullan覺l覺r
        kitap << "Yazarin adi: " << b[i].aname << ",\t";

        cout << "Sayfa sayisi: ";
        cin >> b[i].bpage;      //integer de��i��keni oldu��u i癟in getline a gerek yok
        kitap << "Sayfa sayisi: " << b[i].bpage << "\n";
        cin.ignore(); // program覺n devam etmesi i癟in kullan覺c覺n覺n bir tu��a basmas覺n覺 ister

        cout << "Kitap listeye eklendi." << el;
    }

    kitap.close();

    adminEvents(true); //admin events k覺sm覺na d繹nmesini sa��lar
}

                            //kitap silme
void removeBook() {
    listBooks();
    int removeIndex;                    //silinecek kitap i癟in index tan覺mlan覺r
    cout << "Silmek istediginiz kitabin numarasini girin: ";
    cin >> removeIndex;

    fstream kitap;
    kitap.open("kitaplar.txt", ios::in); //kitaplar.txt yi a癟ar

    if (!kitap.is_open()) {              //kitaplar.txt yoksa geri bildirim verir
        cout << "Dosya acilamadi!" << el;
        return;
    }

    const int MAX_BOOKS = 100;            //Maksimum kitap say覺s覺
    string books[MAX_BOOKS];
    int currentIndex = 0;
    string line;

    //Dosyadaki kitaplar覺 diziye okutma
    while (getline(kitap, line)) {        
        if (currentIndex < MAX_BOOKS) {
            books[currentIndex] = line;   //Line da yazanlar覺 book arrayine yazd覺r覺r
            currentIndex++;
        }
    }

    kitap.close();

    // Silinmesi gereken kitab覺 atlayarak dosyaya yazar
    kitap.open("kitaplar.txt", ios::out | ios::trunc); //trunc : Dosya yoksa dosya olu��turur, Varsa de��erleri silerek a癟ar

    for (int i = 0; i < currentIndex; i++) {
        if (i + 1 != removeIndex) {   //removeIndex hari癟 t羹m sat覺rlar覺 tekrar yazd覺r覺r
            kitap << books[i] << el;  //el == endl
        }
    }

    kitap.close();

    cout << "Kitap silindi." << el;
    wait();
    adminEvents(true);
}

                            //kitap 繹d羹n癟 verilmesi
void giveBook() {
    int bookIndex;
    bool validIndex = false; 
    string studentNumber;
    fstream kitap;

    while (!validIndex) {                        //Ge癟ersiz index olana kadar d繹ng羹y羹 d繹nd羹r羹r
        listBooks();
        cout << "Almak istediginiz kitabin numarasini girin: ";
        cin >> bookIndex;

        kitap.open("kitaplar.txt", ios::in);    //kitaplar.txt yi a癟ar

        const int MAX_BOOKS = 100;              // Maksimum kitap say覺s覺
        string books[MAX_BOOKS];
        int currentIndex = 0;
        string line;

        while (getline(kitap, line)) {              
            if (currentIndex < MAX_BOOKS) {
                books[currentIndex] = line;     //Line da yazanlar覺 book arrayine yazd覺r覺r
                currentIndex++;
            }
        }

        kitap.close();

        if (bookIndex > 0 && bookIndex <= currentIndex) {                       //bookIndex liste s覺n覺rlar覺 i癟erisindeyse 癟al覺��覺r
            validIndex = true;                           

            if (books[bookIndex - 1].find("(kullanimda)") != string::npos) {    //.find :dizi i癟erisinde string arar    npos: bulunamad覺 durumunu belirtmek i癟in kullan覺l覺r
                cout << "Bu kitap zaten kullanimda. Baska bir kitap secin." << el;
                validIndex = false;
            } else {
                cout << "Ogrenci numarasini girin: ";
                cin >> studentNumber;

                books[bookIndex - 1] += " (kullanimda)";                        //Listeden se癟ilen index e kullan覺mda ifadesini ekler

                kitap.open("kitaplar.txt", ios::out | ios::trunc);              //trunc : Dosya yoksa dosya olu��turur, Varsa de��erleri silerek a癟ar
 
                for (int i = 0; i < currentIndex; i++) {                        //kitaplara tekrar index atar
                    kitap << books[i] << el;
                }

                kitap.close();
                cout << "Kitap verildi." << el;
            }
        } else {
            cout << "Gecersiz kitap numarasi. Tekrar deneyin." << el;           
        }
    }
    wait();
    adminEvents(true);
}

                            //kitap iadesi
void depBook() {
    int bookIndex;
    bool validIndex = false;
    string studentNumber;
    fstream kitap;

    while (!validIndex) {
        listBooks();
        cout << "Geri vermek istediginiz kitabin numarasini girin: ";
        cin >> bookIndex;

        kitap.open("kitaplar.txt", ios::in);                                        //kitaplar.txt yi a癟ar

        const int MAX_BOOKS = 100;                                                  // Maksimum kitap say覺s覺
        string books[MAX_BOOKS];
        int currentIndex = 0;
        string line;

        while (getline(kitap, line)) {                      
            if (currentIndex < MAX_BOOKS) {
                books[currentIndex] = line;                                          //Line da yazanlar覺 book arrayine yazd覺r覺r
                currentIndex++;
            }
        }

        kitap.close();

        if (bookIndex > 0 && bookIndex <= currentIndex) {                             //bookIndex liste s覺n覺rlar覺 i癟erisindeyse 癟al覺��覺r
            validIndex = true;

            if (books[bookIndex - 1].find("(kullanimda)") == string::npos) {          //.find :dizi i癟erisinde string arar    npos: bulunamad覺 durumunu belirtmek i癟in kullan覺l覺r
                cout << "Bu kitap kullanimda degil. Kullanimda olan bir kitap numarasi girin." << el << el;
                validIndex = false;
            } else {
                cout << "Ogrenci numarasini girin: ";
                cin >> studentNumber;

                //Listeden se癟ilen indexten kullan覺mda ifadesini siler
                size_t pos = books[bookIndex - 1].find("(kullanimda)");                //size_t:i��aretsiz bir de��i��ken olu��turmay覺 sa��lar
                books[bookIndex - 1].erase(pos, string("(kullanimda)").length());      //erase operat繹r羹nde ilk s覺radaki ba��lang覺癟 konumu ikincisi silece��i karakter say覺s覺

                kitap.open("kitaplar.txt", ios::out | ios::trunc);                     //trunc : Dosya yoksa dosya olu��turur, Varsa de��erleri silerek a癟ar

                for (int i = 0; i < currentIndex; i++) {                               //kitaplara tekrar index atar
                    kitap << books[i] << el;
                }

                kitap.close();

                cout << "Kitap geri verildi." << el;
            }
        } else {
            cout << "Gecersiz kitap numarasi. Tekrar deneyin." << el;
        }
    }
    wait();
    adminEvents(true);
}

                             //����renci opsiyonu
void studentEvents(bool clearConsole)
{
    
    string options[] = { "Liste", "Cikis" };   //opsiyonun tan覺mlanmas覺
   

    if (clearConsole) {
        system("CLS");                //konsolu temizleme komutu
    }

    for (int i = 0; i < sizeof(options) / sizeof(string); i++) 
    {
        cout << "\n" << (i + 1) << ". " << options[i] << "\n";
    }
    cout << "\n";

    int selectedIndex;                  
    cin >> selectedIndex;
    
    switch (selectedIndex) {            //index se癟imi

    default:
        studentEvents(true);
        break;
    case 1:
        listBooks();    
        adminCheck();
        break;
    case 2:
        exit(1);
        break;
    }
}

                            //Giri�� ekran覺
int main() {
    cout << "=========================================\n";
    cout << "|     Library Management System         |\n";
    cout << "=========================================\n";
	cout<<"\n";
	cout<<"Lutfen giris tipinizi seciniz:"<<endl;
	cout<<"1. Admin girisi"<<endl;
	cout<<"2. Ogrenci girisi"<<endl;

	int loginIndex;
    cin >> loginIndex;
    
    switch (loginIndex) {            //Login index se癟imi yap覺l覺r

    case 1: 
        adminLogin();                //admin giri��i se癟imi
        break;
	case 2:
        studentEvents(true);         //繹��renci giri��i se癟imi
        break;
        }
    return 0;

    }
