#include <iostream>
#include <string>
#include <fstream>
#define el endl
using namespace std;

//Developed by Ali Efe �AKIR, Yusuf Efe TEZCAN, Muhammed Seccad BENDI DERYAN 

struct book{               //Kitaplar için structure
    public:
        string bname;      //Kitap ismi
        string aname;      //Yazar ismi
        int bpage;         //Sayfa Sayısı
        bool inUse;        //Kullanımda
};
bool isAdmin;              //admin bool'u
                         //FONKSIYONLAR
void adminEvents(bool clearConsole);     //admin opsiyonları
void studentEvents(bool clearConsole);   //öğrenci opsiyonları
void adminCheck();                       //admin kontrolü
void adminLogin();                       //admin girişi
void listBooks();                        //kitap gösterme
void addBook();                          //kitap ekleme
void giveBook();                         //kitap ödünç alma
void removeBook();                       //kitap silme
void depBook();                          //kitap iade etme
void wait();                             //bekleme komutu     

                            //Devam tuş gerekliliği
void wait(){


    cout << "Devam etmek icin bir tusa basin..." << el;
    cin.ignore(); // programın devam etmesi için kullanıcının bir tuşa basmasını ister
    cin.get();    // Tuş girişi bekle
}

                            //admin Girişi
void adminLogin()
{
	string username="admin";   //admin girişi kullanıcı adı
    string password="1234";    //admin girişi şifresi
    
	string input_username,input_password;
    cout<<"Kullanici adi:";
    cin >>input_username;
    cout<<"Sifre:";
    cin >>input_password;
    if(input_username == username && input_password == password)    //Girdilerler tanımlanmışların eşleşmesi
    {
        isAdmin=true;
        adminEvents(true);
        
    }
    else
    cout<<"Hatali giris. Tekrar deneyiniz!"<<el;    //hatali giriş
    adminLogin();
}

                            //admin kontrolü
void adminCheck(){
   if(isAdmin){      //admin
    adminEvents(false);
   }
   else{              //admin değil
    studentEvents(false);
   }
}

                            //admin opsiyonu
void adminEvents(bool clearConsole)
{
    system("CLS");    //konsol temizleme komutu
    string options[] = { "Liste", "Kitap Ekleme", "Kitap Silme", "Kitap Verme", "Kitap Iade","Cikis" }; // Opsiyonların tanımlanması
    
    if (clearConsole) {
        system("CLS");
        cout<<"Yapmak istediginiz eylemi secin:\n";
    }

    for (int i = 0; i < sizeof(options) / sizeof(string); i++)  //Seçilecek opsiyon için index ataması
    {
        cout << "\n" << i + 1 << ". " << options[i] << "\n";
    }
    cout << "\n";

     // Index i switch e aktarma 
    int selectedIndex; 
    cin >> selectedIndex;
    system("CLS");
    switch (selectedIndex) {    //Opsiyonların atanması

    default:
        adminEvents(true); 
        break;
    case 1: 
        listBooks();      //kitapları listeler
        wait();           //bekleme komutu 
        adminCheck();     //admin kontrolü
        break;
    case 2:
        addBook();         //kitap ekleme
        break;
    case 3:
        removeBook();      //kitap silme
        break;
    case 4:
        giveBook();        //kitap ödünç verme
        break;
    case 5:
        depBook();         //kitap iadesi
        break;
    case 6:
        exit(1);           //çıkış komutu
        break;
    }
}

                            //kitap listesi
void listBooks()
 {
    fstream kitap;
    kitap.open("kitaplar.txt", ios::in); //txt dosyasını açar
    string line;
    int i=1;
    
    while (getline(kitap, line)) {  //getline kullanarak verileri çeker
        cout << i <<". " << line << endl;
        i++;
    }
   
 }

                            //kitap ekleme
void addBook() {
    int n;
    cout << "Eklemek istediginiz kitap sayisini girin: ";
    cin >> n;
    cin.ignore(); // programın devam etmesi için kullanıcının bir tuşa basmasını ister

    struct book b[n];   
    fstream kitap;
    kitap.open("kitaplar.txt", ios::app);   //kitaplar.txt ye append olarak yazmasını sağlar

    for(int i = 0; i < n; i++) {            
        cout << "Kitap bilgilerini girin:" << el;

        cout << "Kitap adi: ";
        getline(cin, b[i].bname); // Aralardaki boşluklar için getline kullanılır
        kitap << "Kitap adi: " << b[i].bname << ",\t";

        cout << "Yazar adi: ";
        getline(cin, b[i].aname); // Aralardaki boşluklar için getline kullanılır
        kitap << "Yazarin adi: " << b[i].aname << ",\t";

        cout << "Sayfa sayisi: ";
        cin >> b[i].bpage;      //integer değişkeni olduğu için getline a gerek yok
        kitap << "Sayfa sayisi: " << b[i].bpage << "\n";
        cin.ignore(); // programın devam etmesi için kullanıcının bir tuşa basmasını ister

        cout << "Kitap listeye eklendi." << el;
    }

    kitap.close();

    adminEvents(true); //admin events kısmına dönmesini sağlar
}

                            //kitap silme
