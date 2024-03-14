class Data
{
	private:
		int _data;
	public:
		Data();
		Data(int data);
		Data(const Data& other);
		const Data& operator= (const Data& other);
		~Data();
		const int& getData() const;
};