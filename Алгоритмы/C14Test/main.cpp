struct widget
{
	int x;
	widget(int k = 0) : x(k) {}
	widget & operator =(const widget & arg) & noexcept;
    widget & operator =(const widget & arg) && = delete;
};
 
widget& widget::operator=(const widget& arg) & noexcept
{
	x = arg.x;
	return *this;
}
 
widget fun()
{
	widget x;
	return x;
}
 
int main()
{
	widget a, b;
	a = b;
	//fun() = a;
//	system("pause");
	return 0;
}