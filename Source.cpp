#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
using namespace std;

int Order_ID = 1;

class Person 
{
public:
	string Name;
	int ID;
	Person()
	{
		Name = "";
		ID = 0;
	}
};

class Product
{
public:
	string Name;
	int Quantity, ID;
	double Price;
	friend ostream& operator << (ostream&, const Product&);

};

void ClearProduct()
{
	ofstream myfile("Product.txt", ios_base::trunc);
}
void ProductToFile(map<int, Product> P, map<int, Product> ::iterator Products_IT, int Products_Number)
{
	ClearProduct();
	ofstream myfile("Product.txt", ios_base::app);
	Products_IT = P.begin();
	myfile << Products_Number << endl; 
	while (Products_IT != P.end())
	{
		myfile << Products_IT->second.ID << endl;
		myfile << Products_IT->second.Name << endl;
		myfile << Products_IT->second.Price << endl;
		myfile << Products_IT->second.Quantity << endl;
		myfile << endl;
		Products_IT++;
	}
	myfile.close();
}
void FileToProduct(map<int, Product>& Pmap , int& Products_Number)
{
	ifstream myfile("Product.txt");
	Product P;
	string line;
	int counter = 1;
	getline(myfile, line);
	Products_Number = atoi(line.c_str());
	while (getline(myfile, line))
	{
		if (line == "")
		{
			continue;
		}
		else if (counter == 1)
		{
			P.ID = atoi(line.c_str());
			counter++;
		}
		else if (counter == 2)
		{
			P.Name = line;
			counter++;
		}
		else if (counter == 3)
		{
			P.Price = stod(line.c_str());
			counter++;
		}
		else if (counter == 4)
		{
			P.Quantity = atoi(line.c_str());
			counter = 1;
			Pmap[P.ID] = P;
		}
		
	}
	myfile.close();
}

ostream& operator << (ostream& os, const Product& P) 
{
	os << " Name : " << P.Name << "    ";
	os << " ID : " << P.ID << "    ";
	os << " Price : " << P.Price << "    ";

	return os;
}

class Delivery_Boys : public Person
{
public:
	bool InOrder;
	Delivery_Boys()
	{
		InOrder = false;
	}
};

void ClearDelivery()
{
	ofstream myfile("Delivery.txt", ios_base::trunc);
}
void DeliveryToFile(map <int, Delivery_Boys> &D, map<int, Delivery_Boys> ::iterator Employees_IT, int Employee_ID)
{
	ClearDelivery();
	ofstream myfile("Delivery.txt", ios_base::app);
	Employees_IT = D.begin();
	myfile << Employee_ID << endl; 
	while (Employees_IT != D.end())
	{
		myfile << Employees_IT->second.ID << endl;
		myfile << Employees_IT->second.Name << endl;
		myfile << Employees_IT->second.InOrder << endl;
		myfile << endl;
		Employees_IT++;
	}
	myfile.close();
}
void FileToDelivery(map<int, Delivery_Boys> &Dmap , int& Employee_ID)
{
	ifstream myfile("Delivery.txt");
	string line;
	 getline(myfile, line);
	Employee_ID = atoi(line.c_str());
	
	int counter = 1;
	Delivery_Boys B;
	
	while (getline(myfile, line))
	{
		if (line == "")
			continue;
		else if (counter == 1)
		{
			B.ID = atoi(line.c_str());
			counter++; 
			//cout << " ID : " << B.ID << endl; 
		}
		else if (counter == 2)
		{
			B.Name = line;
			counter++;
		}
		else if (counter == 3)
		{
			if (line == "false")
			{
				B.InOrder = false;
			}
			else if ( line == "true")
			{
				B.InOrder = true;
			}
			Dmap[B.ID] = B;
			counter = 1;
		}
	}
	myfile.close();
}


class Order
{
public:
	int Total;
	time_t orderdate;
	int Counter, ID, Customer_ID, Delivery_ID;
	vector<Product> Order_Products;  /*Product Order_Products[200];*/
	int quantity[10]; /*xxxx*/
	string Delivery_Name, Customer_Name;

