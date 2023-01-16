#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Order{//основной класс, который отвечает за построение одного заказа, скажем так, его структура
    protected:
    string surname, telnumber, type, price;
    int nomber;
    public:
    virtual void create(const int &nmb,const string &sur, const string &tel,const string &typ,const string &pr){//Функция, кооторая заносит в структуру элементы
        nomber=nmb;
        surname=sur;
        telnumber=tel;
        type=typ;
        price=pr;
    }
    virtual void create(const int nmb, const char* sur, const char* tel,const char* typ,const char* pr){//Функция, которая заносит в структуру элементы
        nomber=nmb;
        surname=sur;
        telnumber=tel;
        type=typ;
        price=pr;
    }
    void replaceEl(int el){//Функция, которая меняет значентие определённого элемента у одного из заказов
        if(el==1){
            string newSurname;
            cout<<endl<<"Введите изменение:";cin>>newSurname;
            surname=newSurname;
        }
        else if(el==2){
            string newTelnumber;
            cout<<endl<<"Введите изменение:";cin>>newTelnumber;
            telnumber=newTelnumber;
        }
        else if(el==3){
            string newType;
            cout<<endl<<"Введите изменение:";cin>>newType;
            type=newType;
        }
        else if(el==4){
            string newPrice;
            cout<<endl<<"Введите изменение:";cin>>newPrice;
            price=newPrice;
        }
    }
    virtual void print()=0;
    virtual void save()=0;
    virtual void del()=0;
};
class Client: public Order{//Класс, в котором выполняются действия с заказами
    public:
    void print(){//Функция, отвечающая за вывод
        cout<<"№ "<<nomber<<" "<<"Фамилия: "<<surname<<" "<<"Тел.: "<<telnumber<<" "<<"Тип ПО: "<<type<<" "<<"Цена: "<<price<<endl;
    }
    void save(){//Функция, отвечающая за загрузку заказов в файл
        setlocale(LC_ALL,"RUSSIAN");//Локализация, чтобы русский тест нормально выводился в текстовик
        ofstream fout("orders.txt", ios_base::app);
        fout<<nomber<<endl<<surname<<endl<<telnumber<<endl<<type<<endl<<price<<endl;
        fout.close();
    }
    void del(){//Функция, которая отвечаяет за удаление информации из файла
        ofstream fout("orders.txt", ios_base::out);
        fout.close();
    }
};
class fabrika{//Класс, который работает над созданием заказа
    public:
    Order* create(const int nb,const char* sn, const char* tl, const char* tp,const char* pri){
        string sn1,tl1,tp1,pri1;
        int nb1;
        sn1=sn;
        tl1=tl;
        tp1=tp;
        pri1=pri;
        nb1=nb;
        return create(nb1,sn1,tl1,tp1,pri1);
    }
    Order* create(int nb,string sn, string tl, string tp, string pri){
        Order *res=NULL;
        res=new Client;
        res->create(nb, sn,tl,tp,pri);
        return res;
    }
};
class controller{//Класс, отвечающий за работу Консоли
    private:
    bool work;
    public:
    fabrika PO;
    int all=0,counter=0;//all-Вспомогательная переменная, которая показывает количество всех заказов, которые были введены, counter- вспомогательная переменная, которая показывает какой порядковый номер был последним в заказах
    Order ** orders=new Order*[100];
    controller(){
        work = 1;
    }
    bool getWork(){
        return work;
    }
    void showMenu(){//Основная консоль
        cout<<"Заказы фирмы разработки ПО"<<endl;
        cout<<"1 - Добавить заказ"<<endl;
        cout<<"2 - Удалить заказ"<<endl;
        cout<<"3 - Изменить заказ"<<endl;
        cout<<"4 - Загрузить из файла"<<endl;
        cout<<"5 - Выгрузить в файл"<<endl;
        cout<<"6 - Вывести все заказы"<<endl;
        cout<<"0 - Exit"<<endl;
        
        while (getMenuItem()==-1);
    }
    int getMenuItem(){//Функция, которая отвечает за работоспособность консоли
        string s,t,ty,p;//s-фамилия, t-номер телефона, ty-тип ПО, p-цена
        int h=0,i=0,l=0,nom=0,g=0;//h-переменная, которая нужна для работы с изменением элемента;i-вспомогательная переменная,l-переменная, которая помогает в введении данных в массив, nom-переменная, которая помогает выводить личные номера заказов, g- переменная, которая помогает считать из файла
        char c;//Вспомогательная переменная, которая осуществялет работу консоли
        cout<<"Введите цифру: ";
        cin>>c;
        
        if (c=='1'){//Добавление заказа
            cout<<"Сколько будет заказов?(для выходы напишите 0)";
            cin>>i;
            if(i==0){
                cout<<endl;
                return 1;
            }
            else{
                l=all+i;
                for(all;all<l;all++){
                    counter=counter+1;
                    cout<<"Фамилия: ";cin>>s;
                    cout<<"Номер телефона: ";cin>>t;
                    cout<<"Тип ПО: ";cin>>ty;
                    cout<<"Цена: ";cin>>p;
                    cout<<endl;
                    orders[all]=PO.create(counter,s,t,ty,p);//Создание в массиве элемента типа Order
                };
                return 1;
            }
        }
        else if(c=='2'){//Удаление заказа
            cout<<"Какой номер у заказа, который вы хотите удалить?(для выходы напишите 0)";cin>>i;
            if(i==0){
                cout<<endl;
                return 2;
            }
            else if(all<i){
                cout<<"Такого заказа нет"<<endl;
                return 2;
            }
            else{
                i--;
                all--;
                for (i;i<all;i++){
                    orders[i]=orders[i+1];
                }
                cout<<"Заказ удалён"<<endl<<endl;
            }
            return 2;
        }
        else if(c=='3'){//Замена элемента в заказе
            cout<<"Какой номер у заказа, который вы хотите изменить?(для выходы напишите 0)";cin>>i;
            if(i==0){
                cout<<endl;
                return 3;
            }
            else if(i>all){
                cout<<"Такого заказа нет";
                cout<<endl;
                return 3;
            }
            else{
                i--;
                cout<<"Какой элемент вы хотите изменить?(1-Фамилия,2-Телефон,3-Тип ПО,4-Цену)";cin>>h;
                orders[i]->replaceEl(h);
                return 3;

            }
            return 3;
        }
        else if(c=='4'){//Загрузка из файла
            fstream fin;
            fin.open("orders.txt", ios::in);
    
            if (!fin.is_open()) {
                cout<<"Файл не может быть открыт"<<endl<<endl;
            }
            else if (all==0){
                while (fin>>nom && fin>>s && fin>>t && fin>>ty && fin>>p){
                    l=all+1;
                        for (all;all<l;all++){
                            orders[g]=PO.create(nom,s,t,ty,p);//Создание новых элементов типа Order в пустой массив
                        }
                    g++;
                }
                cout<<"Файл успешно считан"<<endl<<endl;
            }
            else{ 
                cout<<"Файл может быть считан только в пустое хранилище"<<endl<<endl;
            }
            fin.close();
            return 4;
        }
        else if(c=='5'){//Выгрузка в файл
            orders[0]->del();
            for (i=0;i<all;i++){
                orders[i]->save();
            }
            return 5;
        }
        else if(c=='6'){//Вывод всех заказов, котороые есть в программе
            for (i=0;i<all;i++){
                orders[i]->print();
                cout<<endl;
            }
            return 6;
        }
        else if(c=='0'){
            work=0;
            return 0;
        }
        else{
            return -1;
            
        }
    }
};
int main()
{
    setlocale(LC_ALL,"RUSSIAN");
    controller ctrl; // Запуск консоли
    while(ctrl.getWork())
        ctrl.showMenu();
    return 0;
}