#include<iostream>
#include<vector>
#include<string>
using namespace std;
class MenuItem{
protected:
int id,p;
string n;
public:
MenuItem(int i,string a,int b){id=i;n=a;p=b;}
int getId(){return id;}
int getPrice(){return p;}
string getName(){return n;}
void display(){cout<<id<<". "<<n<<" - "<<p<<" iraqi dinar\n";}
void display(string a,int b){cout<<a<<" - "<<b<<" iraqi dinar\n";}
};
class Dish:public MenuItem{
public:
int ing[4],amt[4],cnt;
Dish(int i,string a,int b,int x[],int y[],int c):MenuItem(i,a,b){
cnt=c;
for(int j=0;j<c;j++){ing[j]=x[j];amt[j]=y[j];}
}
};
class Order{
int id,t,total;
public:
Order(int i,int a){id=i;t=a;total=0;}
void add(int p,int q){total+=p*q;}
void add(int p){total+=p;}
int getId(){return id;}
int getTotal(){return total;}
void display(){
cout<<"Order "<<id<<" | Table "<<t<<" | Total: "<<total<<" iqd\n";
}
};
class Restaurant{
vector<Dish>menu;
vector<Order>orders;
string ingN[8]={"Bread","Beef","Cheese","Dough","Tomato","Pasta","Chicken","Lettuce"};
int stk[8]={20,10,20,10,15,10,10,10};
int next=1;

int num(string msg){
int x;
cout<<msg;
cin>>x;
return x;
}

void showMenu(){
cout<<"\n     menu     \n";
for(int i=0;i<menu.size();i++)menu[i].display();
}

void showStock(){
cout<<"\n         stock         \n";
for(int i=0;i<8;i++)cout<<ingN[i]<<": "<<stk[i]<<'\n';
}
int findDish(int id){
for(int i=0;i<menu.size();i++)
if(menu[i].getId()==id)return i;
return -1;
}
bool checkStock(int i,int q){
for(int j=0;j<menu[i].cnt;j++){
int k=menu[i].ing[j];
if(stk[k]<menu[i].amt[j]*q){
cout<<"Not enough "<<ingN[k]<<".\n";
return false;
}
}
return true;
}
void useStock(int i,int q){
for(int j=0;j<menu[i].cnt;j++){
int k=menu[i].ing[j];
stk[k]-=menu[i].amt[j]*q;
}
}
public:
Restaurant(){
int a[]={0,1,2},b[]={1,1,1};
menu.push_back(Dish(1,"Burger",8000,a,b,3));
int c[]={3,2,4},d[]={1,2,1};
menu.push_back(Dish(2,"Pizza",12000,c,d,3));
int e[]={5,4,2},f[]={1,1,1};
menu.push_back(Dish(3,"Pasta",10000,e,f,3));
int g[]={0,6},h[]={1,1};
menu.push_back(Dish(4,"Chicken Sandwich",7000,g,h,2));
int j[]={7,4},k[]={2,1};
menu.push_back(Dish(5,"Salad",6000,j,k,2));
}
void createOrder(){
int t=num("Table number: ");
Order o(next++,t);
while(true){
showMenu();
int id=num("Dish ID (0 to finish): ");
if(id==0)break;
int i=findDish(id);
if(i==-1){cout<<"Dish not found.\n";continue;}
int q=num("Quantity: ");
if(q<=0){cout<<"Invalid quantity.\n";continue;}
if(!checkStock(i,q))continue;
useStock(i,q);
o.add(menu[i].getPrice(),q);
cout<<q<<" x "<<menu[i].getName()<<" added.\n";
}
if(o.getTotal()>0){
cout<<"Order total: "<<o.getTotal()<<" iqd\n";
orders.push_back(o);
cout<<"Order created. ID: "<<o.getId()<<'\n';
}else cout<<"Empty order cancelled.\n";
}
void showOrders(){
if(orders.empty()){cout<<"No orders yet.\n";return;}
for(int i=0;i<orders.size();i++)orders[i].display();
}
void bill(){
showOrders();
int id=num("Order ID: ");
for(int i=0;i<orders.size();i++){
if(orders[i].getId()==id){
cout<<"Total: "<<orders[i].getTotal()<<" iqd\n";
return;
}
}
cout<<"Order not found.\n";
}
void salesReport(){
int total=0;
for(int i=0;i<orders.size();i++)total+=orders[i].getTotal();
cout<<"Total sales: "<<total<<" iqd\n";
}
void run(){
int c;
do{
cout<<"\n1. View menu\n"
<<"2. Create order\n"
<<"3. View orders\n"
<<"4. Print bill\n"
<<"5. View ingredient stock\n"
<<"6. Sales report\n"
<<"0. Exit\n";
c=num("Choose: ");
switch(c){
case 1:showMenu();break;
case 2:createOrder();break;
case 3:showOrders();break;
case 4:bill();break;
case 5:showStock();break;
case 6:salesReport();break;
case 0:cout<<"Goodbye.\n";break;
default:cout<<"Invalid choice.\n";
}
}while(c!=0);
}
};
int main(){
Restaurant r;
r.run();
return 0;
}