	Order()
	{
		for (int i = 0; i < 10; i++)
		{
			quantity[i] = 0;/*xxxx*/
		}
		Total = 0;
		Counter = 0;
		orderdate = time(NULL);
	}
	friend ostream& operator << (ostream&, const Order&);
};

ostream& operator << (ostream& os, const Order& O)
{
	cout << " Order ID : " << endl;
	cout << O.ID << endl;
	cout << " Customer ID : " << endl;
	cout << O.Customer_ID << endl;
	cout << " Customer Name : " << endl;
	cout << O.Customer_Name << endl;
	cout << " Delivery Boy ID : " << endl;
	cout << O.Delivery_ID << endl;
	cout << " Delivery Boy Name : " << endl;
	cout << O.Delivery_Name << endl;
	//cout << " Order Products : " << endl;
	//for (int i = 0; i < O.Counter; i++)
	//{
	//	cout << i + 1 << " ) " << endl;
	//	cout << O.Order_Products[i] << endl;

	//}
	//cout << " Total Price : " << O.Total << endl;
	//cout << "------------------------------------------------------" << endl;

	return os;
}

void ViewOrder(map<int, Product> Products, Order O , int Products_Number , map<int, Product> ::iterator Products_IT)
{
	
	Products_IT = Products.begin();
	
	for (int i = 0; i < Products_Number; i++)
	{

		if (O.quantity[i] > 0)
		{
			cout << "Name : " << Products_IT->second.Name << "    " << "Quantity : " << O.quantity[i] << endl;
			cout << "Item Price :" << Products_IT->second.Price << endl;
		}
		Products_IT++;
	}
	cout << " Total Price : " << O.Total << endl;
	cout << "________________________________________________________________________" << endl;
}

class Manager : public Person
{
public:
	void ViewCustomerBills (map<int, Order> Orders, map<int, Product> Products, int Products_Number , map<int, Order> ::iterator Order_IT , map<int, Product> ::iterator Products_IT)
	{

		
		Order_IT = Orders.begin();
		int Customer_ID; 
		cout << " Customer ID : " << endl; 
		cin >> Customer_ID;
		while (Order_IT != Orders.end())
		{
			if (Order_IT->second.Customer_ID == Customer_ID)
			{
				
				cout << Order_IT->second << endl;
				ViewOrder(Products, Order_IT->second, Products_Number , Products_IT);
				
			}
			Order_IT++;
		}


	}
	void CheckProducts(map<int, Product>& Products , map<int, Product> ::iterator Products_IT )
	{
		
		Products_IT = Products.begin();
		while (Products_IT != Products.end())
		{
			cout << " Name : " << Products_IT->second.Name << endl;
			cout << " ID : " << Products_IT->second.ID << endl;
			cout << " Price : " << Products_IT->second.Price << endl;
			cout << " Quantity : " << Products_IT->second.Quantity << endl;
			cout << "________________________________________________________________________" << endl;
			Products_IT++;
		}
		if (Products.size() == 0)
		{
			cout << " Products Is Empty " << endl;
		}
	}

	void AddEmp(map<int, Delivery_Boys> & Employees, int& Employee_ID)
	{
		Delivery_Boys db;
		cout << " Employee's Name : ";
		cin >> db.Name;
		Employee_ID++;
		db.ID = Employee_ID;
		cout << " Employee's ID Is : " << db.ID << endl;

		Employees[db.ID] = db;
		cout << " Employee Is Added " << endl;
	}

	void RemoveEmp(map<int, Delivery_Boys> & Employees , int& Employee_ID , map<int, Delivery_Boys> ::iterator Employees_IT)
	{
		//map < int, Delivery_Boys > ::iterator IT;
		int id;
		cout << " Enter Employee's ID : ";
		cin >> id;
		Employees_IT = Employees.find(id);
		if (Employees_IT == Employees.end())
		{
			cout << " Employee Not Found ! " << endl;
		}
		else
		{
			Employees_IT = Employees.erase(Employees_IT);
			cout << " Employee Is Successfully Deleted " << endl;
			Employee_ID--;
		}

	}


};