void removeBook() {
    listBooks();
    int removeIndex;                    //silinecek kitap için index tanımlanır
    cout << "Silmek istediginiz kitabin numarasini girin: ";
    cin >> removeIndex;

    fstream kitap;
    kitap.open("kitaplar.txt", ios::in); //kitaplar.txt yi açar

    if (!kitap.is_open()) {              //kitaplar.txt yoksa geri bildirim verir
        cout << "Dosya acilamadi!" << el;
        return;
    }

    const int MAX_BOOKS = 100;            //Maksimum kitap sayısı
    string books[MAX_BOOKS];
    int currentIndex = 0;
    string line;

    //Dosyadaki kitapları diziye okutma
    while (getline(kitap, line)) {        
        if (currentIndex < MAX_BOOKS) {
            books[currentIndex] = line;   //Line da yazanları book arrayine yazdırır
            currentIndex++;
        }
    }

    kitap.close();

    // Silinmesi gereken kitabı atlayarak dosyaya yazar
    kitap.open("kitaplar.txt", ios::out | ios::trunc); //trunc : Dosya yoksa dosya oluşturur, Varsa değerleri silerek açar

    for (int i = 0; i < currentIndex; i++) {
        if (i + 1 != removeIndex) {   //removeIndex hariç tüm satırları tekrar yazdırır
            kitap << books[i] << el;  //el == endl
        }
    }

    kitap.close();

    cout << "Kitap silindi." << el;
    wait();
    adminEvents(true);
}

                            //kitap ödünç verilmesi
void giveBook() {
    int bookIndex;
    bool validIndex = false; 
    string studentNumber;
    fstream kitap;

    while (!validIndex) {                        //Geçersiz index olana kadar döngüyü döndürür
        listBooks();
        cout << "Almak istediginiz kitabin numarasini girin: ";
        cin >> bookIndex;

        kitap.open("kitaplar.txt", ios::in);    //kitaplar.txt yi açar

        const int MAX_BOOKS = 100;              // Maksimum kitap sayısı
        string books[MAX_BOOKS];
        int currentIndex = 0;
        string line;

        while (getline(kitap, line)) {              
            if (currentIndex < MAX_BOOKS) {
                books[currentIndex] = line;     //Line da yazanları book arrayine yazdırır
                currentIndex++;
            }
        }

        kitap.close();

        if (bookIndex > 0 && bookIndex <= currentIndex) {                       //bookIndex liste sınırları içerisindeyse çalışır
            validIndex = true;                           

            if (books[bookIndex - 1].find("(kullanimda)") != string::npos) {    //.find :dizi içerisinde string arar    npos: bulunamadı durumunu belirtmek için kullanılır
                cout << "Bu kitap zaten kullanimda. Baska bir kitap secin." << el;
                validIndex = false;
            } else {
                cout << "Ogrenci numarasini girin: ";
                cin >> studentNumber;

                books[bookIndex - 1] += " (kullanimda)";                        //Listeden seçilen index e kullanımda ifadesini ekler

                kitap.open("kitaplar.txt", ios::out | ios::trunc);              //trunc : Dosya yoksa dosya oluşturur, Varsa değerleri silerek açar
 
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

        kitap.open("kitaplar.txt", ios::in);                                        //kitaplar.txt yi açar

        const int MAX_BOOKS = 100;                                                  // Maksimum kitap sayısı
        string books[MAX_BOOKS];
        int currentIndex = 0;
        string line;

        while (getline(kitap, line)) {                      
            if (currentIndex < MAX_BOOKS) {
                books[currentIndex] = line;                                          //Line da yazanları book arrayine yazdırır
                currentIndex++;
            }
        }

        kitap.close();

        if (bookIndex > 0 && bookIndex <= currentIndex) {                             //bookIndex liste sınırları içerisindeyse çalışır
            validIndex = true;

            if (books[bookIndex - 1].find("(kullanimda)") == string::npos) {          //.find :dizi içerisinde string arar    npos: bulunamadı durumunu belirtmek için kullanılır
                cout << "Bu kitap kullanimda degil. Kullanimda olan bir kitap numarasi girin." << el << el;
                validIndex = false;
            } else {
                cout << "Ogrenci numarasini girin: ";
                cin >> studentNumber;

                //Listeden seçilen indexten kullanımda ifadesini siler
                size_t pos = books[bookIndex - 1].find("(kullanimda)");                //size_t:işaretsiz bir değişken oluşturmayı sağlar
                books[bookIndex - 1].erase(pos, string("(kullanimda)").length());      //erase operatöründe ilk sıradaki başlangıç konumu ikincisi sileceği karakter sayısı

                kitap.open("kitaplar.txt", ios::out | ios::trunc);                     //trunc : Dosya yoksa dosya oluşturur, Varsa değerleri silerek açar

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

                             //Öğrenci opsiyonu
void studentEvents(bool clearConsole)
{
    
    string options[] = { "Liste", "Cikis" };   //opsiyonun tanımlanması
   

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
    
    switch (selectedIndex) {            //index seçimi

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

                            //Giriş ekranı
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
    
    switch (loginIndex) {            //Login index seçimi yapılır

    case 1: 
        adminLogin();                //admin girişi seçimi
        break;
	case 2:
        studentEvents(true);         //öğrenci girişi seçimi
        break;
        }
    return 0;

    }
