#include <iostream>
using namespace std	;

typedef struct note // khoi tao mot note o do co chua mot gia tri va dia chi cua note tiep theo
{
	int data; // giá tri
	note *pnext; // mot note moi hay con duoc goi la dia chi cua note dang sau o chinh note hien nay
}note;
typedef struct dslk 
{ // khoi tao dslk luon co dia chi dau va cuoi 
// chua tro di dau nên là NULL
	note *phead = NULL;
	note *ptail = NULL;
}dslk;

note *khoitao_note(int x);
void xuat(dslk ds);
void them_cuoi(dslk &ds,int x);
void them_dau(dslk &ds, int x);
void them_vt(dslk &ds, int location, int value);
void xoa_dau(dslk &ds);
void xoa_cuoi(dslk &ds);
void xoa_vt(dslk &ds, int value);
void tach(dslk &initial, dslk &am);

int main()
{
	dslk ds;
	int sl;cout << "Nhap sl pt can them: ";cin >> sl;
	for (int i = 1;i <= sl;i++)
	{
		int x;cout << "Nhap pt thu " << i << ": ";cin >> x;
		them_cuoi(ds, x);
	}
	xuat(ds);
	// xoa cuoi
//	int value ;cout<< "\nNhap gia tri can xoa : " ;cin>>value;
//	xoa_vt(ds,value);
//	cout << "=========XOA_VT=========="<< endl;
//	xuat(ds);
	// dung man hinh
	dslk am;
	tach(ds,am);
	cout << "==========DUONG========="<< endl;
	xuat(ds);
	cout << "==========AM========="<< endl;
	xuat(am);
	cout << "==========kiemtra,phead ,ptail============" << endl; 
	cout << "test : " << ds.phead->data << " ptail  : " << ds.ptail ->data << endl;;
	system("pause");
	return 0;
}
void tach(dslk &initial, dslk &am)
{
	while(initial.phead->data < 0)
	{
		them_cuoi(am,initial.phead->data);
		note *temp = initial.phead;
		initial.phead = initial.phead->pnext;
		delete temp;
		if(initial.phead == NULL)
		{
			initial.ptail == NULL;
			return ;
		}
	}
	note *tam = NULL;
	for(note *k = initial.phead ; k != NULL; k = k-> pnext )
	{
		if(k->data < 0)
		{
			them_cuoi(am,k->data);
			xoa_vt(initial,k->data);
			k = tam;
			if(tam->pnext == NULL)
			{
				initial.ptail = tam;
				break;
			}
		}	
		tam = k;
	}
}
void them_cuoi(dslk &ds,int x)
{
	if(ds.phead == NULL && ds.ptail == NULL) // TH1 : th mà chua co note nào ca
	{
		note *p	= khoitao_note(x);// tao mot note truoc sau do vi chi co mot note thôi 
		// nên ca dau ca cuoi deu o note do
		
		
		ds.phead = ds.ptail = p; //cho dia chi cua phead va ptail bang p ma p luc nay dang quan ly mot note co data x va pnext chi ve NULL;
	}
	else // TH2 : TH2 da co note
	{
		note *p	= khoitao_note(x);
		
		ds.ptail-> pnext = p;
		// cho dia chi ptail bang pnext 
		// lúc này 
		ds.ptail = p;
	}
}
void them_dau(dslk &ds, int x)
{
	if(ds.phead == NULL && ds.ptail == NULL)// th1 : khong co phan tu nao
	{
		note *p = khoitao_note(x);
		ds.phead = ds.ptail = p;
	}
	else // th2 co >= 1 phan tu
	{
		note *p = khoitao_note(x);
		p->pnext = ds.phead;
		ds.phead = p;
	}	
}
void xoa_dau(dslk &ds)
{
	if (ds.phead == ds.ptail && ds.phead != NULL) // th co mot phan tu
	{
		delete ds.phead;
		ds.ptail = ds.phead = NULL;
	}
	else if(ds.phead != ds.ptail) // th2 co nhieu phan tu
	{
		note *temp = ds.phead;
		ds.phead = ds.phead->pnext;
		delete temp;
	}
}
void xoa_cuoi(dslk &ds)
{
	if(ds.phead == ds.ptail && ds.phead != NULL)	 // th co mot phan tu
	{
		delete ds.ptail;
		ds.phead = ds.ptail = NULL;
	}
	else if(ds.phead != ds.ptail) // th2 co nhieu phan tu
	{
		for(note *k = ds.phead; k!=NULL ;k = k->pnext)
		{
			if(k->pnext->pnext == NULL) // v? trí ap út
			{
				delete ds.ptail;
				k->pnext = NULL;
				ds.ptail = k;
				break;
			}
		}
	}
}
void them_vt(dslk &ds, int location, int value)
{
	if(location == 0)
	{
		them_dau(ds,value);
	}
	else {
		note *p = khoitao_note(value);
		int dem = 0, temp =0 ;
		for(note *k = ds.phead; k!=NULL;k = k->pnext)
		{
			if((temp=dem+1)  == location) // vd : neu ta them o vi tri 1 thì ta dung con tro k o vt 0;
			{
				p->pnext = k->pnext->pnext; // cho con tro p chi den vi tri 2 ;
				k->pnext = p; // cho vi tri 0 (hien tai) tro den vi tri p 
			}
			dem++;
		}
	}
}
void xoa_vt(dslk &ds, int value)
{
	if (ds.phead != ds.ptail)
	{
		while(ds.phead->data == value)
		{
			note *tam = ds.phead;
			ds.phead = ds.phead->pnext;
			delete tam;
			if(ds.phead == NULL)
			{
				ds.ptail == NULL;
				return ;
			}
		}
		note *h = NULL;
		for(note *k = ds.phead ; k != NULL ; k= k -> pnext)
		{
			if(k->data == value )
			{
				h->pnext = k ->pnext;
				delete k;
				k = h;
				if(h->pnext ==	NULL)
				{
					ds.ptail = h;
					break;
				}
			}
			h = k;
		}
	}

}
note *khoitao_note(int x) // bien mot gia tri thanh mot note nam giu dia chi x va no duoc coi nhu ptail vi khong tro di dau ca
{
	note*p = new note;
	p-> data = x;
	p -> pnext = NULL ;
	return p;
}
void xuat(dslk ds)
{
	cout << "===========XUAT========="<<endl;
	int i = 1;
	for( note *k = ds.phead; k!= NULL;k = k->pnext)
	{
		cout << "PT thu " << i++ << " la: " << k->data << endl;
	}
}