class Customer : public Person
{
public:
	string  CVV, EMail, Password;
	Customer()
	{

		CVV = "Empty";
		EMail = "Empty";
		Password = "Empty";
		
	}
	void ViewCataloge(map<int, Product> Products)
	{
		map <int, Product> ::iterator IT;
		IT = Products.begin();
		cout << " Our Cataloge " << endl;
		int Counter = 1;
		while (IT != Products.end())
		{
			cout << "   " << Counter << " ) ";
			cout << IT->second << endl;
			cout << " Quantitiy : " << IT->second.Quantity << endl;
			Counter++;
			IT++;
		}

	} 
	void UnRegister(map<int, Customer>& Customers)
	{
		int id;
		string Pass;
		map < int, Customer> ::iterator IT;
		cout << " Please Enter Your ID : " << endl;
		cin >> id;
		IT = Customers.find(id);
		if (IT == Customers.end())
		{
			cout << " Account With Such ID Does Not Exist ! " << endl;
		}
		else
		{
			cout << " Please Enter Your Password " << endl;
			cin >> Pass;
			if (Pass == IT->second.Password)
			{
				IT = Customers.erase(IT);
				cout << " Account Is Successfully Deleted " << endl;
			}
			else
			{
				cout << " Wrong Password !! " << endl;
			}

		}

	}
	void ViewPreviousBills(map<int, Order> Orders, map<int, Product>& Products, int Products_Number , map<int, Product> ::iterator Products_IT)
	{

		map < int, Order> ::iterator it;
		it = Orders.begin();
		while (it != Orders.end())
		{
			if (it->second.Customer_ID == ID)
			{
				cout << it->second << endl;
				ViewOrder(Products, it->second, Products_Number, Products_IT);
			}
			it++;
		}


	}
	void ReFund(map<int, Product>& Products, map<int, Order>& Orders)
	{
		map<int, Order>::iterator it;
		int orderid, productid;
		bool date14 = true, found = false, avl = false;
		cout << "Enter the order id: ";
		cin >> orderid;
		cout << "Enter the Product id: ";
		cin >> productid;
		size_t OID = orderid;

		if (OID > Orders.size())
		{
			cout << "Order's ID is incorrect!!" << endl;
		}
		else
		{
			it = Orders.begin();
			while (it != Orders.end())
			{
				if (it->second.ID == orderid)
				{
					time_t now;
					now = time(NULL);
					long long diff = difftime(now, it->second.orderdate);
					//14 days in seconds -> 1209600...to test the time function change this value to 5 seconds 
					if (diff <= 1209600)
					{
						date14 = true;
					}
					else
					{
						date14 = false;
					}
					if (!date14)
					{
						cout << "Sorry We can't return this Product as you owned it More than 14 days!!" << endl;
						break;
					}
					else if (date14)
					{
						for (int i = 0; i < it->second.Order_Products.size(); i++)
						{
							if (it->second.Order_Products[i].ID == productid)
							{
								map < int, Product> ::iterator IT = Products.begin();
								while (IT != Products.end())
								{
									if (IT->second.ID == productid)
									{
										if (it->second.quantity[i] > 0)
										{
											found = true;
											avl = true;
											IT->second.Quantity += 1;
											it->second.Total -= it->second.Order_Products[i].Price;
											it->second.quantity[i]--;
											cout << "Current Quantitiy=" << it->second.quantity[i] << endl;
										}
										else
										{
											found = false;
										}
										break;
									}
									else
									{
										IT++;
									}

								}
							}
						}
						if (avl == true && found == true)
						{
							cout << "Done!!" << endl;
							break;
						}
					}
				}
				it++;
			}
			if (found == false)
			{
				cout << "This Product is not in this order!!" << endl;
			}
		}
	}
	void New_Order(map<int, Product>& Products, map<int, Delivery_Boys> & Employees,/* Customer C,*/ map<int, Order>& Orders)
	{
		Order O;
		int q = 0;
		map<int, Delivery_Boys> ::iterator IT1;
		IT1 = Employees.begin();
		while (IT1 != Employees.end())
		{
			if (IT1->second.InOrder == false)
			{
				IT1->second.InOrder = true;
				break;
			}

			IT1++;

		}
		O.orderdate = time(NULL);
		O.Delivery_ID = IT1->second.ID;
		O.Delivery_Name = IT1->second.Name;
		O.Customer_ID = ID;
		O.Customer_Name = Name;
		map < int, Product> ::iterator IT = Products.begin();
		int id = -1;

		cout << " Here Is Our Cataloge : " << endl;
		ViewCataloge(Products);
		cout << " Press '0' When U Are Done ! " << endl;
		while (id != 0)
		{

			cout << " Product ID : ";
			cout << endl;
			cin >> id;
			IT = Products.find(id);
			if (IT == Products.end())
			{
				continue;
			}
			else
			{
				cout << " Quantity : ";
				cin >> q;
				if (q <= IT->second.Quantity)
				{
					//for (int i = 0; i < q; i++)
					//{

					//O.Order_Products[O.Counter] = IT->second;
					O.Total += IT->second.Price * q;
					IT->second.Quantity = IT->second.Quantity - q;
					O.Order_Products.push_back(IT->second);
					//O.Order_Products[O.Counter].Quantity = O.Order_Products[O.Counter].Quantity - q;
					O.Counter = O.Counter + q;



					//}
					O.quantity[IT->second.ID - 1] = q + O.quantity[IT->second.ID - 1];

					cout << "\nYou added " << q << " items of ( " << IT->second.Name << " ) to your order" << endl;
					cout << "Remaining items of this product : " << IT->second.Quantity << endl << endl;

				}
				else
				{
					cout << " This Product Is Out .." << endl;
				}
			}
		}

		O.ID = Order_ID;
		Orders[O.ID] = O;
		Order_ID++;
		O.Total = 0;
		q = 0;
	}
};

void ClearCustomer()
{
	ofstream myfile("Customer.txt", ios_base::trunc);
}
void CustomerToFile(map<int, Customer> &C, map<int, Customer>::iterator IT)
{
	ClearCustomer();
	ofstream myfile("Customer.txt", ios_base::app);
	IT = C.begin();
	while (IT != C.end())
	{
		myfile << IT->second.ID << endl;
		myfile << IT->second.Name << endl;
		myfile << IT->second.CVV << endl;
		myfile << IT->second.EMail << endl;
		myfile << IT->second.Password << endl;
		myfile << endl;
		IT++;
	}
	myfile.close();
}
void FileToCustomer(map<int, Customer> &Cmap)
{
	ifstream myfile("Customer.txt");
	string line;
	int counter = 1;
	Customer C;
	while (getline(myfile, line))
	{
		if (line == "")
			continue;
		else if (counter == 1)
		{
			C.ID = atoi(line.c_str());
			counter++;
		}
		else if (counter == 2)
		{
			C.Name = line;
			counter++;
		}
		else if (counter == 3)
		{
			C.CVV = line;
			counter++;
		}
		else if (counter == 4)
		{
			C.EMail = line;
			counter++;
		}
		else if (counter == 5)
		{
			C.Password = line;
			counter++;
			Cmap[C.ID] = C;
			counter = 1;
		}
	}
	myfile.close();
}

Customer Register(map<int, Customer>& Customers)
{
	bool found = false;
	map < int, Customer> ::iterator IT;
	IT = Customers.begin();
	Customer C;
	cout << " Enter Your Name : ";
	cin >> C.Name;
	cout << " Enter Your Credit Card CVV : ";
	cin >> C.CVV;
	cout << " Enter Your EMail : ";
	cin >> C.EMail;
	cout << " Enter Your Password : ";
	cin >> C.Password;
	cout << " Enter Your ID : ";
	cin >> C.ID;

	for (unsigned int i = 0; i < Customers.size(); i++)
	{

		if (IT->second.Password == C.Password || IT->second.ID == C.ID)
		{
			cout << " Contact Info Already Used By Another Account " << endl;
			found = true;
			break;
		}
		IT++;
	}
	if (found != true)
	{
		Customers[C.ID] = C;
		cout << " Account Is Successfully Added " << endl;
	}
	return C;
}

Customer Sign_In(map<int, Customer>& Customers , map<int, Customer>::iterator Customer_IT )
{
	int id;
	string password;
	//map < int, Customer> ::iterator IT;
	while (true)
	{
		cout << " Please Enter Your Info " << endl;
		cout << " ID : ";
		cin >> id;
		cout << " Password : ";
		cin >> password;
		Customer_IT = Customers.find(id);
		if (Customer_IT == Customers.end())
		{
			cout << " Customer With Such ID Does Not Exist ! " << endl;
			return Customer();
		}
		else
		{
			if (Customer_IT->second.Password == password)
			{
				cout << " You Are Signed In As : " << Customer_IT->second.Name << endl;
				return Customer_IT->second;
			}
			else
			{
				cout << " Wrong Password , Retry ! " << endl;
				continue;
			}

		}
	}

}



int main()
{
	map<int, Delivery_Boys> Employees; 
	map<int, Product> Products; 
	map<int, Customer> Customers; 
	map<int, Order> Orders; 
	map<int, Customer>::iterator Customer_IT; 	
	map<int, Order> ::iterator Order_IT; 
	map<int, Delivery_Boys> ::iterator Employees_IT;
	map<int, Product> ::iterator Products_IT;
	int choice = 0 , All, M1, C1, C2 , Employee_ID = 1, Products_Number = 0;
	bool exit = false;
	
	FileToProduct(Products,Products_Number);
	 
	FileToDelivery(Employees, Employee_ID);
	
	FileToCustomer(Customers);
	
	cout << "                Welcome To Online Shopping Managment System                  " << endl;
	while (choice != 3)
	{

		M1 = 0;
		C2 = 0;
		system("cls");
		cout << "  Would You Like To : " << endl;
		cout << " 1) Enter as a Manager       2) Enter as a Customer       3) Exit" << endl;
		cout << " Your Choice : ";
		cin >> choice;
		if (choice == 1)/*Manager*/
		{
			Manager manager; 
			while (M1 != 6)
			{
				cout << " 1) Add Employee " << endl;
				cout << " 2) Remove Employee " << endl;
				cout << " 3) View Active Bills " << endl;
				cout << " 4) View Customer Bills " << endl;
				cout << " 5) Check The Products " << endl;
				cout << " 6) Exit " << endl;

				cin >> M1;
				if (M1 == 1)
				{
					manager.AddEmp(Employees,Employee_ID);
				}
				else if (M1 == 2)
				{
					manager.RemoveEmp(Employees,Employee_ID,Employees_IT);
				}
				else if (M1 == 3)
				{

				}
				else if (M1 == 4)
				{
					manager.ViewCustomerBills(Orders, Products, Products_Number,Order_IT,Products_IT);
					
				}
				else if (M1 == 5)
				{
					manager.CheckProducts(Products,Products_IT);
				}
			}
		}
		else if (choice == 2) /*Customer*/
		{
			Customer C;
			cout << " Would You Like To : " << endl;
			cout << " 1) Register For The First Time . " << endl;
			cout << " 2) Sign In  . " << endl;
			cout << " 3) Unregister From The System . " << endl;
			cout << " 4) Exit . " << endl;
			cin >> C1;
			if (C1 == 1)
			{
				C = Register(Customers);
			}
			else if (C1 == 2)
			{
				C = Sign_In(Customers,Customer_IT);
			}
			else if (C1 == 3)
			{
				C.UnRegister(Customers);
				
			}

			if (C1 == 1 || C1 == 2)
			{
				cout << " Print -1 when u want to break " << endl;
				while (C2 != 5)
				{
					cout << " 1) View The Products Catalogue . " << endl;
					cout << " 2) Make A New Order . " << endl;
					cout << " 3) View My Previous Orders . " << endl;
					cout << " 4) Return A Product And Be ReFunded . " << endl;
					cout << " 5) Exit . " << endl;
					cin >> C2;
					if (C2 == 1)
					{
						C.ViewCataloge(Products);
					}
					else if (C2 == 2)
					{
						C.New_Order(Products, Employees,Orders);
					}
					else if (C2 == 3)
					{
						C.ViewPreviousBills(Orders, Products , Products_Number,Products_IT);
					}
					else if (C2 == 4)
					{
						C.ReFund(Products, Orders);
					}
				}
			}
		}
		
		CustomerToFile(Customers, Customer_IT);
		DeliveryToFile(Employees, Employees_IT, Employee_ID);
		ProductToFile(Products, Products_IT , Products_Number);
	}
	
	return 0;
}
